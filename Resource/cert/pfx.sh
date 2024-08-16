openssl pkcs12 -export -out server.pfx -inkey server.key -in server.crt -certfile ca.crt
openssl pkcs12 -export -out client.pfx -inkey client.key -in client.crt -certfile ca.crt
