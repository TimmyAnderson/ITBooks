rmdir /S /Q MY_PUBLISHED

REM BUILDING and PUBLISHING PROGRAM.
dotnet publish ProgramDockerCLI.csproj --configuration Release --output MY_PUBLISHED