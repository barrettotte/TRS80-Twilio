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

/* For TRS-80 serial interface */
#include <SoftwareSerial.h>

/* std includes */
#include <stdarg.h> // variable length args

/* Configuration and secrets */
#include "trs80_twilio_config.h"

/* OLED dimensions */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

/* Pins */
#define D5 (14) // TRS-80 TX
#define D6 (12) // TRS-80 RX

#define BAUD_RATE      300
#define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE   256
#define RESPBUFF_SIZE  2048

#define TRSPHONE_SIZE   15
#define TRSMSG_SIZE    128
#define TRSBUFF_SIZE   256

const char *_TWILIO_HOST = "https://api.twilio.com";

/* main */
void initSerial();
void initWifi();
void initDisplay();


void getTrsBuffer();


/* display utils */
void clearDisplay();
void syncPrint(const char *s);
void syncPrintf(const char *fmt, ...);
void syncPrintfClr(const char *fmt, ...);

String urlEncode(String s);

#endif
