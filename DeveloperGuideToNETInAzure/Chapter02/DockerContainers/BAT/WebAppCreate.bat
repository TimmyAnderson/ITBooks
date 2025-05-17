REM !!!!! Treba nastavit spravny USER NAME a PASSWORD.

az webapp create --name MyWebProgram --plan MyAppServicePlan --resource-group MyResources --container-registry-user "containertimmyanderson" --container-registry-password "se1Ea0H9d6fZND3S7WH8b+NoIrpfrZ7ty4agcuacq7+ACRAtW4uv" --container-image-name containertimmyanderson.azurecr.io/programdockervs:1.0.0