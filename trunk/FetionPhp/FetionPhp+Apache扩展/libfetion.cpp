/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: RainX(Jing. Xu) <jingxu@alibaba-inc.com>                     |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"
{
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
}
#include "php_libfetion.h"
#include "libfetion_consts.h"

#include <stdio.h>
#include <assert.h>
#include "libfetion/libfetion.h"


/* If you declare any globals in php_libfetion.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(libfetion)
*/

/* True global resources - no need for thread safety here */
static int le_libfetion;

/* {{{ libfetion_functions[]
 *
 * Every user visible function must have an entry in libfetion_functions[].
 */
// remove the const for compatible with older php version
/* const */  zend_function_entry libfetion_functions[] = {
	PHP_FE(confirm_libfetion_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(fx_init,	NULL)
	PHP_FE(fx_terminate,	NULL)
	PHP_FE(fx_close_network,	NULL)
	PHP_FE(fs_login,	NULL)
	PHP_FE(fx_login,	NULL)
	PHP_FE(fx_set_login_status,	NULL)
	PHP_FE(fx_loginout,	NULL)
	PHP_FE(fx_set_system_msg_cb,	NULL)
	PHP_FE(fx_get_msg,	NULL)
	PHP_FE(fs_send_sms,	NULL)
	PHP_FE(fs_send_sms_by_mobile_no,	NULL)
	PHP_FE(fs_send_sms_to_self,	NULL)
	PHP_FE(fx_send_sms,	NULL)
	PHP_FE(fx_send_sms_to_self,	NULL)
	PHP_FE(fx_send_sms_by_mobile_no,	NULL)
	PHP_FE(fs_begin_dialog,	NULL)
	PHP_FE(fs_dialog_send,	NULL)
	PHP_FE(fs_end_dialog,	NULL)
	PHP_FE(fx_begin_dialog,	NULL)
	PHP_FE(fx_dialog_send,	NULL)
	PHP_FE(fx_end_dialog,	NULL)
	PHP_FE(fx_get_usr_uid,	NULL)
	PHP_FE(fx_get_usr_uri,	NULL)
	PHP_FE(fx_get_usr_mobilenum,	NULL)
	PHP_FE(fx_set_user_state,	NULL)
	PHP_FE(fx_get_user_state,	NULL)
	PHP_FE(fx_get_expirestime,	NULL)
	PHP_FE(fx_data_get_PersonalInfo,	NULL)
	PHP_FE(fx_get_group,	NULL)
/*	PHP_FE(fx_get_account,	NULL) */
	PHP_FE(fx_get_blacklist,	NULL)
	PHP_FE(fx_get_qun,	NULL)
	PHP_FE(fx_get_account_by_id,	NULL)
	PHP_FE(fx_is_pc_user_by_id,	NULL)
	PHP_FE(fx_is_pc_user_by_account,	NULL)
	PHP_FE(fx_is_authed_by_id,	NULL)
	PHP_FE(fx_is_authed_by_account,	NULL)
	PHP_FE(fx_is_InBlacklist_by_id,	NULL)
	PHP_FE(fx_is_InBlacklist_by_account,	NULL)
	PHP_FE(fx_is_on_line_by_id,	NULL)
	PHP_FE(fx_is_on_line_by_account,	NULL)
	PHP_FE(fx_get_online_status_by_id,	NULL)
	PHP_FE(fx_get_online_status_by_account,	NULL)
	PHP_FE(fx_update_account_info_by_id,	NULL)
	PHP_FE(fx_get_account_show_name,	NULL)
	PHP_FE(fx_get_qun_show_name,	NULL)
	PHP_FE(fx_get_account_group_id,	NULL)
	PHP_FE(fs_rename_buddylist,	NULL)
	PHP_FE(fs_delete_buddylist,	NULL)
	PHP_FE(fx_rename_buddylist,	NULL)
	PHP_FE(fx_add_buddylist,	NULL)
	PHP_FE(fx_add_buddy_by_uid,	NULL)
	PHP_FE(fx_add_buddy_by_mobile,	NULL)
	PHP_FE(fx_delete_buddylist,	NULL)
	PHP_FE(fs_set_buddyinfo,	NULL)
	PHP_FE(fx_set_buddyinfo,	NULL)
	PHP_FE(fx_delete_buddy_by_id,	NULL)
	PHP_FE(fx_delete_buddy_by_account,	NULL)
	PHP_FE(fx_addto_blacklist_by_id,	NULL)
	PHP_FE(fx_addto_blacklist_by_account,	NULL)
	PHP_FE(fx_addto_blacklist_by_uri,	NULL)
	PHP_FE(fx_removefrom_blacklist_by_id,	NULL)
	PHP_FE(fx_removefrom_blacklist_by_account,	NULL)
	PHP_FE(fx_removefrom_blacklist_by_uri,	NULL)
	PHP_FE(fx_set_proxy,	NULL)
	PHP_FE(fx_set_unknow_proxy,	NULL)
	PHP_FE(fx_get_proxy,	NULL)
	PHP_FE(fx_setProxyEnabled,	NULL)
	PHP_FE(fx_proxyEnabled,	NULL)
	PHP_FE(fx_msg_no_format,	NULL)
	PHP_FE(fx_get_original_ID,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in libfetion_functions[] */
};
/* }}} */

/* {{{ libfetion_module_entry
 */
zend_module_entry libfetion_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"libfetion",
	libfetion_functions,
	PHP_MINIT(libfetion),
	PHP_MSHUTDOWN(libfetion),
	PHP_RINIT(libfetion),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(libfetion),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(libfetion),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

extern "C"
{
#ifdef COMPILE_DL_LIBFETION
ZEND_GET_MODULE(libfetion)
#endif
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("libfetion.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_libfetion_globals, libfetion_globals)
    STD_PHP_INI_ENTRY("libfetion.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_libfetion_globals, libfetion_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_libfetion_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_libfetion_init_globals(zend_libfetion_globals *libfetion_globals)
{
	libfetion_globals->global_value = 0;
	libfetion_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(libfetion)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	LIBFETION_REGISTER_CONSTS;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(libfetion)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(libfetion)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(libfetion)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(libfetion)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "libfetion support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_libfetion_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_libfetion_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "libfetion", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto bool fx_init()
    */
PHP_FUNCTION(fx_init)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_BOOL(fx_init());
}
/* }}} */

/* {{{ proto void fx_terminate()
    */
PHP_FUNCTION(fx_terminate)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	fx_terminate();
	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool fx_close_network()
    */
PHP_FUNCTION(fx_close_network)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_BOOL(fx_close_network());
}
/* }}} */

/* {{{ proto bool fs_login(string uid, string password)
    */
PHP_FUNCTION(fs_login)
{
	char *uid = NULL;
	char *password = NULL;
	int argc = ZEND_NUM_ARGS();
	int uid_len;
	int password_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "ss", &uid, &uid_len, &password, &password_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_login( uid, password));
}
/* }}} */

/* {{{ proto void fx_login(string uid, string password, string func)
   zval args)    */
PHP_FUNCTION(fx_login)
{
	char *uid = NULL;
	char *password = NULL;
	zval *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int uid_len;
	int password_len;
	zval* args;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "sszz", &uid, &uid_len, &password, &password_len, &func, &args) == FAILURE) 
		return;

	// make it write-safety
	SEPARATE_ZVAL(&args);

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(Z_STRVAL_P(func), Z_STRLEN_P(func));
	event->data = args;
	fx_login(uid, password, &fetion_event_callback , (void*) event);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto void fx_set_login_status(int login_status)
    */
PHP_FUNCTION(fx_set_login_status)
{
	int argc = ZEND_NUM_ARGS();
	long login_status;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &login_status) == FAILURE) 
		return;

	fx_set_login_status(login_status);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto void fx_loginout()
    */
PHP_FUNCTION(fx_loginout)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	fx_loginout();
	RETURN_NULL();
}
/* }}} */

/* {{{ proto void fx_set_system_msg_cb(string func)
   zval  args)    */
PHP_FUNCTION(fx_set_system_msg_cb)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "sz", &func, &func_len, &args) == FAILURE) 
		return;

	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	fx_set_system_msg_cb(fetion_event_callback, (void*)event);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto array fx_get_msg(long uid)
    */
PHP_FUNCTION(fx_get_msg)
{
	int argc = ZEND_NUM_ARGS();
	long uid;
	Fetion_MSG * msg;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &uid) == FAILURE) 
		return;

	
	array_init(return_value);
	msg = fx_get_msg(uid);
	// set it to one hash table
	add_assoc_long(return_value, "uid", msg->uid);
	if (msg->message) add_assoc_string(return_value, "message", msg->message, 1);
	if (msg->msgformat) add_assoc_string(return_value, "msgformat", msg->msgformat, 1);
	add_assoc_long(return_value, "ext_id", msg->ext_id);
}
/* }}} */

/* {{{ proto bool fs_send_sms(long who, string message)
    */
PHP_FUNCTION(fs_send_sms)
{
	char *message = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;
	long who;

	if (zend_parse_parameters(argc TSRMLS_CC, "ls", &who, &message, &message_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_send_sms(who, message ));
}
/* }}} */

/* {{{ proto bool fs_send_sms_by_mobile_no(string mobile_no, string message)
    */
PHP_FUNCTION(fs_send_sms_by_mobile_no)
{
	char *mobile_no = NULL;
	char *message = NULL;
	int argc = ZEND_NUM_ARGS();
	int mobile_no_len;
	int message_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "ss", &mobile_no, &mobile_no_len, &message, &message_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_send_sms_by_mobile_no(mobile_no, message ));
}
/* }}} */

/* {{{ proto bool fs_send_sms_to_self(string message)
    */
PHP_FUNCTION(fs_send_sms_to_self)
{
	char *message = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &message, &message_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_send_sms_to_self(message));
}
/* }}} */

/* {{{ proto int fx_send_sms(long who, string message, string func)
   zval args) */
PHP_FUNCTION(fx_send_sms)
{
	char *message = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;
	int func_len;
	long who;
	zval* args =NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "lssz", &who, &message, &message_len, &func, &func_len, &args) == FAILURE) 
		return;

	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	fx_send_sms(who, message, &fetion_event_callback, (void*) args);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto int fx_send_sms_to_self(string message, string func)
   zval args) */
PHP_FUNCTION(fx_send_sms_to_self)
{
	char *message = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;
	int func_len;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "ssz", &message, &message_len, &func, &func_len, &args) == FAILURE) 
		return;
	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	fx_send_sms_to_self(message, &fetion_event_callback, (void*) event);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto int fx_send_sms_by_mobile_no(string mobile_no, string message, string func)
   zval args) */
PHP_FUNCTION(fx_send_sms_by_mobile_no)
{
	char *mobile_no = NULL;
	char *message = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int mobile_no_len;
	int message_len;
	int func_len;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "sssz", &mobile_no, &mobile_no_len, &message, &message_len, &func, &func_len, &args) == FAILURE) 
		return;
	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	fx_send_sms_by_mobile_no(mobile_no, message, &fetion_event_callback, (void*) event);
	RETURN_NULL();


}
/* }}} */

/* {{{ proto bool fs_begin_dialog(long who)
    */
PHP_FUNCTION(fs_begin_dialog)
{
	int argc = ZEND_NUM_ARGS();
	long who;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &who) == FAILURE) 
		return;

	RETURN_BOOL(fs_begin_dialog(who));
}
/* }}} */

/* {{{ proto bool fs_dialog_send(long who, string message)
    */
PHP_FUNCTION(fs_dialog_send)
{
	char *message = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;
	long who;

	if (zend_parse_parameters(argc TSRMLS_CC, "ls", &who, &message, &message_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_dialog_send(who, message));
}
/* }}} */

/* {{{ proto void fs_end_dialog(long who)
    */
PHP_FUNCTION(fs_end_dialog)
{
	int argc = ZEND_NUM_ARGS();
	long who;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &who) == FAILURE) 
		return;

	fs_end_dialog(who);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto int fx_begin_dialog(long who, string func)
   zval args) */
PHP_FUNCTION(fx_begin_dialog)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	long who;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "lsz", &who, &func, &func_len, &args) == FAILURE) 
		return;
	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG( fx_begin_dialog(who, &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto int fx_dialog_send(long who, string message, string func)
   zval args) */
PHP_FUNCTION(fx_dialog_send)
{
	char *message = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int message_len;
	int func_len;
	long who;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "lss", &who, &message, &message_len, &func, &func_len, &args) == FAILURE) 
		return;
	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG (fx_dialog_send(who, message,  &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto void fx_end_dialog(long who)
    */
PHP_FUNCTION(fx_end_dialog)
{
	int argc = ZEND_NUM_ARGS();
	long who;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &who) == FAILURE) 
		return;

	fx_end_dialog(who);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto string fx_get_usr_uid()
    */
PHP_FUNCTION(fx_get_usr_uid)
{
	const char* uid;
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	uid = fx_get_usr_uid();
	RETURN_STRING(estrdup(uid), 1);
}
/* }}} */

/* {{{ proto string fx_get_usr_uri()
    */
PHP_FUNCTION(fx_get_usr_uri)
{
	const char* uri;
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	uri = fx_get_usr_uri();
	RETURN_STRING(estrdup(uri), 1);
}
/* }}} */

/* {{{ proto string fx_get_usr_mobilenum()
    */
PHP_FUNCTION(fx_get_usr_mobilenum)
{
	const char * mobilenum;
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	mobilenum = fx_get_usr_mobilenum();
	RETURN_STRING(estrdup(mobilenum), 1);
}
/* }}} */

/* {{{ proto int fx_set_user_state(int state, string desc, string func)
   zval args) */
PHP_FUNCTION(fx_set_user_state)
{
	char *desc = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int desc_len;
	int func_len;
	long state;
	zval* args = NULL;
	libfetion_event_t* event;

	if (zend_parse_parameters(argc TSRMLS_CC, "lssz", &state, &desc, &desc_len, &func, &func_len, &args) == FAILURE) 
		return;
	// make it write-safety
	SEPARATE_ZVAL(&args);
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG (fx_set_user_state(state, desc,  &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto int fx_get_user_state()
    */
PHP_FUNCTION(fx_get_user_state)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_LONG(fx_get_user_state());
}
/* }}} */

/* {{{ proto int fx_get_expirestime()
    */
PHP_FUNCTION(fx_get_expirestime)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_LONG(fx_get_expirestime());
}
/* }}} */

/* {{{ proto array fx_data_get_PersonalInfo()
    */
PHP_FUNCTION(fx_data_get_PersonalInfo)
{
	const Fetion_Personal* personal;
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	array_init(return_value);
	personal = fx_data_get_PersonalInfo();
	// fill it to hashtable
	if ( LIBFETION_PHP_DEBUG)
	{
		//printf("profile:%s\n", personal->profile );
		//printf("name :%s\n", personal->name );
		//printf("mobile_no :%s\n", personal->mobile_no );
	}
	if(personal->nickname)add_assoc_string(return_value, "nickname", personal->nickname, 1);
	if(personal->impresa)add_assoc_string(return_value, "impresa", personal->impresa, 1);
	add_assoc_long(return_value, "gender", personal->gender);
	if(personal->nation)add_assoc_string(return_value, "nation", personal->nation, 1);
	if(personal->province)add_assoc_string(return_value, "province", personal->province, 1);
	add_assoc_long(return_value, "city", personal->city);
	add_assoc_long(return_value, "portrait_crc", personal->portrait_crc);
	if(personal->mobile_no)add_assoc_string(return_value, "mobile_no", personal->mobile_no, 1);
	if(personal->name)add_assoc_string(return_value, "name", personal->name, 1);
	if(personal->birth_date)add_assoc_string(return_value, "birth_date", personal->birth_date, 1);
	add_assoc_long(return_value, "lunar_animal", personal->lunar_animal);
	add_assoc_long(return_value, "horoscope", personal->horoscope);
	if(personal->profile) add_assoc_string(return_value, "profile", personal->profile, 1);
	add_assoc_long(return_value, "blood_type", personal->blood_type);
	if(personal->occupation)add_assoc_string(return_value, "occupation", personal->occupation, 1);
	if(personal->hobby)add_assoc_string(return_value, "hobby", personal->hobby, 1);
	if(personal->personal_email)add_assoc_string(return_value, "personal_email", personal->personal_email, 1);
	if(personal->work_email)add_assoc_string(return_value, "work_email", personal->work_email, 1);
	if(personal->other_email)add_assoc_string(return_value, "other_email", personal->other_email, 1);
	add_assoc_long(return_value, "primary_email", personal->primary_email);
	if(personal->job_title)add_assoc_string(return_value, "job_title", personal->job_title, 1);
	if(personal->home_phone)add_assoc_string(return_value, "home_phone", personal->home_phone, 1);
	if(personal->work_phone)add_assoc_string(return_value, "work_phone", personal->work_phone, 1);
	if(personal->other_phone)add_assoc_string(return_value, "other_phone", personal->other_phone, 1);
	if(personal->company)add_assoc_string(return_value, "company", personal->company, 1);
	if(personal->company_website)add_assoc_string(return_value, "company_website", personal->company_website, 1);
	add_assoc_long(return_value, "match_enabled", personal->match_enabled);
}
/* }}} */

/* {{{ proto array fx_get_group()
 * an array of Fetion_Group structure
 * Fetion_Group {
 *  int 	id
 *  char * 	name
 * }
    */
PHP_FUNCTION(fx_get_group)
{
	Fetion_Group *group = NULL;
	const DList *tmp = fx_get_group();	
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	array_init(return_value);
	while (tmp)
	{
	  group = (Fetion_Group *) tmp->data;
	  if(group) {
		  zval* g;
		  MAKE_STD_ZVAL(g);
		  array_init(g);
		  add_assoc_long(g, "id", group->id); 
		  add_assoc_string(g, "name", group->name, 1); 
		  // add to zval
		  add_next_index_zval ( return_value, g);
	  }
	  tmp = d_list_next(tmp);
	}
}
/* }}} *

/* REMOVED IN 1.0 version
 *
 * {{{ proto array fx_get_account()
        typedef struct _fetion_account {
        long id; //619369**
        char *uri; //619369**@fetion.com.cn;p=2082
        char *local_name;
        char *buddy_lists;
        int group_id;
        int relation_status;
        int online_notify;
        int status_code; //200 or 400
        int online_status;   //sa event.h USER STATUS Event
        long portrait_crc;
        Fetion_Personal *personal;
        Ftion_USER_TYPE usr_type; //PC or moblie
    }Fetion_Account;

PHP_FUNCTION(fx_get_account)
{
	Fetion_Account *account = NULL;
	const DList *tmp = (const DList *)fx_get_account();
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	array_init(return_value);
	while(tmp) 
	{
	  if( account =(Fetion_Account *)tmp->data ) {
		  zval* g;
		  zval* p;
		  MAKE_STD_ZVAL(g);
		  MAKE_STD_ZVAL(p);
		  array_init(g);
		  array_init(p);
		  add_assoc_long(g, "id", account->id); 
		  if (account->uri) add_assoc_string(g, "uri", account->uri, 1); 
		  if (account->local_name) add_assoc_string(g, "local_name", account->local_name, 1); 
		  if (account->buddy_lists) add_assoc_string(g, "buddy_lists", account->buddy_lists, 1); 
		  add_assoc_long(g, "group_id", account->group_id); 
		  add_assoc_long(g, "relation_status", account->relation_status); 
		  add_assoc_long(g, "online_notify", account->online_notify); 
		  add_assoc_long(g, "status_code", account->status_code); 
		  add_assoc_long(g, "online_status", account->online_status); 
		  add_assoc_long(g, "portrait_crc", account->portrait_crc); 
		  add_assoc_long(g, "usr_type", account->usr_type); 
		  if(account->personal)
		  {
			if(account->personal->nickname)add_assoc_string(p, "nickname", account->personal->nickname, 1);
			if(account->personal->impresa)add_assoc_string(p, "impresa", account->personal->impresa, 1);
			add_assoc_long(p, "gender", account->personal->gender);
			if(account->personal->nation)add_assoc_string(p, "nation", account->personal->nation, 1);
			if(account->personal->province)add_assoc_string(p, "province", account->personal->province, 1);
			add_assoc_long(p, "city", account->personal->city);
			add_assoc_long(p, "portrait_crc", account->personal->portrait_crc);
			if(account->personal->mobile_no)add_assoc_string(p, "mobile_no", account->personal->mobile_no, 1);
			if(account->personal->name)add_assoc_string(p, "name", account->personal->name, 1);
			if(account->personal->birth_date)add_assoc_string(p, "birth_date", account->personal->birth_date, 1);
			add_assoc_long(p, "lunar_animal", account->personal->lunar_animal);
			add_assoc_long(p, "horoscope", account->personal->horoscope);
			if(account->personal->profile) add_assoc_string(p, "profile", account->personal->profile, 1);
			add_assoc_long(p, "blood_type", account->personal->blood_type);
			if(account->personal->occupation)add_assoc_string(p, "occupation", account->personal->occupation, 1);
			if(account->personal->hobby)add_assoc_string(p, "hobby", account->personal->hobby, 1);
			if(account->personal->personal_email)add_assoc_string(p, "account->personal_email", account->personal->personal_email, 1);
			if(account->personal->work_email)add_assoc_string(p, "work_email", account->personal->work_email, 1);
			if(account->personal->other_email)add_assoc_string(p, "other_email", account->personal->other_email, 1);
			add_assoc_long(p, "primary_email", account->personal->primary_email);
			if(account->personal->job_title)add_assoc_string(p, "job_title", account->personal->job_title, 1);
			if(account->personal->home_phone)add_assoc_string(p, "home_phone", account->personal->home_phone, 1);
			if(account->personal->work_phone)add_assoc_string(p, "work_phone", account->personal->work_phone, 1);
			if(account->personal->other_phone)add_assoc_string(p, "other_phone", account->personal->other_phone, 1);
			if(account->personal->company)add_assoc_string(p, "company", account->personal->company, 1);
			if(account->personal->company_website)add_assoc_string(p, "company_website", account->personal->company_website, 1);
			add_assoc_long(p, "match_enabled", account->personal->match_enabled);
			add_assoc_zval(g, "personal", p);
		  }  
		  // add to zval
		  add_next_index_zval ( return_value, g);
	  }
	  tmp = d_list_next(tmp);
	}
}
    */
/* }}} */

/* {{{ proto array fx_get_blacklist()
    */
PHP_FUNCTION(fx_get_blacklist)
{
	Fetion_Black *black = NULL;
	const DList *tmp = fx_get_blacklist();

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	array_init(return_value);

	while(tmp) 
	  {
		if( black =(Fetion_Black *)tmp->data ) {
			zval* g;
			MAKE_STD_ZVAL(g);
			array_init(g);
			add_assoc_long(g, "uid", black->uid);
			if (black->uri) add_assoc_string(g, "uri", black->uri, 1);
			if (black->local_name) add_assoc_string(g, "local_name", black->local_name, 1);
			
			add_next_index_zval(return_value, g);
		}
		tmp = d_list_next(tmp);
	  }
}
/* }}} */

/* {{{ proto array fx_get_qun()
    */
PHP_FUNCTION(fx_get_qun)
{
	Fetion_Qun *fqun = NULL;
	const DList *tmp = fx_get_qun();

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	array_init(return_value);
	while(tmp)
	{
		fqun = (Fetion_Qun *) tmp->data;
		if(fqun) {
			Fetion_QunInfo* qun;
			zval *g, *members;
			MAKE_STD_ZVAL(g);
			MAKE_STD_ZVAL(members);
			array_init(g);
			array_init(members);

			add_assoc_long(return_value, "id", fqun->id);
			if (fqun->uri) add_assoc_string(return_value, "uri", fqun->uri, 1);
			add_assoc_long(return_value, "identity", fqun->identity);
			
			qun = fqun->quninfo;

			if (qun->uri) add_assoc_string(g, "uri", qun->uri, 1);
			if (qun->name) add_assoc_string(g, "name", qun->name, 1);
			if (qun->introduce) add_assoc_string(g, "introduce", qun->introduce, 1);
			if (qun->bulletin) add_assoc_string(g, "bulletin", qun->bulletin, 1);
			if (qun->group_activity) add_assoc_string(g, "group_activity", qun->group_activity, 1);
			add_assoc_long(g, "group_attributes_version", qun->group_attributes_version);
			add_assoc_long(g, "category", qun->category);
			add_assoc_long(g, "portrait_crc", qun->portrait_crc);
			add_assoc_long(g, "searchable", qun->searchable);
			add_assoc_long(g, "current_member_count", qun->current_member_count);
			add_assoc_long(g, "limit_member_count", qun->limit_member_count);
			
			DList *tmp1 = qun->QunMember;

			while(tmp1)
			  {
				zval* member;
				MAKE_STD_ZVAL(member);
				array_init(member);
				Fetion_QunMember* m = (Fetion_QunMember *) tmp1->data;
				if(m) {
					if (m->uri) add_assoc_string(member, "uri", m->uri, 1);
					if (m->nickname) add_assoc_string(member, "nickname", m->nickname, 1);
					if (m->iicnickname) add_assoc_string(member, "iicnickname", m->iicnickname, 1);
					if (m->client_type) add_assoc_string(member, "client_type", m->client_type, 1);
					add_assoc_long(member, "id", m->id);
					add_assoc_long(member, "identity", m->identity);
					add_assoc_long(member, "state", m->state);
					
					add_next_index_zval(members, member);
				}
				tmp1 = d_list_next(tmp1);
			  }
			add_assoc_zval(g, "QunMember", members);

			add_assoc_zval(return_value, "quninfo", g);
		}
		tmp = d_list_next(tmp);
	}

}
/* }}} */

/* {{{ proto array fx_get_account_by_id(long id)
    */
PHP_FUNCTION(fx_get_account_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;
	const Fetion_Account * account;
	const Fetion_Personal * personal;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	array_init(return_value);

	account = fx_get_account_by_id(id);
	if (account)
	{
		add_assoc_long(return_value, "id", account->id);
		add_assoc_long(return_value, "online_status", account->online_status);
		if (account->local_name) add_assoc_string(return_value, "local_name", account->local_name, 1);
		if (account->buddy_lists) add_assoc_string(return_value, "buddy_lists", account->buddy_lists, 1);
		personal = account->personal;
		if (personal)
		{
		  zval* p;
		  MAKE_STD_ZVAL(p);
		  array_init(p);
		  if(personal->nickname)add_assoc_string(p, "nickname", personal->nickname, 1);
		  if(personal->impresa)add_assoc_string(p, "impresa", personal->impresa, 1);
		  add_assoc_long(p, "gender", personal->gender);
		  if(personal->nation)add_assoc_string(p, "nation", personal->nation, 1);
		  if(personal->province)add_assoc_string(p, "province", personal->province, 1);
		  add_assoc_long(p, "city", personal->city);
		  add_assoc_long(p, "portrait_crc", personal->portrait_crc);
		  if(personal->mobile_no)add_assoc_string(p, "mobile_no", personal->mobile_no, 1);
		  if(personal->name)add_assoc_string(p, "name", personal->name, 1);
		  if(personal->birth_date)add_assoc_string(p, "birth_date", personal->birth_date, 1);
		  add_assoc_long(p, "lunar_animal", personal->lunar_animal);
		  add_assoc_long(p, "horoscope", personal->horoscope);
		  if(personal->profile) add_assoc_string(p, "profile", personal->profile, 1);
		  add_assoc_long(p, "blood_type", personal->blood_type);
		  if(personal->occupation)add_assoc_string(p, "occupation", personal->occupation, 1);
		  if(personal->hobby)add_assoc_string(p, "hobby", personal->hobby, 1);
		  if(personal->personal_email)add_assoc_string(p, "personal_email", personal->personal_email, 1);
		  if(personal->work_email)add_assoc_string(p, "work_email", personal->work_email, 1);
		  if(personal->other_email)add_assoc_string(p, "other_email", personal->other_email, 1);
		  add_assoc_long(p, "primary_email", personal->primary_email);
		  if(personal->job_title)add_assoc_string(p, "job_title", personal->job_title, 1);
		  if(personal->home_phone)add_assoc_string(p, "home_phone", personal->home_phone, 1);
		  if(personal->work_phone)add_assoc_string(p, "work_phone", personal->work_phone, 1);
		  if(personal->other_phone)add_assoc_string(p, "other_phone", personal->other_phone, 1);
		  if(personal->company)add_assoc_string(p, "company", personal->company, 1);
		  if(personal->company_website)add_assoc_string(p, "company_website", personal->company_website, 1);
		  add_assoc_long(p, "match_enabled", personal->match_enabled);

		  add_assoc_zval(return_value, "personal", p);
		}
	}
}
/* }}} */

/* {{{ proto bool fx_is_pc_user_by_id(long id)
    */
PHP_FUNCTION(fx_is_pc_user_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_BOOL(fx_is_pc_user_by_id(id));
}
/* }}} */

/* {{{ proto bool fx_is_pc_user_by_account(array account)
    */
PHP_FUNCTION(fx_is_pc_user_by_account)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_BOOL(fx_is_pc_user_by_id(id));
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto int fx_is_authed_by_id(long id)
    */
PHP_FUNCTION(fx_is_authed_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_LONG(fx_is_authed_by_id(id));
}
/* }}} */

/* {{{ proto int fx_is_authed_by_account(array account)
    */
PHP_FUNCTION(fx_is_authed_by_account)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_BOOL(fx_is_authed_by_id(id));
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto bool fx_is_InBlacklist_by_id(long id)
    */
PHP_FUNCTION(fx_is_InBlacklist_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_BOOL(fx_is_InBlacklist_by_id(id));
}
/* }}} */

/* {{{ proto bool fx_is_InBlacklist_by_account(array account)
    */
PHP_FUNCTION(fx_is_InBlacklist_by_account)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_BOOL(fx_is_InBlacklist_by_id(id));
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto bool fx_is_on_line_by_id(long id)
    */
PHP_FUNCTION(fx_is_on_line_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_BOOL(fx_is_on_line_by_id(id));
}
/* }}} */

/* {{{ proto bool fx_is_on_line_by_account(array account)
    */
PHP_FUNCTION(fx_is_on_line_by_account)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_BOOL(fx_is_on_line_by_id(id));
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto int fx_get_online_status_by_id(long uid)
    */
PHP_FUNCTION(fx_get_online_status_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long uid;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &uid) == FAILURE) 
		return;

	RETURN_LONG(fx_get_online_status_by_id(uid));
}
/* }}} */

/* {{{ proto int fx_get_online_status_by_account(array account)
    */
PHP_FUNCTION(fx_get_online_status_by_account)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_LONG(-1);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_LONG(fx_get_online_status_by_id(id));
	}
	RETURN_BOOL(-1);

}
/* }}} */

/* {{{ proto void fx_update_account_info_by_id(long id)
    */
PHP_FUNCTION(fx_update_account_info_by_id)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;
	fx_update_account_info_by_id(id);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto string fx_get_account_show_name(array account)
    */
PHP_FUNCTION(fx_get_account_show_name)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "local_name", sizeof("local_name"), (void **)&ppval) == SUCCESS)
	{
	  	 char* local_name;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_string_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 local_name = Z_STRVAL_PP(ppval);
		 RETURN_STRING(local_name, 1);
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto string fx_get_qun_show_name(array qun)
    */
PHP_FUNCTION(fx_get_qun_show_name)
{
	int argc = ZEND_NUM_ARGS();
	zval *qun = NULL;
	zval** ppval = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &qun) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(qun), "name", sizeof("name"), (void **)&ppval) == SUCCESS)
	{
	  	 char* name;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_string_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_BOOL(false);
		 }

		 name = Z_STRVAL_PP(ppval);
		 RETURN_STRING(name, 1);
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto int fx_get_account_group_id(array account)
    */
PHP_FUNCTION(fx_get_account_group_id)
{
	int argc = ZEND_NUM_ARGS();
	zval *account = NULL;
	zval** ppval = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "a", &account) == FAILURE) 
		return;

	if (zend_hash_find(Z_ARRVAL_P(account), "group_id", sizeof("group_id"), (void **)&ppval) == SUCCESS)
	{
	  	 long group_id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_LONG(-1);
		 }

		 group_id = Z_LVAL_PP(ppval);
		 RETURN_LONG(group_id);
	}
	RETURN_BOOL(false);
}
/* }}} */

/* {{{ proto bool fs_rename_buddylist(int id, string name)
    */
PHP_FUNCTION(fs_rename_buddylist)
{
	char *name = NULL;
	int argc = ZEND_NUM_ARGS();
	int name_len;
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "ls", &id, &name, &name_len) == FAILURE) 
		return;

	RETURN_BOOL( fs_rename_buddylist(id, name));
}
/* }}} */

/* {{{ proto bool fs_delete_buddylist(int id)
    */
PHP_FUNCTION(fs_delete_buddylist)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_BOOL( fs_delete_buddylist(id));
}
/* }}} */

/* {{{ proto int fx_rename_buddylist(int id, string name, string func, mixed args)
   *args) */
PHP_FUNCTION(fx_rename_buddylist)
{
	char *name = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int name_len;
	int func_len;
	long id;
	zval * args= NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lssz", &id, &name, &name_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG (fx_rename_buddylist(id, name,  &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto int fx_add_buddylist(string name, string func, mixed args)
    */
PHP_FUNCTION(fx_add_buddylist)
{
	char *name = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int name_len;
	int func_len;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "ssz", &name, &name_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG (fx_add_buddylist(name,  &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto int fx_add_buddy_by_uid(string uid, string local_name, int groupid, string desc, string func, mixed args)
    */
PHP_FUNCTION(fx_add_buddy_by_uid)
{
	char *uid = NULL;
	char *local_name = NULL;
	char *desc = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int uid_len;
	int local_name_len;
	int desc_len;
	int func_len;
	long groupid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "sslssz", &uid, &uid_len, &local_name, &local_name_len, &groupid, &desc, &desc_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrdup(func);
	event->data = args;
	RETURN_LONG (fx_add_buddy_by_uid(uid, local_name, groupid, desc, &fetion_event_callback, (void*) event) );
}
/* }}} */

/* {{{ proto int fx_add_buddy_by_mobile(string mobile, string local_name, int groupid, string desc, string func, mixed args)
    */
PHP_FUNCTION(fx_add_buddy_by_mobile)
{
	char *mobile = NULL;
	char *local_name = NULL;
	char *desc = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int mobile_len;
	int local_name_len;
	int desc_len;
	int func_len;
	long groupid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "sslssz", &mobile, &mobile_len, &local_name, &local_name_len, &groupid, &desc, &desc_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG(fx_add_buddy_by_mobile(mobile, local_name, groupid, desc, &fetion_event_callback,  (void*) event));
}
/* }}} */

/* {{{ proto int fx_delete_buddylist(int id, string func, mixed args)
    */
PHP_FUNCTION(fx_delete_buddylist)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	long id;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lsz", &id, &func, &func_len, &args) == FAILURE) 
		return;
	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG(fx_delete_buddylist(id, &fetion_event_callback,  (void*) event));
}
/* }}} */

/* {{{ proto bool fs_set_buddyinfo(long uid, string localname)
    */
PHP_FUNCTION(fs_set_buddyinfo)
{
	char *localname = NULL;
	int argc = ZEND_NUM_ARGS();
	int localname_len;
	long uid;

	if (zend_parse_parameters(argc TSRMLS_CC, "ls", &uid, &localname, &localname_len) == FAILURE) 
		return;

	RETURN_BOOL(fs_set_buddyinfo( uid, localname ));
}
/* }}} */

/* {{{ proto int fx_set_buddyinfo(long uid, string localname, string func, mixed args)
    */
PHP_FUNCTION(fx_set_buddyinfo)
{
	char *localname = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int localname_len;
	int func_len;
	long uid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lssz", &uid, &localname, &localname_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG(fx_set_buddyinfo (uid, localname, &fetion_event_callback,  (void*) event));
}
/* }}} */

/* {{{ proto int fx_delete_buddy_by_id(long uid, string func, mixed args)
    */
PHP_FUNCTION(fx_delete_buddy_by_id)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	long uid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lsz", &uid, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG(fx_delete_buddy_by_id (uid, &fetion_event_callback,  (void*) event));
}
/* }}} */

/* {{{ proto int fx_delete_buddy_by_account(array account, string func, mixed args)
    */
PHP_FUNCTION(fx_delete_buddy_by_account)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	zval *account = NULL;
	zval *args = NULL;
	zval** ppval = NULL;
	libfetion_event_t* event = NULL;


	if (zend_parse_parameters(argc TSRMLS_CC, "asz", &account, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_LONG(0);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_LONG(fx_delete_buddy_by_id (id, &fetion_event_callback,  (void*) event));
	}

	RETURN_LONG(0);
}
/* }}} */

/* {{{ proto int fx_addto_blacklist_by_id(long uid, string func, mixed args)
    */
PHP_FUNCTION(fx_addto_blacklist_by_id)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	long uid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lsz", &uid, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG (fx_addto_blacklist_by_id(uid, &fetion_event_callback, (void*) event));
}
/* }}} */

/* {{{ proto int fx_addto_blacklist_by_account(array account, string func, mixed args)
    */
PHP_FUNCTION(fx_addto_blacklist_by_account)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	zval *account = NULL;
	zval *args = NULL;
	zval** ppval = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "asz", &account, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_LONG(0);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_LONG(fx_addto_blacklist_by_id (id, &fetion_event_callback,  (void*) event));
	}

	RETURN_LONG(0);
}
/* }}} */

/* {{{ proto int fx_addto_blacklist_by_uri(string uri, string func, mixed args)
    */
PHP_FUNCTION(fx_addto_blacklist_by_uri)
{
	char *uri = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int uri_len;
	int func_len;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "ssz", &uri, &uri_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;
	RETURN_LONG( fx_addto_blacklist_by_uri( uri, &fetion_event_callback, (void*) event));
}
/* }}} */

/* {{{ proto int fx_removefrom_blacklist_by_id(long uid, string func, mixed args)
    */
PHP_FUNCTION(fx_removefrom_blacklist_by_id)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	long uid;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "lsz", &uid, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG( fx_removefrom_blacklist_by_id( uid, &fetion_event_callback, (void*)event));
}
/* }}} */

/* {{{ proto int fx_removefrom_blacklist_by_account(array account, string func, mixed args)
    */
PHP_FUNCTION(fx_removefrom_blacklist_by_account)
{
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int func_len;
	zval *account = NULL;
	zval *args = NULL;
	zval** ppval = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "asz", &account, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	if (zend_hash_find(Z_ARRVAL_P(account), "id", sizeof("id"), (void **)&ppval) == SUCCESS)
	{
	  	 long id;

		 if (Z_TYPE_PP(ppval) == IS_STRING || Z_TYPE_PP(ppval) == IS_LONG )
		 {
		   convert_to_long_ex(ppval);
		 }
		 else
		 { 
		   php_error(E_WARNING, "wrong param format");
		   RETURN_LONG(0);
		 }

		 id = Z_LVAL_PP(ppval);
		 RETURN_LONG(fx_removefrom_blacklist_by_id (id, &fetion_event_callback,  (void*) event));
	}

	RETURN_LONG(0);
}
/* }}} */

/* {{{ proto int fx_removefrom_blacklist_by_uri(string uri, string func, mixed args)
    */
PHP_FUNCTION(fx_removefrom_blacklist_by_uri)
{
	char *uri = NULL;
	char *func = NULL;
	int argc = ZEND_NUM_ARGS();
	int uri_len;
	int func_len;
	zval *args = NULL;
	libfetion_event_t* event = NULL;

	if (zend_parse_parameters(argc TSRMLS_CC, "ssz", &uri, &uri_len, &func, &func_len, &args) == FAILURE) 
		return;

	// construct event data
	event = (libfetion_event_t*) emalloc( sizeof(libfetion_event_t) ); 
	event->callback = estrndup(func, func_len);
	event->data = args;

	RETURN_LONG( fx_removefrom_blacklist_by_uri( uri, &fetion_event_callback, (void*)event));
}
/* }}} */

/* {{{ proto bool fx_set_proxy(string proxy)
    */
PHP_FUNCTION(fx_set_proxy)
{
	zval *proxy = NULL;
	int argc = ZEND_NUM_ARGS();
	zval** ppval;
	PROXY_ITEM* item;

	/*
typedef struct _PROXY_ITEM{
    \** Proxy host. *\
    char *host;
    \** Proxy port. *\
    char *port;
    \** User name. *\
    char *name;
    \** User password. *\
    char *pwd;
    \** Proxy type, which can be HTTP, SOCKS4, or SOCKS5. *\
    PROXY_TYPE  type;
}PROXY_ITEM;
	 */
	if (zend_parse_parameters(argc TSRMLS_CC, "a", &proxy) == FAILURE) 
		return;
	if (zend_hash_find(Z_ARRVAL_P(proxy), "host", sizeof("host"), (void **)&ppval) != SUCCESS)
	{
	  RETURN_BOOL(0);
	}
	convert_to_string_ex(ppval);
	item->host = estrndup( Z_STRVAL_PP ( ppval) , Z_STRLEN_PP(ppval));

	if (zend_hash_find(Z_ARRVAL_P(proxy), "port", sizeof("port"), (void **)&ppval) != SUCCESS)
	{
	  RETURN_BOOL(0);
	}
	convert_to_string_ex(ppval);
	item->port = estrndup( Z_STRVAL_PP ( ppval) , Z_STRLEN_PP(ppval));

	if (zend_hash_find(Z_ARRVAL_P(proxy), "name", sizeof("name"), (void **)&ppval) != SUCCESS)
	{
	  RETURN_BOOL(0);
	}
	convert_to_string_ex(ppval);
	item->name = estrndup( Z_STRVAL_PP ( ppval) , Z_STRLEN_PP(ppval));

	if (zend_hash_find(Z_ARRVAL_P(proxy), "pwd", sizeof("pwd"), (void **)&ppval) != SUCCESS)
	{
	  RETURN_BOOL(0);
	}
	convert_to_string_ex(ppval);
	item->pwd = estrndup( Z_STRVAL_PP ( ppval) , Z_STRLEN_PP(ppval));

	if (zend_hash_find(Z_ARRVAL_P(proxy), "type", sizeof("type"), (void **)&ppval) != SUCCESS)
	{
	  RETURN_BOOL(0);
	}
	convert_to_long_ex(ppval);

	//TODO : Change String from args to PROXY_ITEM
	RETURN_BOOL( fx_set_proxy( item));
}
/* }}} */

/* {{{ proto void fx_set_unknow_proxy()
    */
PHP_FUNCTION(fx_set_unknow_proxy)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	fx_set_unknow_serve_address();
	RETURN_NULL();
}
/* }}} */

/* {{{ proto string fx_get_proxy()
    */
PHP_FUNCTION(fx_get_proxy)
{
	const PROXY_ITEM* proxy ;
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	proxy =  fx_get_proxy();
	array_init(return_value);
	
	if (proxy->host) add_assoc_string(return_value, "host", (proxy->host), 1);
	if (proxy->port) add_assoc_string(return_value, "port", (proxy->port), 1);
	if (proxy->name) add_assoc_string(return_value, "name", (proxy->name), 1);
	if (proxy->pwd) add_assoc_string(return_value, "pwd", (proxy->pwd), 1);
	add_assoc_long(return_value, "type", proxy->type);
}
/* }}} */

/* {{{ proto void fx_setProxyEnabled(bool status)
    */
PHP_FUNCTION(fx_setProxyEnabled)
{
	int argc = ZEND_NUM_ARGS();
	zend_bool status;

	if (zend_parse_parameters(argc TSRMLS_CC, "b", &status) == FAILURE) 
		return;

	fx_setProxyEnabled(status);
	RETURN_NULL();
}
/* }}} */

/* {{{ proto bool fx_proxyEnabled()
    */
PHP_FUNCTION(fx_proxyEnabled)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	RETURN_BOOL(fx_proxyEnabled());
}
/* }}} */

/* {{{ proto string fx_msg_no_format(string msg)
      */
PHP_FUNCTION(fx_msg_no_format)
{
	char *msg = NULL;
	int argc = ZEND_NUM_ARGS();
	int msg_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &msg, &msg_len) == FAILURE) 
		return;

	RETURN_STRING(estrdup(fx_msg_no_format(msg)), 1);
}
/* }}} */

/* {{{ proto string fx_get_original_ID(long id)
    */
PHP_FUNCTION(fx_get_original_ID)
{
	int argc = ZEND_NUM_ARGS();
	long id;

	if (zend_parse_parameters(argc TSRMLS_CC, "l", &id) == FAILURE) 
		return;

	RETURN_STRING(estrdup(fx_get_original_ID(id)), 1);
}
/* }}} */



/*{{{ callback of EventListener 
 */
void fetion_event_callback(int message, WPARAM wParam, LPARAM lParam, void *args) 
{
	char* callback = NULL; 
	zval* cb_func = NULL;
	libfetion_event_t* event = (libfetion_event_t*) args;	
	zval *fret = NULL;
	zval* argv[4];
	callback = event->callback;
	assert(callback);
	// initial callback arguments
	MAKE_STD_ZVAL(argv[0]);
	MAKE_STD_ZVAL(argv[1]);
	MAKE_STD_ZVAL(argv[2]);
	MAKE_STD_ZVAL(cb_func);
	ZVAL_STRING(cb_func, callback, 1);
	ZVAL_LONG(argv[0], message);
	ZVAL_LONG(argv[1], wParam);
	ZVAL_LONG(argv[2], lParam);
	argv[3] = event->data;
	MAKE_STD_ZVAL(fret);
	// argv[3] = event->data;
	if (LIBFETION_PHP_DEBUG)
		php_printf("callback is %s\n", callback);
	if ( call_user_function( EG(function_table), 
								NULL, 
								cb_func, 
								fret, 
								4,
								argv TSRMLS_CC)
		== FAILURE) {
		if (LIBFETION_PHP_DEBUG)
			php_printf("get an error LINE :%d", __LINE__);
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Could not call the callback function on libfetion");
		return;
	}
	if (LIBFETION_PHP_DEBUG)
		php_printf("fine so far in line:%d", __LINE__);
	zval_ptr_dtor(&fret);
	return;
}
/*
 * }}} //  callback of EventListener */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
