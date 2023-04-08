del Out.txt
del Errors.txt
del PrintLines.c
del PrintLines.cpp

rem Nastavenim option '-+' generujem C++ SCANER.
rem ..\..\!FLEX\flex.exe -+ -oPrintLines.cpp "D:\Programy\.NET\CSharp\CompilerConstruction\Chapter02\FlexScaner\!Examples\PrintLines\Input.flx" > Out.txt 2> Errors.txt

rem Generujem C SCANER.
..\..\!FLEX\flex.exe -oPrintLines.c "D:\Programy\.NET\CSharp\CompilerConstruction\Chapter02\FlexScaner\!Examples\PrintLines\Input.flx" > Out.txt 2> Errors.txt