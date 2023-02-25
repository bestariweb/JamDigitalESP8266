/****************************************************************************************************************************
  TimerInterruptTest.ino
  For ESP8266 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266TimerInterrupt
  Licensed under MIT license

  The ESP8266 timers are badly designed, using only 23-bit counter along with maximum 256 prescaler. They're only better than UNO / Mega.
  The ESP8266 has two hardware timers, but timer0 has been used for WiFi and it's not advisable to use. Only timer1 is available.
  The timer1's 23-bit counter terribly can count only up to 8,388,607. So the timer1 maximum interval is very short.
  Using 256 prescaler, maximum timer1 interval is only 26.843542 seconds !!!

  Now with these new 16 ISR-based timers, the maximum interval is practically unlimited (limited only by unsigned long miliseconds)
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/
/* Notes:
   Special design is necessary to share data between interrupt code and the rest of your program.
   Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
   variable can not spontaneously change. Because your function may change variables while your program is using them,
   the compiler needs this hint. But volatile alone is often not enough.

   When accessing shared variables, usually interrupts must be disabled. Even with volatile,
   if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
   If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
   or the entire sequence of your code which accesses the data.
*/

#if !defined(ESP8266)
  #error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "ESP8266TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     0

// Select a Timer Clock
#define USING_TIM_DIV1                true           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              false            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"
#include <virtuabotixRTC.h>
#include <DMDESP.h>
#include <fonts/Arial_Black_16.h>
#include <fonts/Verdana14b.h>
#include <fonts/Verdana18.h>
#include <fonts/Verdana18b.h>
#include <fonts/Droid_Sans_24.h>
#include <fonts/CooperBlack16.h>
#include <fonts/EMSansSP8x16.h>
#include <fonts/EMSansSP10x16.h>
#include <fonts/CourierNew18.h>

#include <fonts/ArialRoundedMTBold16b.h>
#include <fonts/SystemFont5x7.h>
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(2, 4, 5);


#include <Wire.h>
//#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>
#include <PrayerTimes.h>
// Set WiFi credentials
#define WIFI_SSID "Bestariwebhost.id"
#define WIFI_PASS "passwordwifianda"

//#define WIFI_SSID "GINSA"
//#define WIFI_PASS "Passwordwifi"

#define MAX_TRIAL 300

// Set AP credentials
#define AP_SSID "G3_NO2"
#define AP_PASS "Passwd_AP_Anda"

ESP8266WebServer server(80);
IPAddress    MyapIP(10, 8, 0, 1); 
IPAddress ipap ;
IPAddress iphs ;
// Define NTP Client to get time
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

typedef struct {
  double lat, lon, timezone;
} jws_location_setting_t;
jws_location_setting_t jws_loc_set = { -6.213684, 106.4227035, 7}; // Lokasi Tangerang
String iptype,ipstr,gatewaystr,subnetstr,primaryDNSstr,secondDNSstr;
String tampilkanJWSStr,tampilkanUcapanStr,tampilkanPengumumanStr,tipejamStr,tampilkanKalenderStr,lamajamStr,tipefontstr;
bool tampilkanPengumuman = true;
bool tampilkanUcapan = true;
bool tampilkanKalender = true;
bool tampilkanJWS = true;
int tipejam=1;
int tipefont = 8;
bool jamstart = false;
double prayer_times[sizeof(TimeName) / sizeof(char *)];
String textjwsalt,textjadwalsholat,imsak,subuh,dzuhur,ashar,maghrib,isya;
String content,st;
String formattedDate, YYYY, MM, DD, hhstr, mmstr, ssstr,jamStr,tgl,tglshort,jamshort;
uint16_t YYYYH;
byte MMH,DDH;
int hh, mm, ss, pewaktu,statusCode,hhS,hhD,hhA,hhM,hhI,mmS,mmD,mmA,mmM,mmI;
String ehssid, ehpass;
String essid;
String epass,eblauth,eblserver,epengumuman;
String ipstrap,ipstrhs;
//SETUP DMD
#define DISPLAYS_WIDE 3 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH); 

#define BUILTIN_LED     2       // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
int LAMAJAM = 30;
bool pernahconnect;
volatile bool statusLed = false;
bool webopened;
volatile uint32_t lastMillis = 0;
String daysOfTheWeek[] = {"MINGGU","SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU" };
String NamaBulan[] = {"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER"};
String namaBulanHijriah[] = {"MUHARRAM","SAFAR","RABIUL AWAL","RABIUL AKHIR","JUMADIL AWAL","JUMADIL AKHIR","RAJAB","SYA'BAN","RAMADHAN","SYAWAL","DZULKAIDAH","DZULHIJJAH"};
#define TIMER_INTERVAL_MS       20

// Init ESP8266 timer 1
ESP8266Timer ITimer;
int prognumber;
//=======================================================================
void IRAM_ATTR TimerHandler()
{
  static bool started = false;

  if (!started)
  {
    started = true;
    //Disp.refresh();
    Serial.println("Refresh pertama");
    //pinMode(BUILTIN_LED, OUTPUT);
  }
  Disp.refresh();
  Serial.println("Refresh berikutnya");
  //digitalWrite(BUILTIN_LED, statusLed);  //Toggle LED Pin
  //statusLed = !statusLed;

#if (TIMER_INTERRUPT_DEBUG > 0)
  Serial.println("Delta ms = " + String(millis() - lastMillis));
  lastMillis = millis();
#endif
}
//=======================================================================
//                               Setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
  while (!Serial);
  timeClient.begin();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(200); // Tingkat kecerahan
  Disp.setFont(Arial_Black_16); // Tentukan huruf
  
  delay(300);

  Serial.print(F("\nStarting TimerInterruptTest on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP8266_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);
  }
  else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));
  readeeprom();
  checkconnection();
  createWebServer();
  server.begin();
  Serial.println("Server dijalankan");
  prognumber=1;
  if (pernahconnect) UpdateRTCFromNTP();
  UpdateClockFromRTC();
  prayer_calc_init();
  GetHijriah(myRTC.dayofmonth,myRTC.month,myRTC.year,&DDH,&MMH,&YYYYH);
  //prayer_time_update(YYYY.toInt(),MM.toInt(),DD.toInt(),jws_loc_set, prayer_times);
  prayer_time_update(myRTC.year,myRTC.month,myRTC.dayofmonth,jws_loc_set, prayer_times);
  validasijws();
}
//=======================================================================
//                MAIN LOOP
//=======================================================================
void loop()
{
  Disp.loop(); // Jalankan Disp loop untuk refresh LED
  server.handleClient();
  if ((pernahconnect) && (eblauth.length()>5)){
    if (Blynk.connected()) {  
      Blynk.run();
    } else if ((hh==12) || (hh < 6)) {
      Serial.println("Reconnecting to Internet begin....");
      checkconnection();
    }
  }
  switch (prognumber){
    case 1:
          if ((mm==0) && (ss==0) && pernahconnect) UpdateRTCFromNTP();
          jambesar();
          break;
    case 2:if (tampilkanUcapan){

          if ((((hh==11) && (mm>58)) || (hh==12)) && (myRTC.dayofweek > 0) && (myRTC.dayofweek < 6)){
          agendaharian(0, 50,"Selamat beristirahat, Manfaatkan waktu istirahat untuk sholat dan makan ");
          } else if ((hh==16) && (mm>50) && (myRTC.dayofweek > 0) && (myRTC.dayofweek < 6)){
          agendaharian(0, 50,"Terimakasih kepada Shift 2 yang sudah datang lebih awal. Jangan lupa tukar informasi antar shift  ");
          } else if ((hh==17) && (mm<10) && (myRTC.dayofweek > 0) && (myRTC.dayofweek < 6)){
            agendaharian(0, 50,"Untuk shift 1 yang mau pulang, Hati-hati di jalan, keluarga menunggu di rumah ");
          } else if ((hh==7) && (mm>45) && (myRTC.dayofweek > 0) && (myRTC.dayofweek < 6)){
            agendaharian(0, 50,"Terimakasih kepada shift 1 yang sudah datang lebih awal ");
          } else {prognumber++;}
          break;
          } else {
            ++prognumber;
            break;
          }
    case 3:if (tampilkanJWS){
            jambesar3();break;
          } else {
            ++prognumber;
            break;
          }
    case 4:if (tampilkanKalender){
              Kalender(100);break;
            } else {
              ++prognumber;
              break;
            } 
    case 5:if (tampilkanPengumuman){
            DisplayPengumuman(0, 50);break;
          } else {
            ++prognumber;
            break;
          } 
    case 6:
          if (pernahconnect) UpdateRTCFromNTP();
          prayer_time_update(myRTC.year,myRTC.month,myRTC.dayofmonth,jws_loc_set, prayer_times);
          //prayer_time_update(YYYY.toInt(),MM.toInt(),DD.toInt(),jws_loc_set, prayer_times);
          validasijws();
          UpdateClockFromRTC();
          GetHijriah(myRTC.dayofmonth,myRTC.month,myRTC.year,&DDH,&MMH,&YYYYH);
          //GetHijriah(DD.toInt(),MM.toInt(),YYYY.toInt(),&DDH,&MMH,&YYYYH);
          prognumber=1;break;
  }
  //Serial.print("Prognumber: ");Serial.println(prognumber);
  //Serial.print("hh: ");Serial.println(hh);
}
