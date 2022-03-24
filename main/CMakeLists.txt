# Embed the server root certificate into the final binary
#
# (If this was a component, we would set COMPONENT_EMBED_TXTFILES here.)
idf_component_register(SRCS "Src/user_https_client.c" "Src/main.c"
                            "Src/user_cjson.c"
                    INCLUDE_DIRS "Inc/."
                    EMBED_TXTFILES "certs/howsmyssl_com_root_cert.pem"
                                   "certs/DigiCertGlobalRootCA.pem" 
                                   "certs/ip.pem" 
                                   "certs/geocoding.pem"   
                                   "certs/inverse_geocoding.pem"                 )
