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
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1.2.1.2.1 2008/02/07 19:39:50 iliaa Exp $ */

#ifndef PHP_LIBFETION_H
#define PHP_LIBFETION_H

extern zend_module_entry libfetion_module_entry;
#define phpext_libfetion_ptr &libfetion_module_entry

#ifdef PHP_WIN32
#	define PHP_LIBFETION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_LIBFETION_API __attribute__ ((visibility("default")))
#else
#	define PHP_LIBFETION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

// import fetion declarations
#include "libfetion/libfetion.h"

#define LIBFETION_PHP_DEBUG 1

PHP_MINIT_FUNCTION(libfetion);
PHP_MSHUTDOWN_FUNCTION(libfetion);
PHP_RINIT_FUNCTION(libfetion);
PHP_RSHUTDOWN_FUNCTION(libfetion);
PHP_MINFO_FUNCTION(libfetion);

PHP_FUNCTION(confirm_libfetion_compiled);	/* For testing, remove later. */
PHP_FUNCTION(fx_init);
PHP_FUNCTION(fx_terminate);
PHP_FUNCTION(fx_close_network);
PHP_FUNCTION(fs_login);
PHP_FUNCTION(fx_login);
PHP_FUNCTION(fx_set_login_status);
PHP_FUNCTION(fx_loginout);
PHP_FUNCTION(fx_set_system_msg_cb);
PHP_FUNCTION(fx_get_msg);
PHP_FUNCTION(fs_send_sms);
PHP_FUNCTION(fs_send_sms_by_mobile_no);
PHP_FUNCTION(fs_send_sms_to_self);
PHP_FUNCTION(fx_send_sms);
PHP_FUNCTION(fx_send_sms_to_self);
PHP_FUNCTION(fx_send_sms_by_mobile_no);
PHP_FUNCTION(fs_begin_dialog);
PHP_FUNCTION(fs_dialog_send);
PHP_FUNCTION(fs_end_dialog);
PHP_FUNCTION(fx_begin_dialog);
PHP_FUNCTION(fx_dialog_send);
PHP_FUNCTION(fx_end_dialog);
PHP_FUNCTION(fx_get_usr_uid);
PHP_FUNCTION(fx_get_usr_uri);
PHP_FUNCTION(fx_get_usr_mobilenum);
PHP_FUNCTION(fx_set_user_state);
PHP_FUNCTION(fx_get_user_state);
PHP_FUNCTION(fx_get_expirestime);
PHP_FUNCTION(fx_data_get_PersonalInfo);
PHP_FUNCTION(fx_get_group);
/* PHP_FUNCTION(fx_get_account); */
PHP_FUNCTION(fx_get_blacklist);
PHP_FUNCTION(fx_get_qun);
PHP_FUNCTION(fx_get_account_by_id);
PHP_FUNCTION(fx_is_pc_user_by_id);
PHP_FUNCTION(fx_is_pc_user_by_account);
PHP_FUNCTION(fx_is_authed_by_id);
PHP_FUNCTION(fx_is_authed_by_account);
PHP_FUNCTION(fx_is_InBlacklist_by_id);
PHP_FUNCTION(fx_is_InBlacklist_by_account);
PHP_FUNCTION(fx_is_on_line_by_id);
PHP_FUNCTION(fx_is_on_line_by_account);
PHP_FUNCTION(fx_get_online_status_by_id);
PHP_FUNCTION(fx_get_online_status_by_account);
PHP_FUNCTION(fx_update_account_info_by_id);
PHP_FUNCTION(fx_get_account_show_name);
PHP_FUNCTION(fx_get_qun_show_name);
PHP_FUNCTION(fx_get_account_group_id);
PHP_FUNCTION(fs_rename_buddylist);
PHP_FUNCTION(fs_delete_buddylist);
PHP_FUNCTION(fx_rename_buddylist);
PHP_FUNCTION(fx_add_buddylist);
PHP_FUNCTION(fx_add_buddy_by_uid);
PHP_FUNCTION(fx_add_buddy_by_mobile);
PHP_FUNCTION(fx_delete_buddylist);
PHP_FUNCTION(fs_set_buddyinfo);
PHP_FUNCTION(fx_set_buddyinfo);
PHP_FUNCTION(fx_delete_buddy_by_id);
PHP_FUNCTION(fx_delete_buddy_by_account);
PHP_FUNCTION(fx_addto_blacklist_by_id);
PHP_FUNCTION(fx_addto_blacklist_by_account);
PHP_FUNCTION(fx_addto_blacklist_by_uri);
PHP_FUNCTION(fx_removefrom_blacklist_by_id);
PHP_FUNCTION(fx_removefrom_blacklist_by_account);
PHP_FUNCTION(fx_removefrom_blacklist_by_uri);
PHP_FUNCTION(fx_set_proxy);
PHP_FUNCTION(fx_set_unknow_proxy);
PHP_FUNCTION(fx_get_proxy);
PHP_FUNCTION(fx_setProxyEnabled);
PHP_FUNCTION(fx_proxyEnabled);
PHP_FUNCTION(fx_msg_no_format);
PHP_FUNCTION(fx_get_original_ID);


/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(libfetion)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(libfetion)
*/

/* In every utility function you add that needs to use variables 
   in php_libfetion_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as LIBFETION_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

extern "C" { 
#ifdef ZTS
#define LIBFETION_G(v) TSRMG(libfetion_globals_id, zend_libfetion_globals *, v)
#else
#define LIBFETION_G(v) (libfetion_globals.v)
#endif
}


struct libfetion_event_t {
	char*	callback; // a string or an array
	zval*   data; // actually contains one zval* data
};

// the callback function of php
void fetion_event_callback(int message, WPARAM wParam, LPARAM lParam, void *args);

// make it compatible for higher version php
#if ZEND_MODULE_API_NO <= 20060613
#define zend_parse_parameters_none()										\
		zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "")
#endif // ZEND_MODULE_API_NO <= 20060613


#endif	/* PHP_LIBFETION_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
