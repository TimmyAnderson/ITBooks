REM !!!!! VALUE [14d1a545-6b72-43c4-b1a5-1d1231309766] je PRINCIPAL ID USER ASSINGNED MANAGED IDENTITY. VALUE sa ziskava z COMMAND [az identity list --resource-group Chapter07] z PROPERTY [principalId].

az sql server ad-admin create --resource-group Chapter07 --server ta76dbserver --object-id "14d1a545-6b72-43c4-b1a5-1d1231309766" --display-name "My User Managed Identity"