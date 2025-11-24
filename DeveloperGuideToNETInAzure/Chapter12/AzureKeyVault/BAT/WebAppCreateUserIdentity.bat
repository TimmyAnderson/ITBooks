REM DOCKER HUB musi obsahovat PUBLIC REPOSITORY [keyvaultuserassignedmanagedidentity].

az webapp create --name KeyVaultUserAssignedManagedIdentity --plan MyAppServicePlan --resource-group Chapter12 --container-image-name docker.io/timmyanderson/keyvaultuserassignedmanagedidentity:1.0.0