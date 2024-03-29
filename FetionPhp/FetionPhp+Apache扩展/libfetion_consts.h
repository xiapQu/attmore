#ifndef LIBFETION_CONSTS_H
#define LIBFETION_CONSTS_H
// 
// define the constants for libfetion libraray   
// RainX <jingxu@alibaba-inc.com/china_1982@163.com>
//


#define LIBFETION_REG_L_EX(c) REGISTER_LONG_CONSTANT(#c, c , CONST_CS | CONST_PERSISTENT); 

#define LIBFETION_REGISTER_CONSTS { \
    LIBFETION_REG_L_EX(FETION_LIL_ENDIAN) \
    LIBFETION_REG_L_EX(FETION_BIG_ENDIAN) \
    LIBFETION_REG_L_EX(FETION_BYTEORDER) \
    LIBFETION_REG_L_EX(FX_EVENT_BASE) \
    LIBFETION_REG_L_EX(FX_EVENT_SPARE) \
    LIBFETION_REG_L_EX(FX_LOGIN_CONNECTING) \
    LIBFETION_REG_L_EX(FX_LOGIN_WAIT_AUTH) \
    LIBFETION_REG_L_EX(FX_LOGIN_AUTH_OK) \
    LIBFETION_REG_L_EX(FX_LOGIN_FAIL) \
    LIBFETION_REG_L_EX(FX_LOGIN_NETWORK_ERROR) \
    LIBFETION_REG_L_EX(FX_LOGIN_UNKOWN_ERROR) \
    LIBFETION_REG_L_EX(FX_LOGIN_UNKOWN_USR) \
    LIBFETION_REG_L_EX(FX_LOGIN_GCL_GETTING) \
    LIBFETION_REG_L_EX(FX_LOGIN_GCL_OK) \
    LIBFETION_REG_L_EX(FX_LOGIN_GCL_FAIL) \
    LIBFETION_REG_L_EX(FX_LOGIN_GP_GETTING) \
    LIBFETION_REG_L_EX(FX_LOGIN_GP_OK) \
    LIBFETION_REG_L_EX(FX_LOGIN_GP_FAIL) \
    LIBFETION_REG_L_EX(FX_LOGIN_OK) \
    LIBFETION_REG_L_EX(FX_LOGIN_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_LOGIN_URI_ERROR) \
    LIBFETION_REG_L_EX(FX_LOGIN_SERVER_ERROR) \
    LIBFETION_REG_L_EX(FX_NEW_MESSAGE) \
    LIBFETION_REG_L_EX(FX_NEW_QUN_MESSAGE) \
    LIBFETION_REG_L_EX(FX_SMS_OK) \
    LIBFETION_REG_L_EX(FX_SMS_FAIL) \
    LIBFETION_REG_L_EX(FX_SMS_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_SMS_UNKOWN_ERROR) \
    LIBFETION_REG_L_EX(FX_DIA_BG_TRYING) \
    LIBFETION_REG_L_EX(FX_DIA_BG_OK) \
    LIBFETION_REG_L_EX(FX_DIA_BG_FAIL) \
    LIBFETION_REG_L_EX(FX_DIA_SEND_OK) \
    LIBFETION_REG_L_EX(FX_DIA_SEND_FAIL) \
    LIBFETION_REG_L_EX(FX_DIA_SEND_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_DIA_UNKOWN_ERROR) \
    LIBFETION_REG_L_EX(FX_STATUS_UNSET) \
    LIBFETION_REG_L_EX(FX_STATUS_ONLINE) \
    LIBFETION_REG_L_EX(FX_STATUS_BUSY) \
    LIBFETION_REG_L_EX(FX_STATUS_OFFLINE) \
    LIBFETION_REG_L_EX(FX_STATUS_AWAY) \
    LIBFETION_REG_L_EX(FX_STATUS_MEETING) \
    LIBFETION_REG_L_EX(FX_STATUS_PHONE) \
    LIBFETION_REG_L_EX(FX_STATUS_DINNER) \
    LIBFETION_REG_L_EX(FX_STATUS_EXTENDED_AWAY) \
    LIBFETION_REG_L_EX(FX_STATUS_NUM_PRIMITIVES) \
    LIBFETION_REG_L_EX(FX_STATUS_WAITING_AUTH) \
    LIBFETION_REG_L_EX(FX_STATUS_REFUSE) \
    LIBFETION_REG_L_EX(FX_STATUS_BLACK) \
    LIBFETION_REG_L_EX(FX_STATUS_MOBILE) \
    LIBFETION_REG_L_EX(FX_ACCOUNT_UPDATA_OK) \
    LIBFETION_REG_L_EX(FX_ADD_GROUP_OK) \
    LIBFETION_REG_L_EX(FX_DEL_GROUP_FAIL) \
    LIBFETION_REG_L_EX(FX_DEL_GROUP_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_RENAME_GROUP_OK) \
    LIBFETION_REG_L_EX(FX_RENAME_GROUP_FAIL) \
    LIBFETION_REG_L_EX(FX_RENAME_GROUP_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_SET_BUDDY_INFO_OK) \
    LIBFETION_REG_L_EX(FX_SET_BUDDY_INFO_FAIL) \
    LIBFETION_REG_L_EX(FX_SET_BUDDY_INFO_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_ADD_BUDDY_OK) \
    LIBFETION_REG_L_EX(FX_SYS_ERR_NETWORK) \
    LIBFETION_REG_L_EX(FX_SYS_DEREGISTERED) \
    LIBFETION_REG_L_EX(FX_SET_STATE_OK) \
    LIBFETION_REG_L_EX(FX_SET_STATE_FAIL) \
    LIBFETION_REG_L_EX(FX_SET_STATE_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_ADD_BLACKLIST_OK) \
    LIBFETION_REG_L_EX(FX_ADD_BLACKLIST_FAIL) \
    LIBFETION_REG_L_EX(FX_ADD_BLACKLIST_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_REMOVE_BLACKLIST_OK) \
    LIBFETION_REG_L_EX(FX_REMOVE_BLACKLIST_FAIL) \
    LIBFETION_REG_L_EX(FX_REMOVE_BLACKLIST_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_DEL_BUDDY_OK) \
    LIBFETION_REG_L_EX(FX_DEL_BUDDY_FAIL) \
    LIBFETION_REG_L_EX(FX_DEL_BUDDY_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_GET_QUNLIST_OK) \
    LIBFETION_REG_L_EX(FX_GET_QUNLIST_FAIL) \
    LIBFETION_REG_L_EX(FX_QUN_GP_OK) \
    LIBFETION_REG_L_EX(FX_QUN_SEND_OK) \
    LIBFETION_REG_L_EX(FX_QUN_SEND_TIMEOUT) \
    LIBFETION_REG_L_EX(FX_QUN_SEND_FAIL) \
    }


#endif  // LIBFETION_CONSTS_H
