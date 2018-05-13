#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// -------// Config //--------
#define WIFI_SSID "MaxHome3BB"
#define WIFI_PASSWORD "987654321"

#define UDP_LOCAL_PORT 887
#define MAX_INCOMING_BUFFER_SIZE 10
// ---------------------------

WiFiUDP Udp;

void setup() {
  // Setup Serial of debug
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" connected");  
  
  // Setup UDP
  Udp.begin(UDP_LOCAL_PORT);

  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), UDP_LOCAL_PORT);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    char incomingPacket[MAX_INCOMING_BUFFER_SIZE];
    int len = Udp.read(incomingPacket, MAX_INCOMING_BUFFER_SIZE);
    incomingPacket[len] = 0;
    Serial.printf("UDP packet contents: %s\n", incomingPacket);


    // Check pattern
    if (strcmp(incomingPacket, "IP") == 0) {
      // send back a reply, to the IP address and port we got the packet from
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write("OK");
      Udp.endPacket();
    }
  }
  
  delay(0); // nop
}
