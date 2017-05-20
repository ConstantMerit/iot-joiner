#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "test";          // Declare access point SSID
const char* password = "password";  // Declare access point password
int pinLED = 2;                     // Declare LED pin (GPIO2)
ESP8266WebServer server(80);        // Declare server (port 80)

void setup() {
  // Set up access point:
  delay(1000);                                  // Wait 1 second
  Serial.begin(115200);                         // Start upload at 115200 baud
  Serial.println();                             // Print empty line
  Serial.println("Configuring access point!");  // Print text
  WiFi.softAP(ssid, password);                  // Create access point
  IPAddress myIP = WiFi.softAPIP();             // Locate IP address
  Serial.print("Access point IP address: ");    // Print text
  Serial.println(myIP);                         // Print IP address
  server.on("/", handleRoot);                   // Server content to root
  server.begin();                               // Start server
  Serial.println("HTTP server started!");       // Print text

  // Set up LED pin:
  pinMode(pinLED, OUTPUT);                      // Set as output pin
}

void loop() {
  // Operate server:
  server.handleClient();      // Handle incoming client requests

  // Operate LED:
  digitalWrite(pinLED, HIGH); // Turn LED on
  delay(1000);                // Wait 1 second
  digitalWrite(pinLED, LOW);  // Turn LED off
  delay(1000);                // Wait 1 second
}

void handleRoot() {
  // Respond to server with this content:
  server.send(200, "text/html", "You are connected!"); // Show connection status
}
