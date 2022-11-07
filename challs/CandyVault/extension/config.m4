PHP_ARG_ENABLE(keyvault, whether to enable keyvault support,
[  --enable-keyvault Enable keyvault support], no)

if test "$PHP_KEYVAULT" != "no"; then
  AC_DEFINE(HAVE_KEYVAULT, 1, [ Have keyvault support ])
  PHP_NEW_EXTENSION(keyvault, keyvault.c, $ext_shared)
fi
