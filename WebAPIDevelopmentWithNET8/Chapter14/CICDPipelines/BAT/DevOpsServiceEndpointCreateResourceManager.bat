REM !!!!! FILE [MyEndpointConfigurationResourceManager.json] musi obsahovat konfiguraciu SERVICE ENDPOINT.

az devops service-endpoint create --project MyAzureProgramProject --organization https://dev.azure.com/timmyanderson1976/ --service-endpoint-configuration "MyEndpointConfigurationResourceManager.json"