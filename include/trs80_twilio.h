#ifndef TRS80_TWILIO_H
#define TRS80_TWILIO_H

#include <Arduino.h>

/* OLED support */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/* WiFi and HTTPS requests */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // create TLS connection

/* For TRS-80 serial interface */
#include <SoftwareSerial.h>

/* Base64 encoding authorization header */
#include <base64.h>

/* variable length arguments */
#include <stdarg.h>

/* Configuration and secrets */
#include "trs80_twilio_config.h"

/* OLED dimensions */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

/* Pins */
#define D5 (14) // TRS-80 TX
#define D6 (12) // TRS-80 RX

#define BAUD_RATE      9600
#define TRSBAUDRATE    300
#define TRSBUFF_SIZE   145 // 16+1+128
#define SYNCPRINT_SIZE 256


/* SHA-1 fingerprint as of 04-27-2020 (retrieved from browser) */
const char *_TWILIO_FINGERPRINT = "BC B0 1A 32 80 5D E6 E4 A2 29 66 2B 08 C8 E0 4C 45 29 3F D0";
const size_t _TWILIO_PORT = 443;
const char *_TWILIO_HOST = "api.twilio.com";


/* init */
void initSerial();
void initWifi();
void initDisplay();

/* main */
int sendSms(String phoneTo, String message);
void reset();

/* display utils */
void clearDisplay();
void syncPrint(const char *s);
void syncPrintf(const char *fmt, ...);
void syncPrintfClr(const char *fmt, ...);

/* request utils */
String urlEncode(String s);
String getAuthHeader(const String& acc, const String& auth);


#endif
