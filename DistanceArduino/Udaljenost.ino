#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "" // Insert Firebase HOST
#define FIREBASE_AUTH "" // Insert Firebase AUTH
#define WIFI_SSID "" //Insert WiFi Name
#define WIFI_PASSWORD "" //Insert WiFi password

const int trigPin = D5;
const int echoPin = D6;

FirebaseJson json;
FirebaseData firebasedata;

#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distanceCm = duration * SOUND_VELOCITY/2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  json.set("/distance",distanceCm);
  Firebase.updateNode(firebasedata,"/Distance",json);
  delay(1000);
}