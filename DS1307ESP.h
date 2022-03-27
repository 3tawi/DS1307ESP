

#ifndef DS1307ESP_H
#define DS1307ESP_H

#include <Arduino.h>

#define SECONDS_FROM_1970_TO_2000 946684800L
#define DS1307_I2C_ADDRESS 0x68
const uint8_t daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const String MonthtostrFullEN[12] ={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
const String MonthtostrEN[12]     ={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String daytostrFullEN[7]    ={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const String daytostrEN[7]        ={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const String MonthtostrFullFR[12] ={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};
const String MonthtostrFR[12]     ={"Jan", "Fev", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String daytostrFullFR[7]    ={"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const String daytostrFR[7]        ={"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"} ; 

const String MonthtostrFullGR[12] ={"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
const String MonthtostrGR[12]     ={"Jan", "Feb", "März", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};
const String daytostrFullGR[7]    ={"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
const String daytostrGR[7]        ={"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"}; 

class DS1307ESP {
       private:
               uint8_t decToBcd(uint8_t val);
               uint8_t bcdToDec(uint8_t val);
               uint16_t date2days(uint16_t y, uint8_t m, uint8_t d);
               uint16_t yeardays(uint16_t y, uint8_t m, uint8_t d);
               long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s);
               void DSwrite();
  public:
    void DSadjust(uint8_t _hour, uint8_t _minute, uint8_t _second, uint16_t _year, uint8_t _month, uint8_t _day);
    void SetFont(int fon);
    void begin();
    void begin(uint8_t sda, uint8_t scl);
    void DSadjust(uint32_t t);
    void DSread();
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t dayOfWeek;
    uint8_t dayOfMonth;
    uint8_t month;
    uint16_t year;
    uint8_t DayofYear;

    String MonthtostrFull[12];
    String Monthtostr[12];
    String daytostrFull[7];
    String daytostr[7];

    String getAmPm(bool mode = false);
    String getDayofWeek(bool mode = false);
    String getDate(bool mode = false);
    String getTime(bool mode = false);
    String getDateTime(bool mode = false);
    String getTimeDate(bool mode = false);
    String getMahmin(bool mode);
    String getMihmin(bool mode);
    String getYear();
    String getDay();
    String getMonth(bool mode = false);
    String getHour(bool mode = false);
    String getMinute();
    String getSecond();

    long getEpoch();

};

#endif
