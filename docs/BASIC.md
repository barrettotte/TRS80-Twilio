# BASIC

http://www.retrocomputing.net/parts/r/radio/TRS80_4/docs/trs80-pd.htm#nd80mod4

## Disk BASIC
I'm using NEWDOS V2 on a Model 4P; therefore I'm using Disk BASIC.

http://www.trs-80.com/wordpress/dos-newdos80/manual-5/#chapter7

```BASIC,3,48152,LOAD"XXX/BAS"```

https://www.wikiwand.com/en/Microsoft_BASIC


## USR(x)
Call machine-language subroutine and return control to BASIC program


## SYSTEM
Puts computer in monitor mode, allowing object files (machine language routines or data) to be loaded.
* ```SYSTEM```
* *? - enter file name or '/' address in decimal to begin execution


## NewDOS
Misc notes on NewDOS V2.0

http://www.trs-80.com/wordpress/dos-newdos80/newdos80-v2-0-reference-one-page/

```
SETCOM,WORD=8,BAUD=300,PARITY=1,WAIT
SETCOM,OFF
```
