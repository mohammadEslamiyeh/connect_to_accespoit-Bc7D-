#include <ESP8266WiFi.h>
const char *ssid = "AndroidShare_9141";
const char *password = "941a5577c57b";
const char *host = "www.google.com";
const uint16_t port = 80; 

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println();
 Serial.print("connect to ");
 Serial.print(ssid);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid,password);
 while(WiFi.status() !=WL_CONNECTED){
  delay(5000);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("WIFI conected");
 Serial.println("IP address : ");
 Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print ("connecting to ");
Serial.print(host);
Serial.print(":");
Serial.print(port);
WiFiClient client;
if(!client.connect (host,port)){
Serial.println("connection failed");  
delay(5000);
return;
}
Serial.println("sending data to server");
if (client.connected()){
  client.println("hello from ESP0266");
}
unsigned long timeout = millis();
while(client.available()==0){
  if (millis()- timeout > 5000){
    Serial.println(">>>>> client timeout");
    client.stop();
    delay(6000);
    return;
  }
}
Serial.println("receiving from remote server ");
while (client.available()){
char ch = static_cast<char> (client.read());
Serial.print(ch);  
}
Serial.println();
Serial.println("closing connection");
client.stop();
delay(30000);
}
