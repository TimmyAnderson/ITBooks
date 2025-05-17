rmdir /S /Q Client\bin
rmdir /S /Q Client\obj

rmdir /S /Q MySharedLibrary\bin
rmdir /S /Q MySharedLibrary\obj

rmdir /S /Q MyGitHubActionsProgram\bin
rmdir /S /Q MyGitHubActionsProgram\obj

rmdir /S /Q MyGitHubActionsProgramTests\bin
rmdir /S /Q MyGitHubActionsProgramTests\obj

del /Q GitHubActions.slnLaunch.user

rmdir /S /Q .vs