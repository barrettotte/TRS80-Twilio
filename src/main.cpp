#include "trs80_twilio.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
SoftwareSerial trsSerial;
size_t trsBytes = 0;
char trsBuffer[TRSBUFF_SIZE];


void setup() {
  initSerial();
  initDisplay();
  initWifi();
  yield();
  syncPrintfClr("Listening...\n");
}


void loop(){
  if(WiFi.status() == WL_CONNECTED){

    // read TRS-80 buffer one byte at a time from serial
    if(trsSerial.available() > 0){
      while(trsSerial.available() > 0){
        char c = trsSerial.read();
        trsSerial.flush();
        trsBuffer[trsBytes++] = c;
        Serial.print(c);
        yield();
      }
    }
    // wait for serial to read all bytes (serial is wicked slow)
    if(trsBytes == TRSBUFF_SIZE){
      syncPrintfClr("\nRecieved %d byte(s) from TRS-80\n", trsBytes);
      
      // Parse TRS-80 buffer
      String req = String(trsBuffer);
      int sep = req.indexOf(';');
      String phone = req.substring(0, sep);
      String msg = req.substring(sep+1, req.length());
      
      msg.trim();
      syncPrintf("Phone number:\n%s\nMessage: %s\n", phone.c_str(), msg.c_str());
      delay(750);

      uint8_t status = sendSms(phone, msg);
      delay(750);
      if(status == 0){
        syncPrintf("Request successful\n");
      } else{
        syncPrintf("Request failed\n");
      }
      reset();
    }
  }
}


// reset global variables
void reset(){
  trsBytes = 0;
  trsBuffer[0] = '\0';
}


// set baud rate and init both serials
void initSerial(){
  Serial.begin(BAUD_RATE, SERIAL_8N1);
  trsSerial.begin(TRSBAUDRATE, SWSERIAL_8N1, D5, D6, false, 95, 11);
  
  /* Give some init time + switch to serial monitor */
  Serial.println();
  for(uint8_t t = 3; t > 0; t--){
    Serial.printf("WAIT %d...\n", t);
    Serial.flush();
    trsSerial.flush();
    delay(500);
  }
  Serial.println("\n* * * START * * *");
}


// setup OLED display and text properties
void initDisplay(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
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
  delay(500);
}


// reset OLED
void clearDisplay(){
  delay(500);
  display.clearDisplay();
  display.setCursor(0, 0);
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


// send request to Twilio SMS API, return status code
int sendSms(String phoneTo, String msg){
  WiFiClientSecure client;
  client.setFingerprint(_TWILIO_FINGERPRINT);

  if(!client.connect(_TWILIO_HOST, _TWILIO_PORT)){
    syncPrintfClr("Connection to Twilio API failed\n");
    return -1;
  }
  syncPrintfClr("Connected to\nTwilio API\n");

  String reqBody = "To=" + urlEncode(phoneTo) + 
                   "&From=" + urlEncode(String(_TWILIO_FROM)) + 
                   "&Body=" + urlEncode(msg);

  String http = "POST /2010-04-01/Accounts/" + String(_TWILIO_ACC) + 
                "/Messages.json HTTP/1.1\r\n" +
                getAuthHeader(_TWILIO_ACC, _TWILIO_AUTH) + "\r\n" + 
                "Host: " + String(_TWILIO_HOST) + "\r\n" +
                "Cache-control: no-cache\r\n" +
                "User-Agent: ESP8266 Twilio Example\r\n" +
                "Content-Type: " +
                "application/x-www-form-urlencoded\r\n" +
                "Content-Length: " + reqBody.length() +"\r\n" +
                "Connection: close\r\n" +
                "\r\n" + reqBody + "\r\n";

  client.print(http); // make request
  syncPrintf("Request sent\n");

  // receive headers
  while(client.connected()){
    String line = client.readStringUntil('\n');
    if(line == "\r"){
      syncPrintf("Headers received\n");
      break;
    }
  }

  // receive response, we only care about the status code
  while(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  return client.status();
}


// print a string to serial + OLED
void syncPrint(const char *s){
  Serial.print(s);
  display.print(s);
  display.display();
}


// https://github.com/zenmanenergy/ESP8266-Arduino-Examples
String urlEncode(String s){
  String encodedString = "";
  char c, code0, code1;
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
    }
    yield();
  }
  return encodedString;
}


// https://github.com/TwilioDevEd/twilio_esp8266_arduino_example/blob/master/twilio.cpp#L103
String getAuthHeader(const String& acc, const String& auth){
  size_t toencodeLen = acc.length() + auth.length() + 2;
  char toencode[toencodeLen];
  memset(toencode, 0, toencodeLen);
  snprintf(toencode, toencodeLen, "%s:%s", acc.c_str(), auth.c_str());

  String encoded = base64::encode((uint8_t*)toencode, toencodeLen-1);
  String encoded_string = String(encoded);
  std::string::size_type i = 0;

  // Strip newlines (after every 72 characters in spec)
  while(i < encoded_string.length()){
    i = encoded_string.indexOf('\n', i);
    if(i == -1) break;
    encoded_string.remove(i, 1);
  }
  return "Authorization: Basic " + encoded_string;
}
