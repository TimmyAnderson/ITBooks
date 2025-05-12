REM !!!!! Pre DEVOPS IMAGES sa MUSI pouzit LATEST IMAGE, aby pri CODE CHANGE sa spravit REBUILD.

az webapp create --name MyWebProgramDevOps --plan MyAppServicePlan --resource-group MyResources --container-image-name containertimmyanderson.azurecr.io/programdockervs:latest