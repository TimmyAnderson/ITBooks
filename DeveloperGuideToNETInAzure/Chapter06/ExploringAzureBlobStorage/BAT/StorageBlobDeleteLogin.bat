REM !!!!! Aby LOGIN fungoval, MUSI byt USER ACCOUNT s ktorym USER vykonava CLI COMMANDS pridelena ROLE [Storage Blob Data Contributor].

az storage blob delete --account-name mystorageta --container-name myblobcontainer --name SomeBlobFile.txt --auth-mode login