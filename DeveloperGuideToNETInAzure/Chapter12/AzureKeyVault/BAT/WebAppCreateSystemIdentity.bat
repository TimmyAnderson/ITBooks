REM DOCKER HUB musi obsahovat PUBLIC REPOSITORY [keyvaultsystemassignedmanagedidentity].

az webapp create --name KeyVaultSystemAssignedManagedIdentity --plan MyAppServicePlan --resource-group Chapter12 --container-image-name docker.io/timmyanderson/keyvaultsystemassignedmanagedidentity:1.0.0