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
* [TRS80 Model 4P service manual](https://archive.org/details/TRS80Model4PServiceManual/mode/2up)
