#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFi.h>

#define USER_BUTTON_PIN 0

void connectToSocket(const String& ip);
void connectToWiFi(const String& wifiName, const String& wifiPassword);
void registerRequests(const String& message);
void endSocket();

void setup() {
  Serial.begin(9600);
  pinMode(USER_BUTTON_PIN, INPUT_PULLUP);
  connectToWiFi("JIAOMI", "amJatcha");
  connectToSocket("ip:3001");
}

void loop() {
}

void connectToWiFi(const String& wifiName, const String& wifiPassword) {
  Serial.print("Connecting to WiFi: ");
  Serial.println(wifiName);
  
  WiFi.begin(wifiName.c_str(), wifiPassword.c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected to WiFi: ");
  Serial.println(wifiName);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

WiFiClient client;
void connectToSocket(const String& ip) {
  
  // parse the port from the value $ip:$port in ip
  int port = ip.substring(ip.indexOf(":") + 1).toInt();

  if (!client.connect(ip.substring(0, ip.indexOf(":")).c_str(), port)) {
    Serial.print("Connection failed for ");
    Serial.print(ip.substring(0, ip.indexOf(":")).c_str());
    Serial.print(":");
    Serial.println(port);
    return;
  }
  
  Serial.println("Connected to socket");
  
}

void registerRequests(const String& message) {
  int spaceIndex = message.indexOf(" ");
  if (spaceIndex != -1) {
    int numRequests = message.substring(0, spaceIndex).toInt();
    String ipAddress = message.substring(spaceIndex + 1);
    
    for (int i = 0; i < numRequests; i++) {
      client.print("GET / HTTP/1.1\r\nHost: ");
      client.print(ipAddress);
      client.print("\r\nConnection: close\r\n\r\n");
    }
  }
}

void endSocket() {
  client.stop();
}
