REM Ziskanie nazvu DRIVER.
REM DEVCON.EXE HWIDS *

FOR /L %%X IN (1,1,300) DO (ECHO ITERATION %%X & DEVCON.EXE disable Root\DMASlaveCommonBufferDriver & TIMEOUT 3 & DEVCON.EXE enable Root\DMASlaveCommonBufferDriver)