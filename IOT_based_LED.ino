#include <Wi-Fi.h>
const char *ssid="";
const char *password="";
WiFiServerserver(80);
String header;
String ouput2State="off";
const int output2=2;
void setup()
{
    Serial.begin(115200);
    pinMode(output2,OUTPUT);
    digitalWrite(output2,LOW);
    Serial.print("Connecting to");
    Serial.println(ssid);
    WiFi.begin(ssid,password);
    while(WiFi.status()!=WL_CONNECTED)
    {
      delay(500);
      Serial.println(".");
    }
    //Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    WiFiClient client=server.available();
    if(client)
    {
      Serial.println("New Client.");
      String currentLine="";
      while(client.connected())
      {
        if(client.available())
        {
          char c=client.read();
          Serial.write(c);
          header+=c;
          if(c=='\n')
          {
            if(currentLine.length()==0)
            {
              client.println("HTTP/1.1200 OK");
              client.println("Content-type:text/hmtl");
              client.println("Connection:close");
              client.println():
              if(header.indexOf("GET/2/on")>=0)
              {
                Serial.println("GPIO 2 on");
                output2state="on";
                digitalWrite(output2,HIGH);
              }
              else if(header.indexOf("GET/2/off")>=0)
              {
                Serial.println("GPIO 2 off");
                output2state="off");
                digitalWrite(output2,LOW);
              }
              client.println("<!DOCTYPE hmtl><hmtl>");
              client.println("<head><meta name=\"viewport\"ocntent=\"width=device-width,initial-scale=1\">");
            }
          }
        }
      }

}
