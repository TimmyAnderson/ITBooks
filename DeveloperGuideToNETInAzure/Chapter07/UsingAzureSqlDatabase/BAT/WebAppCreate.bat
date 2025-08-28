REM !!!!! V DOCKER HUB musi byt vytvoreny REPOSITORY [using_azure_sql_database].

az webapp create --name MyWebProgram --plan MyAppServicePlan --resource-group Chapter07 --container-image-name docker.io/timmyanderson/using_azure_sql_database:1.0.0