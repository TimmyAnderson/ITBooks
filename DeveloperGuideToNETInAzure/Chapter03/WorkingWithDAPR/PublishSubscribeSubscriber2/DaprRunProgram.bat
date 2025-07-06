REM !!!!! DOCKER DESKTOP MUSI BEZAT, pretoze DAPR RUNTIME bezi v DOCKER.

dapr run --app-id SUBSCRIBER_SERVICE_2 --app-port 5012 --dapr-http-port 10012 -- dotnet run