/*
 * @file swi_mangoh_data_router.h
 *
 * Data router module.
 *
 * This module is the main module for the MangOH data router.
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */
#include "legato.h"
#include "interfaces.h"

#ifndef SWI_MANGOH_DATA_ROUTER_DB_INCLUDE_GUARD
#define SWI_MANGOH_DATA_ROUTER_DB_INCLUDE_GUARD

#define SWI_MANGOH_DATA_ROUTER_SEC_STORE_BASE_NAME          "Database"
#define SWI_MANGOH_DATA_ROUTER_SEC_STORE_MAX_KEYS_LEN	     16384
#define SWI_MANGOH_DATA_ROUTER_SEC_STORE_KEYS_SEPARATOR     ","

#define SWI_MANGOH_DATA_ROUTER_CFG_BASE_NAME                "/Database"
#define SWI_MANGOH_DATA_ROUTER_CFG_MAX_PATH_LEN             128
#define SWI_MANGOH_DATA_ROUTER_CFG_KEY                      "key"
#define SWI_MANGOH_DATA_ROUTER_CFG_TYPE                     "type"
#define SWI_MANGOH_DATA_ROUTER_CFG_VALUE                    "value"
#define SWI_MANGOH_DATA_ROUTER_CFG_TIMESTAMP                "timestamp"

#define SWI_MANGOH_DATA_ROUTER_DB_MAP_NAME                  "WorkflowMgrDB"
#define SWI_MANGOH_DATA_ROUTER_DB_MAP_SIZE                  63

#define SWI_MANGOH_DATA_ROUTER_APP_ID_LEN                   64
#define SWI_MANGOH_DATA_ROUTER_KEY_MAX_LEN                  128
#define SWI_MANGOH_DATA_ROUTER_DATA_MAX_LEN                 128

//------------------------------------------------------------------------------------------------------------------
/**
 * Data Router data value
 */
//------------------------------------------------------------------------------------------------------------------
typedef struct _swi_mangoh_data_router_data_t
{
  dataRouterApi_DataType_t              type;                                               ///< Data type
  char                                  key[SWI_MANGOH_DATA_ROUTER_KEY_MAX_LEN];            ///< Data key
  union {
    char                                sValue[SWI_MANGOH_DATA_ROUTER_DATA_MAX_LEN];        ///< Data string value
    float                               fValue;
    int32_t                             iValue;                                             ///< Data integer value
    bool                                bValue;                                             ///< Data boolean values
  };
  time_t                                timestamp;                                          ///< Data timestamp
} swi_mangoh_data_router_data_t;

//------------------------------------------------------------------------------------------------------------------
/**
 * Data Router database item
 */
//------------------------------------------------------------------------------------------------------------------
typedef struct _swi_mangoh_data_router_dbItem_t
{
  swi_mangoh_data_router_data_t         data;                                               ///< Data value
  le_sls_List_t                         subscribers;                                        ///< Data update subscribers
  dataRouterApi_Storage_t	        storageType;                                        ///< Data storage
} swi_mangoh_data_router_dbItem_t;

//------------------------------------------------------------------------------------------------------------------
/**
 * Data Router database module
 */
//------------------------------------------------------------------------------------------------------------------
typedef struct _swi_mangoh_data_router_db_t
{
  le_hashmap_Ref_t                      database;                                           ///< Data cache
} swi_mangoh_data_router_db_t;

swi_mangoh_data_router_dbItem_t* swi_mangoh_data_router_db_getDataItem(swi_mangoh_data_router_db_t*, const char*);
void swi_mangoh_data_router_db_setStorageType(swi_mangoh_data_router_dbItem_t*, dataRouterApi_Storage_t);
void swi_mangoh_data_router_db_setDataType(swi_mangoh_data_router_dbItem_t*, dataRouterApi_DataType_t);
void swi_mangoh_data_router_db_setBooleanValue(swi_mangoh_data_router_dbItem_t*, bool);
void swi_mangoh_data_router_db_setIntegerValue(swi_mangoh_data_router_dbItem_t*, int32_t);
void swi_mangoh_data_router_db_setFloatValue(swi_mangoh_data_router_dbItem_t*, float);
void swi_mangoh_data_router_db_setStringValue(swi_mangoh_data_router_dbItem_t*, const char*);
void swi_mangoh_data_router_db_setTimestamp(swi_mangoh_data_router_dbItem_t*, uint32_t);

swi_mangoh_data_router_dbItem_t* swi_mangoh_data_router_db_createDataItem(swi_mangoh_data_router_db_t*, const char*);
void swi_mangoh_data_router_db_init(swi_mangoh_data_router_db_t*);
void swi_mangoh_data_router_db_destroy(swi_mangoh_data_router_db_t*);

#endif