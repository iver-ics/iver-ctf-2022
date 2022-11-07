#ifndef PHP_KEYVAULT_H
# define PHP_KEYVAULT_H

const char *passwords[] = {
    "hunter2",
    "hello_iver",
    "Sommar2020",
    "S3CuR3P4ssw000rd",
    "C4nDyISGREAT"
};


extern zend_module_entry keyvault_module_entry;
# define phpext_keyvault_ptr &keyvault_module_entry

# define PHP_KEYVAULT_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_KEYVAULT)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_KEYVAULT_H */
