https://dev.to/roeeyn/how-to-setup-your-ctfd-platform-with-https-and-ssl-3fda


sudo certbot certonly

cp /etc/letsencrypt/live/YOUR_DOMAIN/fullchain.pem ./conf/nginx/fullchain.pem
cp /etc/letsencrypt/live/YOUR_DOMAIN/privkey.pem ./conf/nginx/privkey.pem


diff --git a/conf/nginx/http.conf b/conf/nginx/http.conf
index ff40613..5009a38 100644
--- a/conf/nginx/http.conf
+++ b/conf/nginx/http.conf
@@ -14,9 +14,19 @@ http {
   }

   server {
-
     listen 80;
+    return 301 https://$host$request_uri;
+  }
+
+  server {
+
+    listen 443 ssl;

+    ssl_certificate /certificates/fullchain.pem;
+    ssl_certificate_key /certificates/privkey.pem;
+    ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
+    ssl_ciphers HIGH:!aNULL:!MD5;
+
     client_max_body_size 4G;

     # Handle Server Sent Events for Notifications
diff --git a/docker-compose.yml b/docker-compose.yml
index 379633c..611fb8e 100644
--- a/docker-compose.yml
+++ b/docker-compose.yml
@@ -31,8 +31,11 @@ services:
     restart: always
     volumes:
       - ./conf/nginx/http.conf:/etc/nginx/nginx.conf
+      - ./conf/nginx/fullchain.pem:/certificates/fullchain.pem:ro
+      - ./conf/nginx/privkey.pem:/certificates/privkey.pem:ro
     ports:
       - 80:80
+      - 443:443
     depends_on:
       - ctfd

