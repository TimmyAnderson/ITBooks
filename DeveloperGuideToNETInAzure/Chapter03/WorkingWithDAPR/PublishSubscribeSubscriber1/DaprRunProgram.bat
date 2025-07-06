REM !!!!! DOCKER DESKTOP MUSI BEZAT, pretoze DAPR RUNTIME bezi v DOCKER.

dapr run --app-id SUBSCRIBER_SERVICE_1 --app-port 5011 --dapr-http-port 10011 -- dotnet run