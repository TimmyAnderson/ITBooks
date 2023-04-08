@echo OFF

rem PATH where MASM is installed.
set MASM_PATH="C:\%1 Files (x86)\Microsoft Visual Studio 10.0\VC\bin"
rem PATH where MASM32 SDK is installed.
set MASM32_SDK10_PATH=C:\MASM32\
rem PATH to SUBFOLDER 'LIB' of MASM32 SDK installation directory.
set LIB=%MASM32_SDK10_PATH%LIB

if exist %1.obj del %1.obj
if exist %1.exe del %1.exe

%MASM_PATH%\ML.EXE /I %MASM32_SDK10_PATH% /c /coff %1.asm
if errorlevel 1 goto errasm

%MASM_PATH%\LINK.EXE /SUBSYSTEM:CONSOLE /OPT:NOREF %1.obj
if errorlevel 1 goto errlink
dir %1.*
goto TheEnd

:errlink
echo !!! Assembly LINKING Error !!!
goto TheEnd

:errasm
echo !!! Assembly COMPILATION Error !!!
goto TheEnd

:TheEnd
del *.obj

pause