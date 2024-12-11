REM !!! Za FILENAME [FILENAME.inf] je treba pouzit FILENAME, ktore VYGENEROVAL SYSTEM pri DRIVER INSTALL COMMAND. Typickym prikladom je FILENAME [oemNUMBER.inf], kde VALUE [NUMBER] je vygenerovane cislo.
REM !!! FILENAME je mozne zistit volanim COMMAND [pnputil /enum-drivers], ktory zobrazi vsetky SOFTWARE DRIVERS.
REM !!! FILENAME je mozne zistit takisto pomocou DEVICE MANAGER v PROPERTIES daneho DRIVER, kde sa vyberie OPTION [Details->Inf name].
pnputil.exe /delete-driver FILENAME.inf