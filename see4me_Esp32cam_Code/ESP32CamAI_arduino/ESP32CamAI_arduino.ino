#include <WebSocketsServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "camera_wrap.h"


const char* ssid = "SEECS";    // <<< change this as yours
const char* password = "openaccess"; // <<< change this as yours
//holds the current upload
int cameraInitState = -1;
uint8_t* jpgBuff = new uint8_t[68123];
size_t   jpgLength = 0;
uint8_t camNo=0;
bool clientConnected = false;

//Creating UDP Listener Object. 
WiFiUDP UDPServer;
IPAddress addrRemote;
unsigned int portRemote;
unsigned int UDPPort = 6868;
const int RECVLENGTH = 16;
byte packetBuffer[RECVLENGTH];

WebSocketsServer webSocket = WebSocketsServer(86);
String html_home;

const int LED_BUILT_IN        = 4;
const uint8_t TRACK_DUTY      = 100;
const int PIN_SERVO_PITCH     = 12;
const int PINDC_LEFT_BACK     = 13;
const int PINDC_LEFT_FORWARD  = 15;
const int PINDC_RIGHT_BACK    = 14;
const int PINDC_RIGHT_FORWARD = 2;
const int LEFT_CHANNEL        = 2;
const int RIGHT_CHANNEL       = 3;
const int SERVO_PITCH_CHANNEL = 4;
const int SERVO_YAW_CHANNEL   = 5;
const int SERVO_RESOLUTION    = 16;
unsigned long previousMillisServo = 0;
const unsigned long intervalServo = 10;
int posServo = 75;
int PWMTrackHIGH = 138;
int PWMTrackLOW = 138;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
      case WStype_DISCONNECTED:
          Serial.printf("[%u] Disconnected!\n", num);
          camNo = num;
          clientConnected = false;
          break;
      case WStype_CONNECTED:
          Serial.printf("[%u] Connected!\n", num);
          clientConnected = true;
          break;
      case WStype_TEXT:
      case WStype_BIN:
      case WStype_ERROR:
      case WStype_FRAGMENT_TEXT_START:
      case WStype_FRAGMENT_BIN_START:
      case WStype_FRAGMENT:
      case WStype_FRAGMENT_FIN:
          Serial.println(type);
          break;
  }
}

void processUDPData(){
  int cb = UDPServer.parsePacket();

  if (cb) {
      UDPServer.read(packetBuffer, RECVLENGTH);
      addrRemote = UDPServer.remoteIP();
      portRemote = UDPServer.remotePort();

      String strPackage = String((const char*)packetBuffer);
  #ifdef DEBUG
      Serial.print("receive: ");
      Serial.print(strPackage);
      Serial.print(" from: ");
      Serial.print(addrRemote);
      Serial.print(":");
      Serial.println(portRemote);
  #endif
      if(strPackage.equals("whoami")){
          UDPServer.beginPacket(addrRemote, portRemote-1);
          String res = "ESP32-CAM";
          UDPServer.write((const uint8_t*)res.c_str(),res.length());
          UDPServer.endPacket();
          Serial.println("response");
      }else if(strPackage.equals("ledon")){
        digitalWrite(LED_BUILT_IN, HIGH);
      }else if(strPackage.equals("ledoff")){
        digitalWrite(LED_BUILT_IN, LOW);
      }

      memset(packetBuffer, 0, RECVLENGTH);
  }

}

void setup(void) {

  Serial.begin(115200);
  Serial.print("\n");
  #ifdef DEBUG
  Serial.setDebugOutput(true);
  #endif

  pinMode(LED_BUILT_IN, OUTPUT);
  digitalWrite(LED_BUILT_IN, LOW);

  cameraInitState = initCamera();

  Serial.printf("camera init state %d\n", cameraInitState);

  if(cameraInitState != 0){
    return;
  }

  //WIFI INIT
  Serial.printf("Connecting to %s\n", ssid);
  if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  String ipAddress = WiFi.localIP().toString();;
  Serial.println(ipAddress);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  UDPServer.begin(UDPPort); 
}

void loop(void) {
  webSocket.loop();
  if(clientConnected == true){
    grabImage(jpgLength, jpgBuff);
    webSocket.sendBIN(camNo, jpgBuff, jpgLength);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisServo >= intervalServo) {
    previousMillisServo = currentMillis;
    processUDPData();
  }

  
}



