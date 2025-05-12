FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS runtime

EXPOSE 5001

WORKDIR /app

COPY MY_PUBLISHED/ ./

ENTRYPOINT ["dotnet", "ProgramDockerCLI.dll"]