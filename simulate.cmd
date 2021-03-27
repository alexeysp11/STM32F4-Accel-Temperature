@echo off 

if "%1" == "--no-build" (
    dotnet run --project ./Simulation3d/Simulation3d.csproj --no-build
) else (
    dotnet run --project ./Simulation3d/Simulation3d.csproj 
)
