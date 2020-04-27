#include "trs80_twilio.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiClientSecure client;
SoftwareSerial trsSerial;

char trsBuffer[TRSBUFF_SIZE];
boolean hasMsg = false;

void setup() {
  initSerial();
  initDisplay();
  //initWifi();

  // TODO: move to loop
  syncPrintfClr("Listening...\n");


}


void loop(){
  char c;

  if(Serial.available()){
    Serial.print("Received buffer\n");

    while(Serial.available() > 0){
      c = Serial.read();
      Serial.print(c);
    }
    Serial.println();
  }

  // if(WiFi.status() == WL_CONNECTED){

    // while(trsSerial.available()){
    //   Serial.print("Recieved buffer\n");
      
    //   char msg[TRS_MSG+2], phoneTo[TRS_PHONE+2];
    //   strcpy(phoneTo, trsSerial.readStringUntil(';').c_str());
    //   delay(250);
    //   strcpy(msg, trsSerial.readString().c_str());
    //   delay(500);
      
    //   Serial.printf("%s\n", phoneTo);
    //   Serial.printf("%s\n", msg);
    // }

    // char target[128], authHeader[128];
    // sprintf(target, "%s2010-04-01/Accounts/%s/Messages.json", _TWILIO_HOST, _TWILIO_ACC);
    // sprintf(authHeader, "Basic %s:%s", _TWILIO_ACC, _TWILIO_AUTH);

    // HTTPClient http;
    // syncPrintfClr("Sending HTTP POST\nrequest to\n\n%s", _TWILIO_HOST);
    // http.begin(client, target);
    // http.addHeader("Authorization", authHeader);
    // http.addHeader("Accept", "application/json");
    // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
    // char req[512];
    // sprintf(req, "To=%s&From=%s&Body=%s", phoneTo, urlEncode(_TWILIO_FROM).c_str(), msg);
    // int status = http.POST(req);

    // char resp[3072];
    // if(status > 0){
    //   syncPrintf("\n\nHTTP POST %d\n", status);
    //   strcpy(resp, http.getString().c_str());
    //   if(status != HTTP_CODE_CREATED && status != HTTP_CODE_OK){
    //     Serial.printf("HTTP ERR: %s\n", resp);
    //   } else{
    //     Serial.print(resp);
    //   }
    // } else{
    //   Serial.printf("HTTP FAILED: %s\n", http.errorToString(status).c_str());
    // }
    // http.end();
    //
  // }
  delay(2500);
}


// set baud rate and init both serials
void initSerial(){
  Serial.begin(BAUD_RATE, SERIAL_8N1);
  
  /* Give some init time + switch to serial monitor */
  Serial.println();
  Serial.println();
  Serial.println();
  for(uint8_t t = 3; t > 0; t--){
    Serial.printf("WAIT %d...\n", t);
    Serial.flush();
    delay(500);
  }
  trsSerial.begin(BAUD_RATE, SWSERIAL_8N1, D5, D6, false, TRSBUFF_SIZE, 32);
  delay(1000);
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


// fetch TRS-80 buffer from software serial
void getTrsBuffer(){
  if(trsSerial.available()){
    Serial.print("Recieved buffer\n");
    strcpy(trsBuffer, trsSerial.readString().c_str());
    delay(1000);
    syncPrintf("%s\n", trsBuffer);
  }
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


// lol...yeah i didn't have the time to look completely into
// writing up a URL encoder; so this looked good enough.
// https://github.com/zenmanenergy/ESP8266-Arduino-Examples
String urlEncode(String s){
  String encodedString = "";
  char c, code0, code1, code2;
  for(size_t i = 0; i < s.length(); i++){
    c = s.charAt(i);
    if(c == ' '){
      encodedString += '+';
    } else if(isalnum(c)){
      encodedString += c;
    } else{
      code1 = (c & 0xf) + '0';
      if((c & 0xf) > 9){
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9){
        code0 = c - 10 + 'A';
      }
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString += code2;
    }
    yield();
  }
  return encodedString;
}
