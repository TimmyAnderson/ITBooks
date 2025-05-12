REM DOCKER HUB musi obsahovat PUBLIC REPOSITORY [myprogram_dockervs_dockerhub].

az webapp create --name MyWebProgramDockerHub --plan MyAppServicePlan --resource-group MyResources --container-image-name docker.io/timmyanderson/myprogram_dockervs_dockerhub:1.0.0