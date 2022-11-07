#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include "php.h"
#include "ext/standard/info.h"
#include "php_keyvault.h"
#include "stdlib.h"
#include "string.h"


PHP_FUNCTION(keyvault_check)
{
    char *str;
    size_t len;

    ZEND_PARSE_PARAMETERS_START(1,1)
	Z_PARAM_STRING(str,len);
    ZEND_PARSE_PARAMETERS_END();

    for(int i = 0; i < sizeof(passwords)/sizeof(char*);i++) {
        if (strcmp(passwords[i], str) == 0) {
            RETURN_TRUE;
        }
    }
    RETURN_FALSE;
}

ZEND_BEGIN_ARG_INFO(arginfo_keyvault, 1)
    ZEND_ARG_INFO(0,str)
ZEND_END_ARG_INFO()

const zend_function_entry keyvault_functions[] = {
    PHP_FE(keyvault_check, arginfo_keyvault)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(keyvault)
{
    /* Here the module is being initialized */
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(keyvault)
{
    /* Here the module is deinitialized */
    return SUCCESS;
}

PHP_RINIT_FUNCTION(keyvault)
{
#if defined(ZTS) && defined(COMPILE_DL_keyvault)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(keyvault)
{
    /* Here the module is deinitialized for a given request */
    return SUCCESS;
}

PHP_MINFO_FUNCTION(keyvault)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "keyvault support", "enabled");
    php_info_print_table_end();
}

zend_module_entry keyvault_module_entry = {
    STANDARD_MODULE_HEADER,
    "keyvault", /* Extension name */
    keyvault_functions, /* zend_function_entry */
    PHP_MINIT(keyvault), /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(keyvault), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(keyvault), /* PHP_RINIT - Request initialization */
    PHP_RSHUTDOWN(keyvault), /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(keyvault), /* PHP_MINFO - Module info */
    PHP_KEYVAULT_VERSION, /* Version */
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_KEYVAULT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(keyvault)
#endif
