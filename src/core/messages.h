#pragma once

// Defined types
typedef unsigned long long channel_t;

// Channel constants
#define CONTROL_MESSAGE 4001

// Control message-type constants
#define CONTROL_ADD_CHANNEL 2001
#define CONTROL_REMOVE_CHANNEL 2002
#define CONTROL_SET_CON_NAME 2004
#define CONTROL_SET_CON_URL 2005
#define CONTROL_ADD_RANGE 2008
#define CONTROL_REMOVE_RANGE 2009
#define CONTROL_ADD_POST_REMOVE 2010
#define CONTROL_CLEAR_POST_REMOVE 2011

// State Server constants and macros:
#define STATESERVER_OBJECT_GENERATE_WITH_REQUIRED 2001
#define STATESERVER_OBJECT_GENERATE_WITH_REQUIRED_OTHER 2003
#define STATESERVER_OBJECT_UPDATE_FIELD  2004
#define STATESERVER_OBJECT_UPDATE_FIELD_MULTIPLE  2005
#define STATESERVER_OBJECT_DELETE_RAM  2007
#define STATESERVER_OBJECT_SET_ZONE  2008
#define STATESERVER_OBJECT_CHANGE_ZONE  2009
#define STATESERVER_OBJECT_NOTFOUND  2015
#define STATESERVER_OBJECT_QUERY_ALL  2020
#define STATESERVER_OBJECT_QUERY_ZONE_ALL  2021
#define STATESERVER_OBJECT_LOCATE  2022
#define STATESERVER_OBJECT_LOCATE_RESP  2023
#define STATESERVER_OBJECT_QUERY_FIELD  2024
#define STATESERVER_OBJECT_QUERY_ALL_RESP  2030
#define STATESERVER_OBJECT_LEAVING_AI_INTEREST  2033
#define STATESERVER_OBJECT_SET_AI_CHANNEL  2045
#define STATESERVER_OBJECT_QUERY_ZONE_ALL_DONE  2046
#define STATESERVER_OBJECT_NOTIFY_MANAGING_AI 2047
#define STATESERVER_OBJECT_CREATE_WITH_REQUIRED_CONTEXT  2050
#define STATESERVER_OBJECT_CREATE_WITH_REQUIR_OTHER_CONTEXT  2051
#define STATESERVER_OBJECT_CREATE_WITH_REQUIRED_CONTEXT_RESP  2052
#define STATESERVER_OBJECT_CREATE_WITH_REQUIR_OTHER_CONTEXT_RESP  2053
#define STATESERVER_OBJECT_DELETE_DISK  2060
#define STATESERVER_SHARD_RESET  2061
#define STATESERVER_OBJECT_QUERY_FIELD_RESP  2062
#define STATESERVER_OBJECT_ENTERZONE_WITH_REQUIRED  2065
#define STATESERVER_OBJECT_ENTERZONE_WITH_REQUIRED_OTHER  2066
#define STATESERVER_OBJECT_ENTER_AI_RECV  2067
#define STATESERVER_OBJECT_ENTER_OWNER_RECV  2068
#define STATESERVER_OBJECT_CHANGE_OWNER_RECV  2069
#define STATESERVER_OBJECT_SET_OWNER_RECV  2070
#define STATESERVER_OBJECT_QUERY_FIELDS  2080
#define STATESERVER_OBJECT_QUERY_FIELDS_RESP  2081
#define STATESERVER_OBJECT_QUERY_FIELDS_STRING  2082
#define STATESERVER_OBJECT_QUERY_MANAGING_AI  2083
#define STATESERVER_BOUNCE_MESSAGE  2086
#define STATESERVER_QUERY_OBJECT_CHILDREN_LOCAL  2087
#define STATESERVER_QUERY_OBJECT_CHILDREN_LOCAL_DONE  2089
#define STATESERVER_QUERY_OBJECT_CHILDREN_RESP  2087

#define LOCATION2CHANNEL(p, z) ((channel_t)(p)<<32|(channel_t)(z))

#define DBSERVER_CREATE_STORED_OBJECT 1003
#define DBSERVER_CREATE_STORED_OBJECT_RESP 1004
