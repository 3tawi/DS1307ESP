//  DS1307ESP Edited by 3tawi
//  DS1307ESP Library: https://github.com/3tawi/DS1307ESP
//  Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <DS1307ESP.h>

DS1307ESP rtc;

uint32_t lastTime; 
// uint8_t sdapin = 12, sclpin = 14; 

void setup() {
  Serial.begin(115200);
// The SDA and SCL lines of the I2C bus come from GPIO21 and GPIO22 of the ESP32 board (respectively)
// The SDA and SCL lines of the I2C bus come from GPIO4 (D2) and GPIO5 (D1) of the NodeMCU ESP8266 board (respectively)
   rtc.begin(); 
// rtc.begin(sdapin, sclpin);                     
   rtc.DSadjust(0, 19, 21, 2022, 3, 16); // 00:19:21 16 Mar 2022
// rtc.DSadjust(1647216003); // 00:00:03 14 Mar 2022
// rtc.SetFont(0);                         //  language 0 = EN  |  1 = FR  |  2 = GR 
}
void loop() {
   if(millis() - lastTime >= 1000) {
    updateTime();
    lastTime = millis();
    }
}
void updateTime()
{
      rtc.DSread(); 
      Serial.println(rtc.getMahmin(true));      //  (String) true = 00:00  false = 00 00  (24h)
      Serial.println(rtc.getMihmin(true));      //  (String) true = 12:00  false = 12 00  (12h)
      Serial.println(rtc.getTime());          //  (String) 00:00:03  (24h)
      Serial.println(rtc.getTime(true));      //  (String) 12:00:03  (12h)
      Serial.println(rtc.getDate());          //  (String) Mon, 14 Mar 2022
      Serial.println(rtc.getDate(true));      //  (String) Monday, 14-March-2022
      Serial.println(rtc.getDateTime());      //  (String) Mon, 14 Mar 2022 00:09:21
      Serial.println(rtc.getDateTime(true));  //  (String) Monday, 14-March-2022 00:09:21
      Serial.println(rtc.getTimeDate());      //  (String) 12:07:18 Mon, 14 Mar 2022
      Serial.println(rtc.getTimeDate(true));  //  (String) 00:00:03 Monday, 14-March-2022
      Serial.println(""); 
      Serial.println(rtc.getEpoch());         //  (long)    1647216003
      Serial.println(rtc.getSecond());        //  (String)     30    (00-59)
      Serial.println(rtc.getMinute());        //  (String)     58    (00-59)
      Serial.println(rtc.getHour());          //  (String)     12    (01-12)
      Serial.println(rtc.getHour(true));      //  (String)     00    (00-23)
      Serial.println(rtc.getDay());           //  (String)     14    (1-31)
      Serial.println(rtc.getMonth());         //  (String)     Mar
      Serial.println(rtc.getMonth(true));     //  (String)     March
      Serial.println(rtc.getYear());          //  (String)     2022
      Serial.println(rtc.getDayofWeek());     //  (String)     Mon
      Serial.println(rtc.getDayofWeek(true)); //  (String)     Monday
      Serial.println(rtc.getAmPm());          //  (String)  pm
      Serial.println(rtc.getAmPm(true));      //  (String)  PM
      Serial.println(""); 
      Serial.println(rtc.getSecond());        //  (int)     30    (0-59)
      Serial.println(rtc.getMinute());        //  (int)     58    (0-59)
      Serial.println(rtc.hour);               //  (int)     0     (0-23)
      Serial.println(rtc.dayOfMonth);         //  (int)     14    (1-31)
      Serial.println(rtc.month);              //  (int)     3     (1-12)
      Serial.println(rtc.year + 2000);        //  (int)     2022
      Serial.println(rtc.dayOfWeek);          //  (int)     1     (0-6)
      Serial.println(rtc.DayofYear);          //  (int)     73    (0-365)
      Serial.println(""); 
} 