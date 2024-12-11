REM !!! COMMAND vrati vygenerovany nazov PUBLISHED INF FILE NAME, ktory sa pouziva pri REMOVE DRIVER.
REM !!! PUBLISHED INF FILE NAME je mozne zistit volanim COMMAND [pnputil /enum-drivers], ktory zobrazi vsetky SOFTWARE DRIVERS.
REM !!! PUBLISHED INF FILE NAME je mozne zistit takisto pomocou DEVICE MANAGER v PROPERTIES daneho DRIVER, kde sa vyberie OPTION [Details->Inf name].
pnputil.exe /add-driver C:\Drivers\IntroductionToKMDF.inf /install