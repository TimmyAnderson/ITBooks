REM !!!!! RULE efektivne povoluje OPTION [Allow Azure services and resources to access this server] na SQL SERVERI.

az sql server firewall-rule create --name AllowAzureService --resource-group Chapter07 --server ta76dbserver --start-ip-address 0.0.0.0 --end-ip-address 0.0.0.0