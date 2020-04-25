# TRS80-Twilio

Calling the Twilio SMS API from a TRS-80 Model 4P.


## Embedded Development in VS Code
I decided I would take this opportunity to learn about a new tool, [PlatformIO](https://platformio.org/).

[PlatformIO IDE Extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

Linux Additional Steps:
* https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules
* Setting permissions to allow board upload:
  * ```sudo usermod -a -G dialout <user>```
  * ```sudo usermod -a -G plugdev <user>```
  * ```sudo usermod -a -G tty <user>```
* Logout/Login


## References
* [Introduction to PlatformIO](https://www.youtube.com/watch?v=0poh_2rBq7E)
* [TRS-80 Model 4P service manual](https://archive.org/details/TRS80Model4PServiceManual/mode/2up)
* [TRS-80 Model III Operation and BASIC Language Reference Manual](http://www.1000bit.it/support/manuali/trs/Model%203%20Operation%20and%20BASIC%20Language%20Ref%20Man%20%281980%29%28Tandy%29%5Ba2%5D.pdf)
* [NewDos 2.0](http://www.trs-80.com/wordpress/dos-newdos80/newdos80-v2-0-reference-one-page/)