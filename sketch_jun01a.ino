#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "Carlita";
char pass[] = "abcdefghijh"; // your network password
int tempPin = 0;
float temp;
int uvPin = 1;
float uv;


int status = WL_IDLE_STATUS;
IPAddress server(192,168,43,46);   // Google

// Initialize the client library
WiFiClient client;
WiFiServer wifiServer(80);

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }



  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(1000);
  }

  Serial.println("Testing");
  while ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    status = WiFi.begin(ssid, pass);
  }
   
  Serial.println("Connected to wifi");
  Serial.println("\nStarting connection...");
}

void loop() {
  // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      uv = analogRead(uvPin);
      uv = uv/1024*3.3;
      Serial.println("connected");
      // Make a HTTP request:
      String cl = "GET /ArduinoProject/ArduinoDatabaseConnection.php?UV=";
      //Here get the real value
      cl.concat(uv);
      cl.concat(" HTTP/1.1");
      client.println(cl);
      client.println("Host: 192.168.43.46");
      client.println("Connection: close");
      client.println();
      Serial.println("sent");
    }

    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      temp = analogRead(tempPin);
      temp = temp/1024;
      temp = temp * 5;
      temp = temp - 0.5;
      temp = temp * 100;
      Serial.println("connected");
      // Make a HTTP request:
      String cl = "GET /ArduinoProject/ArduinoDatabaseConnection.php?Temperature=";
      //Here get the real value
      cl.concat(temp);
      cl.concat(" HTTP/1.1");
      client.println(cl);
      client.println("Host: 192.168.43.46");
      client.println("Connection: close");
      client.println();
      Serial.println("sent");
    }
    
    delay(10000);
}
