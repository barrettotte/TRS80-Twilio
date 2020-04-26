## Minicom
Testing RS232 port with Ubuntu before jumping down the ESP2866 rabbit hole.

* TRS-80 Model 100 ----- RS232 to USB ----- Ubuntu
* minicom, a text-based serial port comm program - ```apt-get install minicom```
* find names of ports - ```dmesg | grep tty```
* TRS80 Model 100 in **Terminal mode** with ```38N1D``` (**F3** ```STAT 38N1D```)
  * **3** - 300 baud
  * **8** - 8-bit word size
  * **N** - Parity None
  * **1** - Stop bit(s)
  * **D** - XON/XOFF status disabled (program controlled)
* minicom serial device config (see [docs/minirc.trs80m100](docs/minirc.trs80m100))
  * Port: /dev/ttyUSB0
  * Bps/Par/Bits: ```300 8N1```
  * Hardware Flow Control: ```No```
  * Software Flow Control: ```Yes```
* minicom session (CTRL+A Z)
  * E - turn on local Echo
  * T Terminal Settings -> A Terminal emulation: ANSI
  * T Terminal Settings -> B Backspace key sends: DEL
  * T Terminal Settings -> U Add Carriage Ret
  * T Terminal Settings -> A Add linefeed


## Tic
* https://zork.net/~octal/mod100.xhtml
* https://arstechnica.com/information-technology/2015/08/surfing-the-internet-from-my-trs-80-model-100/
```
trs100|Radio Shack Model 100:\
        :am:bs:xt:\
        :co#40:li#8:\
        :al=\EL:bl=^G:cd=\EJ:ce=\EK:cl=\EE:cm=\EY%+ %+ :\
        :cr=^M:dl=\EM:do=^J:ho=\EH:kb=^H:kd=^_:kl=^]:kr=^\:\
        :ku=^^:le=^H:nd=\034:se=\Eq:sf=^J:so=\Ep:up=\EA:\
        :ve=\EP:vi=\EQ:
```

