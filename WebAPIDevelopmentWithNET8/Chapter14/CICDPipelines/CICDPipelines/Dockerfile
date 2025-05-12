# See https://aka.ms/customizecontainer to learn how to customize your debug container and how Visual Studio uses this Dockerfile to build your images for faster debugging.

# !!!!!! DOCKER FILE bol vytvoreny s CONTEXT nastavenym na SOLUTION DIRECTORY. To je vhodne, ak PROJECT obsahuje ASSEMBLIES na ine PROJECTS v ramci toho isteho SOLUTION.

# COMMAND nastavuje IMAGE, ktory bude pouzity pre nasledujuce COMMANDS.
# IMAGE [mcr.microsoft.com/dotnet/aspnet:8.0] je zakladny ASP.NET IMAGE obsahujuci ASP.NET CORE RUNTIME FILES.
# !!! IMAGE je potrebny pre spustenie ASP.NET PROGRAMU.
FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base

# COMMAND nastavuje nazov USER, ktory sa pouzije na vykonanie nasledujucich COMMANDS.
USER $APP_UID

# COMMAND vytvori DIRECTORY [/app] a zaroven ho nastavi ako CURRENT WORKING DIRECTORY.
WORKDIR /app

# COMMANDS definuju PORTS, ktore DOCKER IMAGE vystavi do DOCKER CONTAINER.
# COMMANDS vystavuju PORTS z DOCKER IMAGE do DOCKER CONTAINER, ale NIE z DOCKER CONTAINER do HOST MACHINE.
# PORTS su PORTS PROGRAMU a pre tieto PORTS VISUAL STUDIO automaticky vytvoril vo FILE [launchSettings.json] specialny PROFILE, kde prave tieto PORTS vystavuje z DOCKER.
EXPOSE 8080
EXPOSE 8081

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

# COMMAND nastavuje IMAGE, ktory bude pouzity pre nasledujuce COMMANDS.
# IMAGE [mcr.microsoft.com/dotnet/sdk:8.0] je NET CORE SDK IMAGE, obsahujuci .NET CORE SDK RUNTIME FILES.
# !!!!! Tento IMAGE je potrebny IBA pre BUILD .NET PROGRAMU, ale nie je potrebny vo vyslednom DOCKER IMAGE, kedze na spustenie PROGRAMU staci iba IMAGE [mcr.microsoft.com/dotnet/aspnet:8.0].
FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build

# COMMAND nastavi CUSTOM VARIABLE, ktora moze byt pouzita neskor.
ARG BUILD_CONFIGURATION=Release

# COMMAND vytvori DIRECTORY [/src] a zaroven ho nastavi ako CURRENT WORKING DIRECTORY.
WORKDIR /src

# !!! COMMAND kopiruje FILE [CICDPipelines.csproj] z LOCAL FILE SYSTEM do DIRECTORY [CICDPipelines] vo FILE SYSTEM vytvaraneho DOCKER CONTAINER.
COPY ["CICDPipelines/CICDPipelines.csproj", "CICDPipelines/"]

# !!! COMMAND kopiruje FILE [MySharedLibrary/MySharedLibrary.csproj] z LOCAL FILE SYSTEM do DIRECTORY [MySharedLibrary] vo FILE SYSTEM vytvaraneho DOCKER CONTAINER.
COPY ["MySharedLibrary/MySharedLibrary.csproj", "MySharedLibrary/"]

# COMMAND vykona COMMAND [dotnet restore] nad CURRENT IMAGE. Po jeho vykonani, vytvori novy LAYER, ktory moze byt pouzity v nasledujucich COMMANDS.
# .NET COMMAND [dotnet restore] vykonava RESTORE vsetkych DEPENDENCY PACKAGES.
RUN dotnet restore "./CICDPipelines/CICDPipelines.csproj"

# !!! COMMAND nakopiruje vsetky FILES z CURRENT DIRECTORY v LOCAL FILE SYSTEM do CURRENT DIRECTORY v vo FILE SYSTEM vytvaraneho DOCKER CONTAINER.
# !!!!! Kedze DOCKER BUILD musi byt spustany v MAIN DIRECTORY .NET PROJECT, COMMAND de-facto skopiruje vsetky SOURCE CODES z LOCAL MACHINE do vytvaraneho DOCKER CONTAINER.
COPY . .

# COMMAND vytvori DIRECTORY [/src/CICDPipelines] a zaroven ho nastavi ako CURRENT WORKING DIRECTORY.
WORKDIR "/src/CICDPipelines"

# COMMAND spusti BUILD ASP.NET CORE PROGRAMU.
RUN dotnet build "./CICDPipelines.csproj" -c $BUILD_CONFIGURATION -o /app/build

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

# !!!!! COMMAND nastavi STAGE na stav v ktorom naposledy nachadzal STAGE [build].
FROM build AS publish

# COMMAND nastavi CUSTOM VARIABLE, ktora moze byt pouzita neskor.
ARG BUILD_CONFIGURATION=Release

# COMMAND spusti PUBLISH ASP.NET CORE PROGRAMU.
# !!!!! .NET COMMAND [dotnet publish] nakopiruje vsetky FILES daneho PROGRAMU, ktory bol BUILT v jednom z predoslych krokov do DIRECTORY [/app/publish] LAYER, ktory bol vykonanim COMMAND [RUN] vytvoreny.
# !!!!! FILES nie su kopirovane do FILE SYSTEM vysledneho DOCKER CONTAINER IMAGE, alebo iba do LAYER z ktoreho je ich treba prekopirovat do FILE SYSTEM DOCKER CONTAINER IMAGE.
RUN dotnet publish "./CICDPipelines.csproj" -c $BUILD_CONFIGURATION -o /app/publish /p:UseAppHost=false

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

# !!!!! COMMAND nastavi STAGE na stav v ktorom naposledy nachadzal STAGE [base].
FROM base AS final

# COMMAND nastavi DIRECTORY [/app] ako CURRENT WORKING DIRECTORY.
WORKDIR /app

# !!!!! COMMAND nakopiruje DIRECTORY [/app/publish] z LAYER, ktory vytvoril STAGE [publish] do CURRENT DIRECTORY vo FILE SYSTEM vytvaraneho DOCKER IMAGE.
# !!!!! DOCKER IMAGE vo vysledku bude obsahovat iba EXECUTABLE FILES s DEPENDENCIES v DIRECTORY [/app], a ZIADNE INE FILES, ani DIRECTORIES, ktore vznikli v priebehu celeho BUILD procesu.
COPY --from=publish /app/publish .

# !!! COMMAND spusta .NET PROGRAM v DOCKER CONTAINER.
ENTRYPOINT ["dotnet", "CICDPipelines.dll"]

# ----------------------------------------------------------------------------------------------------------------------