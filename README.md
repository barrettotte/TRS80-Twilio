# TRS80-Twilio


Sending a text message from a TRS-80 Model 100 using the Twilio SMS API and an ESP8266.


This is one of my entries to the [Twilio Hackathon on DEV (2020)](https://dev.to/devteam/announcing-the-twilio-hackathon-on-dev-2lh8).

Here are the links to my [submission post](https://dev.to/barrettotte/trs80-twilio-sending-texts-like-its-1983-submission-450l) and [demo](https://www.youtube.com/watch?v=C2nngeuc3Oc).


<br>
<p align="center">
  <img src="https://github.com/barrettotte/TRS80-Twilio/blob/master/docs/screenshots/20200427_195814.jpg" alt="TRS80-TWILIO" width="50%" height="50%"/>
</p>


## Background
After I decided I was going to participate in the Twilio hackathon I stumbled across documentation for using an ESP8266 to send an SMS. Naturally, I decided to take it a step further and make a complete coding abomination.
**The basic goal was to use a vintage computer as a frontend and an ESP8266 as a backend to send a text message**.
This probably won't get judged (I can't blame them), but this was one of the funnest projects I've ever done.

I started out making the "frontend" on a TRS-80 Model 4P using BASIC and Z80 assembly.
To summarize, I woke up one morning and my old computer no longer worked...Read more at [test/TRS80-4P](test/TRS80-4P).
So, I had to start from scratch 5 days before the due date of this hackathon.
I recently bought a cheap TRS-80 model 100, so I switched over to learning how it worked.


<p align="center">
  <img src="https://github.com/barrettotte/TRS80-Twilio/blob/master/docs/screenshots/20200427_220409.jpg" alt="TRS80-TWILIO" width="50%" height="50%"/>
</p>


To my surprise, it was magnitudes easier to work with than the TRS-80 model 4P.
With the model 4P, I was forced to embed Z80 machine code into BASIC in order to write to its serial port.
With the model 100, all I had to do was open the serial port like a file and print to it...amazing.
The primary frontend file is [TWILIO.BAS](https://github.com/barrettotte/TRS80-Twilio/blob/master/TWILIO.BAS).
The frontend's job was to:
* provide a simple interface to input a phone number and message
* build a buffer of 145 bytes from user input
* basic phone number validation
* send buffer to the ESP8266 via RS232 (serial).

The "backend" was pretty easy to build. I recently refreshed on Arduino and learned how to use PlatformIO.
The biggest challenge with the backend was waiting for the incredibly slow serial port send all of the data.
The primary backend file is [src/main.cpp](https://github.com/barrettotte/TRS80-Twilio/blob/master/src/main.cpp)
The backend's job was to:
* establish connection to WiFi
* output helpful messages to OLED
* read serial input and parse buffer from TRS80
* establish connection to Twilio API
* build and invoke HTTP request to Twilio SMS API


<p align="center">
  <img src="https://github.com/barrettotte/TRS80-Twilio/blob/master/docs/screenshots/20200427_200253.jpg" alt="TRS80-TWILIO" width="50%" height="50%"/>
</p>


## Project Layout
<p align="center">
  <img src="https://github.com/barrettotte/TRS80-Twilio/blob/master/docs/screenshots/TRS80-Twilio.png" alt="TRS80-TWILIO" width="50%" height="50%"/>
</p>

```
### Basic Wiring ###

TRS80 DB25 --> DB25-DB9 Null Modem --> DB9 Male-Male --> TTL-RS232 ...

TTL-RS232   ESP8266      Mini OLED
              GND <----> GND
              3V3 <----> VCC
              D1  <----> SCL
              D2  <----> SDA
GND <-------> GND
VCC <-------> 3V3
TXD <-------> D6 (RXD)
RXD <-------> D5 (TXD)
```


## Setup
In case anyone feels inclined to set this up (or I forget how to in the future)

* Setup Twilio Account using [Twilio's documentation](https://www.twilio.com/docs/usage/tutorials/how-to-use-your-free-trial-account)
* Own a working TRS-80 model 100
* Either enter [TWILIO.BA](https://github.com/barrettotte/TRS80-Twilio/blob/master/TWILIO.BAS) by hand (what I did) or transfer via TELCOM application.
* Hardware - refer to Project Layout above
  * [DB9 to DB25 Null Modem cable](https://www.amazon.com/StarTech-com-Cross-Wired-Serial-Modem/dp/B00066HL50/ref=sr_1_4?dchild=1)
  * [DB9 Male to Male coupler](https://www.amazon.com/gp/product/B07DMWGNTF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  * [TTL-RS232 breakout](https://www.amazon.com/gp/product/B07Z5Y1WKX/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  * [ESP2866](https://www.amazon.com/KeeYees-Internet-Development-Wireless-Compatible/dp/B07HF44GBT/ref=sr_1_3?dchild=1)
  * [0.96 inch mini OLED](https://www.amazon.com/DIYmall-Serial-128x64-Display-Arduino/dp/B00O2KDQBE)
* Install VS Code and PlatformIO extension (refer to **Embedded Development in VS Code** below)
* ```git clone https://github.com/barrettotte/TRS80-Twilio```
* Open repository with VS Code
* Create **include/trs80_twilio_config.h** based on **include/template_config.h**
* Setup ESP2866, TTL-RS232 breakout, and mini OLED - refer to Project Layout above
* Connect ESP2866 via USB, compile, and upload with PlatformIO extension
* On TRS80 Model 100, load **TWILIO.BA** and execute ```RUN``` in BASIC interpreter

There's some other fun stuff included in [docs/](https://github.com/barrettotte/TRS80-Twilio/tree/master/docs), have a look.


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
* [TRS-80 Model 100 Manuals](http://www.classiccmp.org/dunfield/kyocera/index.htm)
* [Ira Goldklang's TRS-80 Revived Site](http://www.trs-80.com/wordpress/)
* [minicom manpages](https://manpages.ubuntu.com/manpages/trusty/man1/minicom.1.html)
* [ESP9266 Twilio](https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-esp8266-cpp)


## License
[MIT](http://www.opensource.org/licenses/mit-license.html)


## Disclaimer
No warranty expressed or implied. Software is as is.

As stated in official Twilio documentation (https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-esp8266-cpp)
**"If this device is deployed in the field you should only deploy a revocable key. This code is only suitable for prototyping or if you retain physical control of the installation."**

**In no way is this practical or should be recreated. This was solely for fun; don't take this too seriously.**
