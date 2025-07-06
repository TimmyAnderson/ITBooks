REM !!!!! DOCKER DESKTOP MUSI BEZAT, pretoze DAPR RUNTIME bezi v DOCKER.

dapr run --app-id SERVICE_2 --app-port 5002 --dapr-http-port 10002 -- dotnet run