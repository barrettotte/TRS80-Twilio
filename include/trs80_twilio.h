#ifndef TRS80_TWILIO_H
#define TRS80_TWILIO_H

#include <Arduino.h>

/* JSON support */
#include <ArduinoJson.h>

/* OLED support */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/* WiFi and HTTPS requests */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // create TLS connection

/* std includes */
#include <stdarg.h> // variable length args

/* Configuration and secrets */
#include "trs80_twilio_config.h"

/* OLED dimensions */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

#define BAUD_RATE      300
#define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE   256
#define RESPBUFF_SIZE  2048


/* main */
void initSerial();
void initWifi();
void initDisplay();


/* display utils */
void clearDisplay();
void syncPrint(const char *s);
void syncPrintf(const char *fmt, ...);
void syncPrintfClr(const char *fmt, ...);

#endif
