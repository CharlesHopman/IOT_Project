//Aquaponics System - IOT Project
//Charles Hopman

//Connect to WiFi and Firebase

#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
Ticker ticker;

#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#define FirebaseHost "your-project-name.firebaseio.com"
#define FirebaseAuth "EnterYourFirebaseAuthKey"
FirebaseData firebasedata;

//-------------------------------WIFI-------------------------------------------------
void tick() {
  int state = digitalRead(BUILTIN_LED); //current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

void WifiConnect() {
  pinMode(BUILTIN_LED, OUTPUT);
  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.6, tick);

  WiFiManager wifiManager;

  wifiManager.setAPCallback(configModeCallback);

  if (!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();

  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);
}
//-------------------------------------FIREBASE-------------------------------------------
void FirebaseConnect() {
  Serial.print("Connecting to Firebase");
  Firebase.begin(FirebaseHost, FirebaseAuth);
}

//void CreateDatabase() {
//  Firebase.setInt(firebasedata, "/S1", 0);
//  Firebase.setInt(firebasedata, "/S2", 0);
//  Firebase.setInt(firebasedata, "/S3", 0);
//  Firebase.setInt(firebasedata, "/S4", 0);
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WifiConnect();
  RelaySetup();
  FirebaseConnect();
  //  CreateDatabase();
}

void loop() {
  // put your main code here, to run repeatedly:

}
