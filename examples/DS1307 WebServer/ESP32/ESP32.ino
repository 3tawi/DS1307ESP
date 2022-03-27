//  DS1307ESP Edited by 3tawi
//  DS1307ESP Library: https://github.com/3tawi/DS1307ESP
//  Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects


#include <WiFi.h>
#include <WebServer.h>
#include <DS1307ESP.h>
#include "index.h"

DS1307ESP rtc;
WebServer server(80);

char ssid[] = "your-ssid";
char pass[] = "your-password";
const char* Apssid = "Espxx";
const char* Appassword = "3tawi-GP";
  IPAddress ip(192, 168, 1, 62); // http://192.168.1.62
  IPAddress dns(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress gatewayap(192, 168, 4, 1); // http://192.168.4.1
  IPAddress subnet(255, 255, 255, 0);

uint32_t lastTime;   
int Tz = 1; // Time Zone 
String text;  
int fon = 0; // language 0 = EN  |  1 = FR  |  2 = GR 
String langfont[3] = {"EN", "FR", "GR"}; 

void(* resetFunc) (void) = 0;//declare reset function at address 0

void getWifi() {
  WiFi.config(ip, dns, gateway, subnet); 
  WiFi.begin(ssid, pass);
  int xc = 0;
  while (WiFi.status() != WL_CONNECTED && xc < 10) {
    delay(500);
    xc++;
  }
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.print("CONNECTED To: ");
    Serial.println(ssid);
    Serial.print("IP Address: http://");
    Serial.println(WiFi.localIP().toString().c_str());
    WiFi.softAPdisconnect(true);
    } else { 
    WiFi.softAPConfig(ip, gatewayap, subnet);
    WiFi.softAP(Apssid, Appassword);
    Serial.print("CONNECTED To: ");
    Serial.print(Apssid);
    Serial.print(" Password: ");
    Serial.println(Appassword);
    Serial.print("IP Address: http://");
    Serial.println(WiFi.softAPIP().toString().c_str());
    }
}
  void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}
void handlezoneTime() {
    handleRoot();
    Tz = server.arg("locatz").toInt(); 
    Serial.println("Zone Time Update ");
}
void handlelocaltime() {
    rtc.DSadjust(server.arg("locadt").toInt() + (Tz * 3600)); 
    handleRoot();
    Serial.println("Local Time Update");
}
void handleMyTime() { 
    handleRoot(); 
    String hbuf = server.arg("htmie"); 
    String dbuf = server.arg("ddate");
    text = hbuf[0];
    text += hbuf[1];
    int h = text.toInt(); 
    text = hbuf[3];
    text += hbuf[4];
    int m = text.toInt(); 
    text = hbuf[6];
    text += hbuf[7];
    int s = text.toInt();
    
    text = dbuf[0];
    text += dbuf[1];
    text += dbuf[2];
    text += dbuf[3];
    int yr = text.toInt(); 
    text = dbuf[5];
    text += dbuf[6];
    int mo = text.toInt();
    text = dbuf[8];
    text += dbuf[9];
    int dd = text.toInt();
  rtc.DSadjust(h, m, s, yr, mo, dd); 
  Serial.println("Manually Time Update");
}
void handleChangefont() {  
    handleRoot();
    fon++;
    fon%=3;
    rtc.SetFont(fon);
}
void handlestate() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += Tz;
  content += "</analog><analog>";
  content += langfont[fon];
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handleRestesp() {  
    handleRoot();
    delay(4000);     
    resetFunc();
}
void setup() {
  Serial.begin(115200);
  getWifi(); 
  rtc.begin(); // The SDA and SCL lines of the I2C bus come from GPIO21 and GPIO22 of the ESP32 board (respectively)
  server.on("/", handleRoot); 
  server.on("/mytimezon", handlezoneTime); 
  server.on("/localdatime", handlelocaltime);
  server.on("/restime", handleMyTime);
  server.on("/readtemhu", handlestate); 
  server.on("/restesp", handleRestesp);
  server.on("/changefont", handleChangefont);
  server.begin();
}
void loop() {

  server.handleClient();
   if(millis() - lastTime >= 1000) {
  updateTime();
  lastTime = millis();
  }
}
void updateTime()
{
      rtc.DSread(); 
      Serial.println(rtc.getTime());          //  (String) 00:00:03
      Serial.println(rtc.getTime(true));      //  (String) 12:00:03
      Serial.println(rtc.getDate());          //  (String) Mon, 14 Mar 2022
      Serial.println(rtc.getDate(true));      //  (String) Monday, 14-March-2022
} 