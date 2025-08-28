REM !!!!! RULE efektivne odstranuje OPTION [Allow Azure services and resources to access this server] na SQL SERVERI.

az sql server firewall-rule delete --name AllowAzureService --resource-group Chapter07 --server ta76dbserver