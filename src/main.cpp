#include "trs80_twilio.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiClientSecure client;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  initSerial();
  initDisplay();
  //initWifi();

  //client.setInsecure();

  // TODO: move to loop
  //syncPrintfClr("Listening...");
}

void recieveMessage(){
  static byte ndx = 0;
  char end = '\n';
  char c;

  while(Serial.available() > 0 && !newData){
    c = Serial.read();
    if(c != end){
      receivedChars[ndx] = c;
      ndx++;
      if(ndx >= numChars){
        ndx = numChars - 1;
      }
    } else{
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData(){
  if(newData){
    syncPrintfClr("received\n\n%s", receivedChars);
    newData = false;
  }
}

void loop() {
  recieveMessage();
  showNewData();
  delay(1000);
}

// set baud rate and init serial buffer
void initSerial(){
  Serial.begin(BAUD_RATE);
  Serial.println();
  Serial.println();
  Serial.println();
  for(uint8_t t = 3; t > 0; t--){
    Serial.printf("WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  Serial.println("\n* * * START * * *");
}


// setup OLED display and text properties
void initDisplay(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1500);
  clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}


// connect to wifi using SSID and password in include/anilist8266_config.h
void initWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(_WIFI_SSID, _WIFI_PWD);

  syncPrintf("Connecting..");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    syncPrint(".");
  }
  syncPrintfClr("SSID: %s\nIP: %s\n", _WIFI_SSID, WiFi.localIP().toString().c_str());
}


// reset OLED
void clearDisplay(){
  display.clearDisplay();
  display.setCursor(0, 0);
  delay(500);
}


// clear display and print formatted string to serial + OLED
void syncPrintfClr(const char *fmt, ...){
  va_list args;
  va_start(args, fmt);
  char buffer[SYNCPRINT_SIZE];
  vsnprintf(buffer, SYNCPRINT_SIZE-1, fmt, args);
  clearDisplay();
  syncPrint(buffer);
  va_end(args);
}


// print formatted string to serial + OLED
void syncPrintf(const char *fmt, ...){
  va_list args;
  va_start(args, fmt);
  char buffer[SYNCPRINT_SIZE];
  vsnprintf(buffer, SYNCPRINT_SIZE-1, fmt, args);
  syncPrint(buffer);
  va_end(args);
}


// print a string to serial + OLED
void syncPrint(const char *s){
  Serial.print(s);
  display.print(s);
  display.display();
}