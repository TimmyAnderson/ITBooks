REM !!!!! Treba nastavit spravny USER NAME a PASSWORD.
REM !!!!! Pre DEVOPS IMAGES sa MUSI pouzit LATEST IMAGE, aby pri CODE CHANGE sa spravit REBUILD.

az webapp create --name MyAzureProgram --plan MyBookPlan --resource-group MyBook --container-registry-user "mybookcontainer" --container-registry-password "uPo+5msUSyq7xxNaRuaYV+YXGf2Ds+1wuA/sRF/c9l+ACRD7vEwu" --container-image-name mybookcontainer.azurecr.io/myazureprogram:latest