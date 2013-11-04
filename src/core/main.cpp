#include <string>
#include <cstring>
#include <fstream>
#include <vector>

#include "global.h"
#include "RoleFactory.h"
LogCategory mainlog("main", "Main");

ConfigVariable<std::vector<std::string> > dc_files("general/dc_files", std::vector<std::string>());

int main(int argc, char *argv[])
{
	std::string cfg_file;

	//TODO: Perhaps verbosity should be specified via command-line switch?
	if(argc < 2)
	{
		cfg_file = "astrond.yml";
	}
	else
	{
		cfg_file = "astrond.yml";
		for(int i = 1; i < argc; i++)
		{
			if((strcmp(argv[i], "--log") == 0 || strcmp(argv[i], "-L") == 0) && i + 1 < argc)
			{
				delete g_logger;
				g_logger = new Logger(argv[++i]);
			}
			else if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
			{
				std::cerr << "Usage: astrond [OPTION]... [CONFIG]" << std::endl
				          << "Astrond is a distributed server daemon." << std::endl << std::endl
				          << "-h, --help  Print this help dialog." << std::endl
				          << "-L, --log   Specify a file to write log messages to." << std::endl;
				exit(0);
			}
		}
		if(argv[argc - 1][0] != '-')
		{
			cfg_file = argv[argc - 1];
		}
	}

	mainlog.info() << "Loading configuration file..." << std::endl;


	std::ifstream file(cfg_file.c_str());
	if(!file.is_open())
	{
		mainlog.fatal() << "Failed to open configuration file." << std::endl;
		return 1;
	}

	if(!g_config->load(file))
	{
		mainlog.fatal() << "Could not parse configuration file!" << std::endl;
		return 1;
	}
	file.close();

	std::vector<std::string> dc_file_names = dc_files.get_val();
	for(auto it = dc_file_names.begin(); it != dc_file_names.end(); ++it)
	{
		if(!g_dcf->read(*it))
		{
			mainlog.fatal() << "Could not read DC file " << *it << std::endl;
			return 1;
		}
	}

	// Initialize configured MessageDirector
	MessageDirector::singleton.init_network();
	g_eventsender.init();

	// Load uberdog metadata from configuration
	YAML::Node udnodes = g_config->copy_node()["uberdogs"];
	if(!udnodes.IsNull())
	{
		for(auto it = udnodes.begin(); it != udnodes.end(); ++it)
		{
			YAML::Node udnode = *it;
			Uberdog ud;
			ud.dcc = g_dcf->get_class_by_name(udnode["class"].as<std::string>());
			if(!ud.dcc)
			{
				mainlog.fatal() << "DCClass " << udnode["class"].as<std::string>()
				               << "Does not exist!" << std::endl;
				exit(1);
			}
			ud.anonymous = udnode["anonymous"].as<bool>();
			g_uberdogs[udnode["id"].as<doid_t>()] = ud;
		}
	}

	// Initialize configured roles
	YAML::Node node = g_config->copy_node();
	node = node["roles"];
	for(auto it = node.begin(); it != node.end(); ++it)
	{
		RoleFactory::singleton.instantiate_role((*it)["type"].as<std::string>(), *it);
	}

	try
	{
		io_service.run();
	}
	catch(std::exception &e)
	{
		mainlog.fatal() << "Exception from the network io service: "
		                << e.what() << std::endl;
	}

	return 0;
}
