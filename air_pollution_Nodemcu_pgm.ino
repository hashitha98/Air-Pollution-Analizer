#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "**********"
#define FIREBASE_AUTH "***************************************"
#define WIFI_SSID "********"
#define WIFI_PASSWORD "************"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);

  if (Firebase.setInt(firebaseData, "/LED_Status", 1)) {
    Serial.println("Set int data success");
  } else {
    Serial.print("Error in setInt, ");
    Serial.println(firebaseData.errorReason());
  }
  if (Firebase.getInt(firebaseData, "/LED_Status")) {
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());

  } else {
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }

}
int i = 0;
void loop() {
  Firebase.setInt(firebaseData, "hum", random(0, 100) );
  Firebase.setInt(firebaseData, "temp", random(10, 50));
  Firebase.setInt(firebaseData, "airpo", random(0, 500));
  i++;
  delay(5000);
}
