# Notes on BASIC
I'm forgetful and the manual I'm using doesn't have OCR.


## BASIC Command Mode
* CLEAR - clear all variable values
* CLS - clear screen
* CONT - continue exec after STOP command or BREAK
* FILES - print data and program files stored in RAM
* FRE - return amount of memory available to BASIC
* HIMEM - returns address of highest memory available to BASIC
* IPL - defines a BASIC program to run upon power up
* KILL - erases a RAM file
* LCOPY - copies the screen text to the printer
* LIST - list current program onto screen
* LLIST - lists current program onto printer
* LOAD - loads a BASIC program
* MAXRAM - returns address of highest available memory
* MENU - returns to model 100 menu
* MERGE - combines two BASIC programs
* NAME - renames a RAM file
* NEW - erases current program
* POWER - controls auto power off feature
* ? - abreviation for PRINT
* SAVE - save current program (to RAM)


## BASIC File I/O
* CLOSE - closes file
* EOF - func returning EOF cond
* INPUT$ - func returning specified number of chars from a file
* INPUT - reads data from a file
* KILL - delates a file
* LINE INPUT - reads a string of chars terminated by a carriage return
* LOAD - loads the BASIC program file into memory
* LOADM - loads a machine language program into memory
* MAXFILES - specifies max number of files your program may have open at one time
* MERGE - merges a BASIC program file with the program currently in BASIC memory
* NAME - changes the name of a file
* OPEN - allocates a buffer (temp block of memory) for IO to device
* PRINT - send data to a file
* PRINT USING - send formatted data into a file
* RUN - begins execution of a program
* RUNM - loads and runs a machine language program
* SAVE - sends a BASIC program to a device
* SAVEM - Sends a machine language program to a device


```
1    EXAMPLE PRINT TO RS232
10   OPEN "COM:87N1E" FOR OUTPUT AS 4
15   REM TRANSMIT 10,20,30 TO RS232 LINE
20   PRINT #4,10,20,30
```


## BASIC Error Codes
| Code  | Message | Meaning          |
| ----- | ------- | ---------------- |
| 1     | NF      | NEXT without FOR |
| 2     | SN      | Syntax Error     |
| 3     | RG      | RETURN without GOSUB |
| 4     | OD      | Out of Data      |
| 5     | FC      | Illegal function call |
| 6     | OV      | Overflow         |
| 7     | OM      | Out of memory    |
| 8     | UL      | Undefined line   |
| 9     | BS      | Bad subscript    |
| 10    | DD      | Doubly dimensioned array |
| 11    | /0      | Divide by zero   |
| 12    | ID      | Illegal Direct   |
| 13    | TM      | Type mismatch    |
| 14    | OS      | Out of string space |
| 15    | LS      | String too long  |
| 16    | ST      | String formula too complex |
| 17    | CN      | Cant continue    |
| 18    | IO      | Error            |
| 19    | NR      | No RESUME        |
| 20    | RW      | RESUME without error |
| 21    | UE      | Undefined error  |
| 22    | MO      | Missing operand  |
| 23-49 | UE      | Undefined error  |
| 50    | IE      | Undefined error  |
| 51    | BN      | Bad file number  |
| 52    | FF      | File not found   |
| 53    | AO      | Already open     |
| 54    | EF      | Input past end of file |
| 55    | NM      | Bad file name    |
| 56    | DS      | Direct statement in file |
| 57    | FL      | Undefined error  |
| 58    | CF      | File not open    |
| 59-255 | UE     | Undefined error  |


