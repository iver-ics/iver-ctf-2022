FROM php:7.4-apache
COPY . .
RUN cd extension && phpize && ./configure && make
RUN cp extension/modules/keyvault.so /var/www/keyvault.so
RUN cat passwords.txt | while read line; do echo -n "$line" | md5sum | cut -d" " -f1; done > public/bannedHashes.txt
RUN cp public/* /var/www/html/.
# Use the default production configuration
RUN mv "$PHP_INI_DIR/php.ini-production" "$PHP_INI_DIR/php.ini"
RUN echo "extension=/var/www/keyvault.so" >> "$PHP_INI_DIR/php.ini"
