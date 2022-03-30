
#include "DS1307ESP.h"
#include <Wire.h>



uint16_t DS1307ESP::yeardays(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; i++)
        days += daysInMonth[i - 1];
    if (m > 2 && y % 4 == 0)
        days++;
    return days;
}

uint16_t DS1307ESP::date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; i++)
        days += daysInMonth[i - 1];
    if (m > 2 && y % 4 == 0)
        days++;
    return days + 365 * y + (y + 3) / 4 - 1;
}

long DS1307ESP::time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

uint8_t DS1307ESP::decToBcd(uint8_t val) {
    return ((val / 10 * 16) + (val % 10));
}

uint8_t DS1307ESP::bcdToDec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

long DS1307ESP::getEpoch() {
    uint16_t days = date2days(year, month, dayOfMonth);
    uint32_t t = time2long(days, hour, minute, second);
    t += SECONDS_FROM_1970_TO_2000;
    return t;
}

String DS1307ESP::getAmPm(bool mode){
  if (hour >= 12) {
    if (mode) { return "pm"; }
    else { return "PM"; }
  }
  else {
    if (mode) { return "am"; }
    else { return "AM"; }
  }
}

String DS1307ESP::getMahmin(bool mode){
  char s[10];
  if (mode) { sprintf(s, "%02d:%02d", hour, minute); }
  else { sprintf(s, "%02d %02d", hour, minute); }
  return String(s);
}

String DS1307ESP::getMihmin(bool mode){
  char s[10];
    if (hour > 12) {
      if (mode) { sprintf(s, "%02d:%02d", hour-12, minute); }
      else { sprintf(s, "%02d %02d", hour-12, minute); } }
    else if (hour == 0) {
      if (mode) { sprintf(s, "%s:%02d", "12", minute); }
      else { sprintf(s, "%s %02d", "12", minute); } }
    else { 
      if (mode) { sprintf(s, "%02d:%02d", hour, minute); }
      else { sprintf(s, "%02d %02d", hour, minute); } }
  return String(s);
}

String DS1307ESP::getDate(bool mode){
  char s[51];
  if (mode)
  { sprintf(s, "%s, %02d %s %04d", daytostrFull[dayOfWeek], dayOfMonth, MonthtostrFull[month-1], year+2000); }
  else
  { sprintf(s, "%s, %02d %s %04d", daytostr[dayOfWeek], dayOfMonth, Monthtostr[month-1], year+2000); }
  return String(s);
}

String DS1307ESP::getDayDate(){
  char s[12];
  sprintf(s, "%04d-%02d-%02d", year+2000, month, dayOfMonth);
  return String(s);
}

String DS1307ESP::getTime(bool mode){
  char s[10];
  if (mode)
  { sprintf(s, "%02d:%02d:%02d", hour, minute, second); }
  else
  {
    if (hour > 12)
    { sprintf(s, "%02d:%02d:%02d", hour-12, minute, second); }
    else if (hour == 0)
    { sprintf(s, "%s:%02d:%02d", "12", minute, second); }
    else
    { sprintf(s, "%02d:%02d:%02d", hour, minute, second); }
  }
  return String(s);
}

String DS1307ESP::getDateTime(bool mode){
 String dtime = getDate(mode);
  dtime += " ";
  dtime += getTime(mode);
  return dtime;
}

String DS1307ESP::getTimeDate(bool mode){
 String dtime = getTime(mode);
  dtime += " ";
  dtime += getDate(mode);
  return dtime;
}

String DS1307ESP::getHour(bool mode){
  char s[2];
  if (mode) {
    if (hour > 12) { sprintf(s, "%02d", hour-12); }
    else if (hour == 0) { sprintf(s, "%s", "12"); }
    else  { sprintf(s, "%02d", hour); } }
  else {
    sprintf(s, "%02d", hour); }
  return String(s);
}

String DS1307ESP::getMinute(){
  char s[2];
  sprintf(s, "%02d", minute);
  return String(s);
}

String DS1307ESP::getSecond(){
  char s[2];
  sprintf(s, "%02d", second);
  return String(s);
}

String DS1307ESP::getDayofWeek(bool mode){
  char s[51];
  if (mode)
  { sprintf(s, "%s", daytostr[dayOfWeek]); }
  else
  { sprintf(s, "%s", daytostrFull[dayOfWeek]); }
  return String(s);
}

String DS1307ESP::getYear() {
  char s[4];
  sprintf(s, "%04d", year + 2000);
  return String(s);
}

String DS1307ESP::getMonth(bool mode){
  char s[21];
  if (mode)
  { sprintf(s, "%s", Monthtostr[month-1]); }
  else
  { sprintf(s, "%s", MonthtostrFull[month-1]); }
  return String(s);
}

String DS1307ESP::getDay(){
  char s[2];
  sprintf(s, "%02d", dayOfMonth);
  return String(s);
}

void DS1307ESP::begin() {
    Wire.begin();
    SetFont(0);
}

void DS1307ESP::begin(uint8_t sda, uint8_t scl) {
    Wire.begin(sda, scl);
    SetFont(0);
}

void DS1307ESP::SetFont(int fon) {
   if(fon > 2 || fon < 0) { fon = 0; }
    switch (fon) { 
      case 0:
       for(int i=0; i < 12; i++) {
  MonthtostrFull[i] = MonthtostrFullEN[i];
  Monthtostr[i] = MonthtostrEN[i];
  if(i < 7) {
  daytostrFull[i] = daytostrFullEN[i];
  daytostr[i] = daytostrEN[i];
      }
      }
      break;

      case 1:
       for(int i=0; i < 12; i++) {
  MonthtostrFull[i] = MonthtostrFullFR[i];
  Monthtostr[i] = MonthtostrFR[i];
  if(i < 7) {
  daytostrFull[i] = daytostrFullFR[i];
  daytostr[i] = daytostrFR[i];
      }
      }
      break;

      case 2:
       for(int i=0; i < 12; i++) {
  MonthtostrFull[i] = MonthtostrFullGR[i];
  Monthtostr[i] = MonthtostrGR[i];
  if(i < 7) {
  daytostrFull[i] = daytostrFullGR[i];
  daytostr[i] = daytostrGR[i];
      }
      }
      break;

      default:
      break;
      }
}

void DS1307ESP::DSread() {
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    second     = bcdToDec(Wire.read() & 0x7f);
    minute     = bcdToDec(Wire.read());
    hour       = bcdToDec(Wire.read() & 0x3f);
    dayOfWeek  = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month      = bcdToDec(Wire.read());
    year       = bcdToDec(Wire.read());
    DayofYear  = yeardays(year, month, dayOfMonth);
}

void DS1307ESP::DSwrite() {
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(second));
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour));
    Wire.write(decToBcd(dayOfWeek));
    Wire.write(decToBcd(dayOfMonth));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();
}

void DS1307ESP::DSadjust(uint8_t _hour, uint8_t _minute, uint8_t _second, uint16_t _year, uint8_t _month, uint8_t _day) {
    // assign variables
    hour = _hour;
    minute = _minute;
    second = _second;
    year = _year - 2000;
    month = _month;
    dayOfMonth = _day;
    uint16_t day = date2days(year, month, dayOfMonth);
    dayOfWeek = (day + 6) % 7;
    DSwrite();
}

void DS1307ESP::DSadjust(uint32_t t) {
    t -= SECONDS_FROM_1970_TO_2000; // bring to 2000 timestamp from 1970
    second = t % 60;
    t /= 60;
    minute = t % 60;
    t /= 60;
    hour = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (year = 0; ;year++) {
        leap = year % 4 == 0;
        if (days < 365u + leap)
            break;
        days -= 365 + leap;
    }

    for (month = 1; ; month++) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + month - 1);
        if (leap && month == 2)
            daysPerMonth++;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }

    dayOfMonth = days + 1;
    uint16_t day = date2days(year, month, dayOfMonth);
    dayOfWeek = (day + 6) % 7;
    DSwrite();
}
