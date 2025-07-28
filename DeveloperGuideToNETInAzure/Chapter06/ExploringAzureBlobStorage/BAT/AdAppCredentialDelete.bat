REM !!!!! VALUE [ffc56ede-3197-4a50-b902-997042c385b3] sa ziskava pomocou COMMAND [az ad app list].
REM !!!!! VALUE [366c3957-867d-4725-9534-ee6abb31e21c] sa ziskava pomocou COMMAND [az ad app credential list --id "44b6ff6a-28f0-4210-b546-0b3a7d6cf1fa"].

az ad app credential delete --id "44b6ff6a-28f0-4210-b546-0b3a7d6cf1fa" --key-id "366c3957-867d-4725-9534-ee6abb31e21c"