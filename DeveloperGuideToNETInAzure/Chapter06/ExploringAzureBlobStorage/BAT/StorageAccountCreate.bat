REM !!! COMMAND vyzaduje registraciu SERVICE PROVIDER [Microsoft.Storage] pomocou COMMAND [az provider register --namespace "Microsoft.Storage"].

az storage account create --name mystorageta --resource-group Chapter06 --location "West US" --sku "Standard_LRS" --access-tier Hot --min-tls-version TLS1_2 --allow-blob-public-access false --encryption-services blob