REM Ziskanie nazvu DRIVER.
REM DEVCON.EXE HWIDS *

FOR /L %%X IN (1,1,100) DO (ECHO ITERATION %%X & DEVCON.EXE disable Root\PortResourcesDriver & TIMEOUT 10 & DEVCON.EXE enable Root\PortResourcesDriver)