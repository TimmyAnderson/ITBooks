REM Ziskanie nazvu DRIVER.
REM DEVCON.EXE HWIDS *

FOR /L %%X IN (1,1,100) DO (ECHO ITERATION %%X & DEVCON.EXE disable Root\MemoryResourcesDriver & TIMEOUT 10 & DEVCON.EXE enable Root\MemoryResourcesDriver)