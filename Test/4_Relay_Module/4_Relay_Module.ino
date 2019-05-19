//Aquaponics System - IOT Project
//Charles Hopman

//Control 4 relay module using the firebase

//--------------------------------------------------------//
// Uncomment to create the database on your               //
// firebase realtime database as required in this project //
//--------------------------------------------------------//

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

//----------------------------------------------------------------------------------------------

//--------------------------------------4 RELAY MODULE------------------------------------------

#define Relay1 5  //GPIO5 = D1
int Rel1 = 0;
#define Relay2 4  //GPIO4 = D2
int Rel2 = 1;
#define Relay3 14 //GPIO14 = D5
int Rel3;
#define Relay4 12 //GPIO12 = D6
int Rel4;

void RelaySetup() {
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
}

void RelayModule() {
  //check and turn on/off the switch
  Firebase.getInt(firebasedata, "/S1");
  Rel1 = firebasedata.intData();
  Serial.println(firebasedata.intData());
  if (Rel1 == 1)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Relay 1 ON ");
  }
  else if (Rel1 == 0)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay 1 OFF");
  }

  Firebase.getInt(firebasedata, "/S2");
  Rel2 = firebasedata.intData();
  Serial.println(firebasedata.intData());
  if (Rel2 == 1)
  {
    digitalWrite(Relay2, LOW);
    Serial.println("Relay 2 ON");
  }
  else if (Rel2 == 0)
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("Relay 2 OFF");
  }


  Firebase.getInt(firebasedata, "/S3");
  Rel3 = firebasedata.intData();
  Serial.println(firebasedata.intData());
  if (Rel3 == 1)
  {
    digitalWrite(Relay3, LOW);
    Serial.println("Relay 3 ON");
  }
  else if (Rel3 == 0)
  {
    digitalWrite(Relay3, HIGH);
    Serial.println("Relay 3 OFF");
  }


  Firebase.getInt(firebasedata, "/S4");
  Rel4 = firebasedata.intData();
  Serial.println(firebasedata.intData());
  if (Rel4 == 1)
  {
    digitalWrite(Relay4, LOW);
    Serial.println("Relay 4 ON");
  }
  else if (Rel4 == 0)
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("Relay 4 OFF");
  }
}

//--------------------------------------------------------------------------------------------

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
  RelayModule();
}
