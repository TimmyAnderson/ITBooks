REM !!! Za FILENAME [FILENAME.inf] je treba pouzit FILENAME, ktore VYGENEROVAL SYSTEM. Typickym prikladom je FILENAME [oemNUMBER.inf], kde VALUE [NUMBER] je vygenerovane cislo.
REM !!! FILENAME je mozne zistit volanim COMMAND [pnputil /enum-drivers], ktory zobrazi vsetky SOFTWARE DRIVERS.
REM !!! FILENAME je mozne zistit takisto pomocou DEVICE MANAGER v PROPERTIES daneho DRIVER, kde sa vyberie OPTION [Details->Inf name].
"C:\Program Files (x86)\Windows Kits\10\Tools\10.0.26100.0\x64\devcon.exe" dp_delete FILENAME.inf