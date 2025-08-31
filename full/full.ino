#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "BeaconMonitor.h"
#include <CycleDockManager.h>

// WiFi
#define WIFI_SSID "Galaxy Tab A72113"

#define WIFI_PASSWORD "Apoorva167"


// Firebase
#define API_KEY "AIzaSyA1d9_rzP2hWgFgDzvbxsCvM-7FI-XlNHA"

#define DATABASE_URL  "https://page-a3cca-default-rtdb.asia-southeast1.firebasedatabase.app"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const char* location = "station2";

// Known MAC addresses
const char* beaconMACs[] = {
  "AA:BB:CC:11:22:01",
  "AA:BB:CC:11:22:02",
  "AA:BB:CC:11:22:03",
  "AA:BB:CC:11:22:04",
  "AA:BB:CC:11:22:05",
  "60:77:71:8E:74:1B", 
  "60:77:71:8E:63:12", 
};

BeaconMonitor monitor(beaconMACs, 7, location, &fbdo);
CycleDockManager dockManager(
  "Galaxy Tab A72113",
 "Apoorva167",
  "AIzaSyA1d9_rzP2hWgFgDzvbxsCvM-7FI-XlNHA",
  "https://page-a3cca-default-rtdb.asia-southeast1.firebasedatabase.app",
  "location2"  // <- Replace with actual location
);
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi connected");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = "apoorva1276@gmail.com";
  auth.user.password = "12thjune2006";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  monitor.begin();
  
  dockManager.addCycle("cycle1", 26, 32, 33, 100.0);
  dockManager.addCycle("cycle2", 27, 25, 26, 2.0);

  dockManager.begin([](TokenInfo info) {
    Serial.println("Firebase token ready.");
  });
}

void loop() {
  monitor.scanAndUpdate();
  delay(10000); // Scan every 10s
  dockManager.checkAllCycles();
  delay(5000);
}
