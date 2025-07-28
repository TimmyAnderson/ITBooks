REM !!!!! Aby LOGIN fungoval, MUSI byt USER ACCOUNT s ktorym USER vykonava CLI COMMANDS pridelena ROLE [Storage Blob Data Contributor].

az storage blob upload --account-name mystorageta --container-name myblobcontainer --name MyFile.tmp --file MyFile.tmp --auth-mode login