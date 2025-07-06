REM !!! COMMAND vyzaduje registraciu SERVICE PROVIDER [Microsoft.Storage] pomocou COMMAND [az provider register --namespace "Microsoft.Storage"].

az storage account create --name mystorageta --resource-group MyBook --location "West US 2" --sku "Standard_LRS" --allow-blob-public-access false