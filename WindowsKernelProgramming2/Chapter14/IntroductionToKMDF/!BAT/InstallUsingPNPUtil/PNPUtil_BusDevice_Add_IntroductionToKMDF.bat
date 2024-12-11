REM !!! COMMAND instaluje BUS DEVICE.
REM !!! HARDWARE ID sa MUSI zhodovat s tym, ktore je uvedene v INF FILE v SECTION [Standard.NT$ARCH$.10.0...16299] a DIRECTIVE [%IntroductionToKMDF.DeviceDesc%].
"C:\Program Files (x86)\Windows Kits\10\Tools\10.0.26100.0\x64\devgen.exe" /add /bus ROOT /hardwareid Root\IntroductionToKMDF /instanceid MY_TEST_DEVICE