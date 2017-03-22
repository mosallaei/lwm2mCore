/**
 * @file objects.h
 *
 * Object manager header file
 *
 *
 * Copyright (C) Sierra Wireless Inc.
 *
 */

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <lwm2mcore/lwm2mcore.h>
#include "liblwm2m.h"

//--------------------------------------------------------------------------------------------------
/** Define entry for the list inside user data structure for list element
 *
 * Example:
 *
 * typedef struct mydata {
 *      DLIST_ENTRY(mydata) list;
 *      int value;
 * } mydata_t;
 *
 * @param[in] type data type of the user data structure.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_ENTRY(type) struct { struct type *p_next, *p_prev; const void *p_head;}

//--------------------------------------------------------------------------------------------------
/** Define a new data type for the list head
 *
 * Example:
 *
 * DLIST_HEAD(mylist_head, mydata) mylist;
 *
 * Which defines a list head variable "mylist" whose type is "struct mylist_head", and the
 * list element consists of "struct mydata" as defined by DLIST_ENTRY() above.
 *
 * @param[in] name name of the list head data type.
 * @param[in] type name of the list element data type.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_HEAD(name, type) struct name{ struct type *p_first, *p_last;}

//--------------------------------------------------------------------------------------------------
/** Macro to initialize the list
 *
 * @param[in] head pointer to the list head.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_INIT(head) ((head)->p_first = (head)->p_last = NULL)

//--------------------------------------------------------------------------------------------------
/** Insert new element into the tail of the list
 *
 * @param[in] head pointer to the list head.
 * @param[in] new_elem element to be inserted.
 * @param[in] field the field name of the user data structure used as link element.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_INSERT_TAIL(head, new_elem, field) do { \
    (new_elem)->field.p_head = (const void *)head; \
    (new_elem)->field.p_next = NULL; \
    (new_elem)->field.p_prev = (head)->p_last; \
    if ((head)->p_last) (head)->p_last->field.p_next = (new_elem); \
    else (head)->p_first = (new_elem); \
    (head)->p_last = (new_elem); \
}while(0)

//--------------------------------------------------------------------------------------------------
/** Return first element from the list
 *
 * @param[in] head pointer to the list head.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_FIRST(head) ((head)->p_first)

//--------------------------------------------------------------------------------------------------
/** Return next element from the list
 *
 * @param[in] pointer to the list element whose next element will be returned.
 * @param[in] field the field name of the user data structure used as link element.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_NEXT(elem, field) ((elem)->field.p_next)

//--------------------------------------------------------------------------------------------------
/** Remove element from the list
 *
 * @param[in] head pointer to the list head.
 * @param[in] elem element to be removed.
 * @param[in] field the field name of the user data structure used as link element.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_REMOVE(head, elem, field) do { \
    if ((elem)->field.p_next) (elem)->field.p_next->field.p_prev = (elem)->field.p_prev; \
    else (head)->p_last = (elem)->field.p_prev; \
    if ((elem)->field.p_prev) (elem)->field.p_prev->field.p_next = (elem)->field.p_next; \
    else (head)->p_first = (elem)->field.p_next; \
} while(0)

//--------------------------------------------------------------------------------------------------
/** Remove element from the head of the list
 *
 * @param[in] head pointer to the list head.
 * @param[in] field the field name of the user data structure used as link element.
 */
//--------------------------------------------------------------------------------------------------
#define DLIST_REMOVE_HEAD(head, field) do { \
    (head)->p_first = (head)->p_first->field.p_next; \
    if ((head)->p_first) (head)->p_first->field.p_prev = NULL; \
    else (head)->p_last = NULL; \
} while(0)

//--------------------------------------------------------------------------------------------------
/**
 * Macro for array size
 */
//--------------------------------------------------------------------------------------------------
#if !defined(ARRAYSIZE)
#define ARRAYSIZE(a) sizeof(a)/sizeof(a[0])
#endif

//--------------------------------------------------------------------------------------------------
/**
 * Maximum buffer length from CoAP
 */
//--------------------------------------------------------------------------------------------------
#define LWM2MCORE_BUFFER_MAX_LEN 1024

//--------------------------------------------------------------------------------------------------
/**
 * Define the server URI max length
 */
//--------------------------------------------------------------------------------------------------
#define LWM2MCORE_SERVER_URI_MAX_LEN    255

//--------------------------------------------------------------------------------------------------
/**
 * Enumeration for LWM2M objects
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_SECURITY_OID          = 0,        ///< Security
    LWM2MCORE_SERVER_OID            = 1,        ///< Server
    LWM2MCORE_ACL_OID               = 2,        ///< Access Control
    LWM2MCORE_DEVICE_OID            = 3,        ///< Device
    LWM2MCORE_CONN_MONITOR_OID      = 4,        ///< Connectivity monitoring
    LWM2MCORE_FIRMWARE_UPDATE_OID   = 5,        ///< Firmware update
    LWM2MCORE_LOCATION_OID          = 6,        ///< Location
    LWM2MCORE_CONN_STATS_OID        = 7,        ///< Connectivity statistics
    LWM2MCORE_SOFTWARE_UPDATE_OID   = 9,        ///< Application update
    LWM2M_SWI_SUBSCRIPTION_OID      = 10241,    ///< Sierra Wireless proprietary object ID:
                                                ///< Subscription
    LWM2M_SWI_EXT_CONN_STATS_OID    = 10242,    ///< Sierra Wireless proprietary object ID: Extended
                                                ///< connectivity statistics
    LWM2M_SWI_SSL_CERTIFS_OID       = 10243     ///< Sierra Wireless proprietary object ID: SSL
                                                ///< certificate
} lwm2mcore_objectEnum_t;

//--------------------------------------------------------------------------------------------------
/**
 * Enumeration for LWM2M object 0 (security) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_SECURITY_SERVER_URI_RID = 0,          ///< LWM2M server URI
    LWM2MCORE_SECURITY_BOOTSTRAP_SERVER_RID,        ///< Bootstrap server (true or false)
    LWM2MCORE_SECURITY_MODE_RID,                    ///< Security mode
    LWM2MCORE_SECURITY_PKID_RID,                    ///< Public key or identity
    LWM2MCORE_SECURITY_SERVER_KEY_RID,              ///< Server public key
    LWM2MCORE_SECURITY_SECRET_KEY_RID,              ///< Secret key
    LWM2MCORE_SECURITY_SMS_SECURITY_MODE_RID,       ///< SMS security mode
    LWM2MCORE_SECURITY_SMS_BINDING_KEY_PAR_RID,     ///< SMS binding key parameters
    LWM2MCORE_SECURITY_SMS_BINDING_SEC_KEY_RID,     ///< SMS binding secret key(s)
    LWM2MCORE_SECURITY_SERVER_SMS_NUMBER_RID,       /// <LWM2M server SMS number
    LWM2MCORE_SECURITY_SERVER_ID_RID,               ///< Short server ID
    LWM2MCORE_SECURITY_CLIENT_HOLD_OFF_TIME_RID     ///< Client hold of time
}lwm2mcore_securityResource_t;

//--------------------------------------------------------------------------------------------------
/**
 * Enumeration for LWM2M object 1 (server) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_SERVER_SHORT_ID_RID = 0,              ///< Server short ID
    LWM2MCORE_SERVER_LIFETIME_RID,                  ///< Server lifetime
    LWM2MCORE_SERVER_DEFAULT_MIN_PERIOD_RID,        ///< Server default minimum period
    LWM2MCORE_SERVER_DEFAULT_MAX_PERIOD_RID,        ///< Server default minimum period
    LWM2MCORE_SERVER_DISABLE_RID,                   ///< Disable the device
    LWM2MCORE_SERVER_DISABLE_TIMEOUT_RID,           ///< Disable timeout
    LWM2MCORE_SERVER_STORE_NOTIF_WHEN_OFFLINE_RID,  ///< Notification storing when disabled
                                                    ///< or offline
    LWM2MCORE_SERVER_BINDING_MODE_RID,              ///< Binding
    LWM2MCORE_SERVER_REG_UPDATE_TRIGGER_RID,        ///< Registration update trigger
}lwm2mcore_serverResource_t;

//--------------------------------------------------------------------------------------------------
/**
* Enumeration for LWM2M object 3 (device) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_DEVICE_MANUFACTURER_RID = 0,          ///< Manufacturer
    LWM2MCORE_DEVICE_MODEL_NUMBER_RID,              ///< Model number
    LWM2MCORE_DEVICE_SERIAL_NUMBER_RID,             ///< Serial number
    LWM2MCORE_DEVICE_FIRMWARE_VERSION_RID,          ///< Firmware version
    LWM2MCORE_DEVICE_REBOOT_RID,                    ///< Reboot the device
    LWM2MCORE_DEVICE_FACTORY_RESET_RID,             ///< Factory reset request
    LWM2MCORE_DEVICE_AVAIL_POWER_SOURCES_RID,       ///< Available power sources
    LWM2MCORE_DEVICE_AVAIL_POWER_VOLTAGES_RID,      ///< Power source voltage
    LWM2MCORE_DEVICE_AVAIL_POWER_CURRENTS_RID,      ///< Power source current
    LWM2MCORE_DEVICE_BATTERY_LEVEL_RID,             ///< Battery Level
    LWM2MCORE_DEVICE_MEMORY_FREE_RID,               ///< Memory free
    LWM2MCORE_DEVICE_ERROR_CODES_RID,               ///< Error code
    LWM2MCORE_DEVICE_RESET_ERROR_CODE_RID,          ///< Reset error code
    LWM2MCORE_DEVICE_CURRENT_TIME_RID,              ///< Current time
    LWM2MCORE_DEVICE_UTC_OFFSET_RID,                ///< UTC offset
    LWM2MCORE_DEVICE_TIMEZONE_RID,                  ///< Timezone
    LWM2MCORE_DEVICE_SUPPORTED_BINDING_MODE_RID,    ///< Supported binding and modes
}lwm2mcore_deviceResource_enum_t;

//--------------------------------------------------------------------------------------------------
/**
* Enumeration for LWM2M object 5 (firmware update) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_FW_UPDATE_PACKAGE_RID = 0,        ///< Package
    LWM2MCORE_FW_UPDATE_PACKAGE_URI_RID,        ///< Package URI
    LWM2MCORE_FW_UPDATE_UPDATE_RID,             ///< Update
    LWM2MCORE_FW_UPDATE_UPDATE_STATE_RID,       ///< State
    LWM2MCORE_FW_UPDATE_SUPPPORTED_OBJ_RID,     ///< Update supported objects
    LWM2MCORE_FW_UPDATE_UPDATE_RESULT_RID,      ///< Update result
    LWM2MCORE_FW_UPDATE_PACKAGE_NAME_RID,       ///< Package name
    LWM2MCORE_FW_UPDATE_PACKAGE_VERSION_RID,    ///< Package version
    LWM2MCORE_FW_UPDATE_PROTO_SUPPORT_RID,      ///< Fw update protocol support
    LWM2MCORE_FW_UPDATE_DELIVERY_METHOD_RID,    ///< Fw update delivery method
}lwm2mcore_fwUpdateResource_t;

//--------------------------------------------------------------------------------------------------
/**
* Enumeration for LWM2M object 9 (software update) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_SW_UPDATE_PACKAGE_NAME_RID = 0,       ///< Package name
    LWM2MCORE_SW_UPDATE_PACKAGE_VERSION_RID,        ///< Package version
    LWM2MCORE_SW_UPDATE_PACKAGE_RID,                ///< Software package (push mode)
    LWM2MCORE_SW_UPDATE_PACKAGE_URI_RID,            ///< Package URI (pull mode)
    LWM2MCORE_SW_UPDATE_INSTALL_RID,                ///< Install software
    LWM2MCORE_SW_UPDATE_CHECKPOINT_RID,             ///< Checkpoint
    LWM2MCORE_SW_UPDATE_UNINSTALL_RID,              ///< Uninstall software
    LWM2MCORE_SW_UPDATE_UPDATE_STATE_RID,           ///< Update state
    LWM2MCORE_SW_UPDATE_UPDATE_SUPPORTED_OBJ_RID,   ///< Update supported objects
    LWM2MCORE_SW_UPDATE_UPDATE_RESULT_RID,          ///< Update result
    LWM2MCORE_SW_UPDATE_ACTIVATE_RID,               ///< Activate software
    LWM2MCORE_SW_UPDATE_DEACTIVATE_RID,             ///< Deactivate software
    LWM2MCORE_SW_UPDATE_ACTIVATION_STATE_RID,       ///< Activation state
    LWM2MCORE_SW_UPDATE_PACKAGE_SETTINGS_RID,       ///< Package settings
    LWM2MCORE_SW_UPDATE_USER_NAME_RID,              ///< User name for pull mode
    LWM2MCORE_SW_UPDATE_PASSWORD_RID,               ///< Password for pull mode
    LWM2MCORE_SW_STATUS_REASON_RID,                 ///< Status
    LWM2MCORE_SW_COMPONENT_LINK_RID,                ///< Reference to software components
    LWM2MCORE_SW_COMPONENT_TREE_LENGTH_RID,         ///< Software component tree length
}lwm2mcore_swUpdateResource_t;

//--------------------------------------------------------------------------------------------------
/**
* Enumeration for LWM2M object 10243 (SSL certificates) resources
 */
//--------------------------------------------------------------------------------------------------
typedef enum
{
    LWM2MCORE_SSL_CERTIFICATE_CERTIF         = 0    ///< SSL certificates
} lwm2mcore_sslCertificateResource_t;

//--------------------------------------------------------------------------------------------------
/*! \struct lwm2m_attribute_t
 *  \brief data structure represent the attribute.
 */
//--------------------------------------------------------------------------------------------------
typedef struct
{
    int pmin;       ///< min value
    int pmax;       ///< max value
    int gt;         ///< greater than
    int lt;         ///< less than
    int st;         ///< step
    int cancel;     ///< cancel observe
    int mask;       ///< bitmask indicates what attributes are set
}lwm2m_attribute_t;

//--------------------------------------------------------------------------------------------------
/*! \struct _lwm2m_resource
 *  \brief data structure reprents a lwm2m resource.
 */
//--------------------------------------------------------------------------------------------------
typedef struct _lwm2mcore_internalResource
{
    DLIST_ENTRY(_lwm2mcore_internalResource) list;  ///< list entry for resource linked list
    uint16_t id;                        ///< resource id
    uint16_t iid;                       ///< resource instance id
    lwm2m_ResourceType_t type;          ///< resource data type
    bool multiple;                      ///< flag indicate if this is single or multiple instances
    lwm2m_attribute_t attr;             ///< resource attributes

    /* operation handler */
    lwm2mcore_ReadCallback_t read;     ///< READ handler
    lwm2mcore_WriteCallback_t write;   ///< WRITE handler
    lwm2mcore_ExecuteCallback_t exec;  ///< EXECUTE handler

    /* used by async notification*/
    char *cache;                        ///< cache value for OBSERVE
}lwm2mcore_internalResource_t;

//--------------------------------------------------------------------------------------------------
/** LWM2M Core resource list data type
 */
//--------------------------------------------------------------------------------------------------
DLIST_HEAD(_lwm2m_resource_list, _lwm2mcore_internalResource);

//--------------------------------------------------------------------------------------------------
/*! \struct _lwm2m_object
 *  \brief data structure reprents a lwm2m object.
 */
//--------------------------------------------------------------------------------------------------
typedef struct _lwm2mcore_internalObject
{
    DLIST_ENTRY(_lwm2mcore_internalObject) list;   ///< list entry for object linked list
    uint16_t id;                                    ///< object id
    uint16_t iid;                                   ///< object instance id
    bool multiple;                                  ///< flag indicate if this is single or multiple
                                                    ///< instances
    lwm2m_attribute_t attr;                         ///< object attributes
    struct _lwm2m_resource_list resource_list;      ///< resource linked list
}lwm2mcore_internalObject_t;

//--------------------------------------------------------------------------------------------------
/**
 * LWM2M Core object list data type
 */
//--------------------------------------------------------------------------------------------------
DLIST_HEAD(_lwm2mcore_objectsList, _lwm2mcore_internalObject);

//--------------------------------------------------------------------------------------------------
/**
 * Function to convert bytes(in network byte order) to integer
 *
 * @return
 *      - converted data
 */
//--------------------------------------------------------------------------------------------------
int64_t BytesToInt
(
    const uint8_t *bytes,
    size_t len
);

//--------------------------------------------------------------------------------------------------
/**
 *  Free the registered objects and resources (LWM2MCore and Wakaama)
 */
//--------------------------------------------------------------------------------------------------
void ObjectsFree
(
    void
);

#endif /* __OBJECTS_H__ */

