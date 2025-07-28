REM !!!!! Aby LOGIN fungoval, MUSI byt USER ACCOUNT s ktorym USER vykonava CLI COMMANDS pridelena ROLE [Storage Blob Data Contributor].

az storage blob list --account-name mystorageta --container-name myblobcontainer --auth-mode login