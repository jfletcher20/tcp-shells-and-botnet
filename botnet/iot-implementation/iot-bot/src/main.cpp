#include <Arduino.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define USER_BUTTON_PIN 0

void connectToSocket();
void connectToWiFi(const String& wifiName, const String& wifiPassword);
void registerRequests(const String& message);
void endSocket();

WiFiClient client;

const char *serverIp = "ipaddress", *serverPort = "3001";

void setup() {
  Serial.begin(9600);
  pinMode(USER_BUTTON_PIN, INPUT_PULLUP);
  connectToWiFi("JIAOMI", "amJatcha");
  connectToSocket();
}

void loop() {
  // reset the socket if the user button is pressed; make sure  to add a debouncing delay

  if (digitalRead(USER_BUTTON_PIN) == LOW) {
    endSocket();
    delay(1000);
    connectToSocket();
  }

  if (client.available()) {
    String message = client.readStringUntil('\n');
    message.trim();
    if (message == "close connections") {
      Serial.println("Closing connection to server socket.");
      endSocket();
    } else {
      Serial.println("Registering " + message + " request... ");
      registerRequests(message);
    }
  }
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

void connectToSocket() {

  int port = ((String) serverPort).toInt();
  client.setTimeout(5);

  // print message that we are starting to connect to socket at ip and port
  Serial.print("Connecting to socket at ");
  Serial.print(serverIp);
  Serial.print(":");
  Serial.println(port);

  if (!client.connect(serverIp, port)) {
    Serial.print("Connection failed for ");
    Serial.print(serverIp);
    Serial.print(":");
    Serial.println(port);
    return;
  }
  
  Serial.println("Connected to socket");
  
}

HTTPClient http;
void registerRequests(const String& message) {
  int spaceIndex = message.indexOf(" ");
  if (spaceIndex != -1) {
    int numRequests = message.substring(0, spaceIndex).toInt();
    String ipAddress = message.substring(spaceIndex + 1);
    int port = message.substring(spaceIndex + 1).toInt();
    http.begin(client, serverIp, port, "/", false);
    for (int i = 0; i < numRequests; i++) {
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("HTTP GET request to %s returned code %d\n", ipAddress.c_str(), httpCode);
      } else {
        Serial.printf("HTTP GET request to %s failed, error: %s\n", ipAddress.c_str(), http.errorToString(httpCode).c_str());
      }
      client.flush();
      http.end();
    }
  }
}

void endSocket() {
  client.stop();
}
