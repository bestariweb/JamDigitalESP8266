
void UpdateRTCFromNTP(){
  //myRTC.updateTime(); 
  //if(((myRTC.year < 2022) || (myRTC.year > 2090)) || ((myRTC.hours==6) && (myRTC.minutes==0) && (myRTC.seconds < 2))){
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    YYYY = formattedDate.substring(0, 4);
    if (YYYY.toInt() > 2020){
    MM = formattedDate.substring(7, 5);
    DD = formattedDate.substring(10, 8);
    hh = timeClient.getHours();
    mm = timeClient.getMinutes();
    ss = timeClient.getSeconds();
    }
    /*
    Serial.println("Set RTC ke jam Internet: ");
    Serial.print(DD);Serial.print("/");
    Serial.print(MM);Serial.print("/");
    Serial.print(YYYY);Serial.print("  Jam: ");
    Serial.print(hh);Serial.print(":");
    Serial.println(mm);
    */
    if (YYYY.toInt() > 2020){
      myRTC.setDS1302Time(ss,mm ,hh , timeClient.getDay(), DD.toInt(), MM.toInt(), YYYY.toInt());
      //Serial.println("Done");
    } else {
      //Serial.println("FAILED. Jam Internet tidak valid");
    }
    
  //}
}


void UpdateClockFromRTC(){
  myRTC.updateTime(); 
  hh=myRTC.hours;
  mm=myRTC.minutes;
  ss=myRTC.seconds;
  jamStr ="";

    if (hh < 10)  jamStr += "0";
    jamStr += String(hh);
    hhstr = jamStr;
    //Disp.refresh();
    jamStr +=":";
    mmstr="";
    if (mm < 10) {
      jamStr += "0";
      mmstr += "0";
    }
    jamStr += String(mm);
    mmstr += String(mm);
    
    jamshort = jamStr;
    jamStr +=":";
    //Disp.refresh();
    if (myRTC.seconds < 10) jamStr += "0";
    jamStr += String(myRTC.seconds);
    jamStr +=" ";
    //Serial.print("myRTC.dayofweek: ");Serial.println(myRTC.dayofweek);
    //Serial.print("myRTC.month: ");Serial.println(myRTC.month);
    YYYY = String(myRTC.year);
    MM = String(myRTC.month);
    DD = String(myRTC.dayofmonth);
    Serial.println("Jam di RTC:");
    Serial.print("Tanggal: ");
    Serial.print(DD);Serial.print("/");Serial.print(MM);Serial.print("/");Serial.println(YYYY);
    Serial.print("Jam: ");Serial.print(hh);Serial.print(":");Serial.print(mm);Serial.print(":");Serial.println(ss);
    tgl = String(daysOfTheWeek[myRTC.dayofweek]) + ", " + String(myRTC.dayofmonth) + " " + NamaBulan[myRTC.month - 1] + " " + String(myRTC.year)+" ";
    tglshort = String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year);
    if (MMH > 7) tgl += " - "+String(DDH)+" "+namaBulanHijriah[MMH-1]+" "+String(YYYYH)+" HIJRIYYAH ";
}

void prayer_calc_init() {
  set_calc_method(ISNA);  // Methode perhitungan mengikuti ISNA
  set_asr_method(Shafii); // Pendapat Imam Syafi'i
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20); // Sudut Waktu Subuh
  set_isha_angle(18); ////Sudut Waktu Isya
}
void prayer_time_update(int tahun,int bulan,int tanggal, const jws_location_setting_t jws_set,
                        double *times_out) {
  Serial.println("Update Jadwal Sholat");
  Serial.print("Tanggal : ");
  Serial.println(String(tanggal)+"/"+String(bulan)+"/"+String(tahun));
  get_prayer_times(tahun, bulan, tanggal, jws_set.lat,
                   jws_set.lon, jws_set.timezone, times_out);

}

void validasijws(){
  String bulanjws,tgljws;
  int pemisah;
  int hhx, mmx;
  char tmx[16];

  

  //if ((textjwsalt=="") || ((gpsminute==0) && (gpssecond==0))){
  //prayer_time_update(gpsyear,gpsmonth,gpsdate,jws_loc_set, prayer_times);
  //textjwsalt = "Jadwal Sholat tanggal "+String(gpsdate)+"/"+String(gpsmonth)+"/"+String(gpsyear);
  textjwsalt = "  Jadwal Sholat Lokasi : "+Namakota(int(jws_loc_set.lat * 100),int(jws_loc_set.lon*100))+" ";

  get_float_time_parts(prayer_times[0] - (10.0f / 60.0f), hhx, mmx);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhx, mmx);
    imsak = String(tmx);
    textjwsalt += "    IMSAK " + imsak;

    get_float_time_parts(prayer_times[0], hhS, mmS);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhS, mmS);
    subuh = String(tmx);
    textjwsalt += "    SHUBUH " + subuh;

    get_float_time_parts(prayer_times[1], hhx, mmx);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhx, mmx);
    textjwsalt += "    TERBIT " + String(tmx);

    get_float_time_parts(prayer_times[2], hhD, mmD);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhD, mmD);
    dzuhur = String(tmx);
    textjwsalt += "    DZUHUR " + dzuhur;

    get_float_time_parts(prayer_times[3], hhA, mmA);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhA, mmA);
    ashar = String(tmx);
    textjwsalt += "    ASHAR " + ashar;

    get_float_time_parts(prayer_times[5], hhM, mmM);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhM, mmM);
    maghrib = String(tmx);
    textjwsalt += "    MAGHRIB " + maghrib;

    get_float_time_parts(prayer_times[6], hhI, mmI);
    snprintf_P(tmx, sizeof(tmx), "%02d:%02d", hhI, mmI);
    isya = String(tmx);
    textjwsalt += "    ISYA " + isya;
    textjadwalsholat = textjwsalt;
    Serial.println(textjwsalt);
  //}  

}

String Namakota(int lat100, int long100){
  float flat = lat100/100;
  float flong = long100/100;
  //Disp.refresh();
  if ((long100<10537) && (long100>11437)){
    return "@"+String(flat)+" , "+String(flong);
  } else {
    if ((long100>10600) && (long100<10619) ){
      if ((lat100 < (-598)) && (lat100 >= (-605))){
        return "Cilegon";
      } else if ((lat100 < (-605)) && (lat100 >= (-620))){
        return "Serang";
      } else if ((lat100 < (-620)) && (lat100 >= (-635))){
        return "Cilegon";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10619) && (long100<10635) ){
      if ((lat100 < (-612)) && (lat100 > (-617))){
        return "Keragilan";
      } else if ((lat100 < (-617)) && (lat100 >= (-622))){
        return "Cikande";
      } else if ((lat100 < (-622)) && (lat100 >=(-638))){
        return "Rangkasbitung";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10635) && (long100<10647) ){
      if ((lat100 < (-602)) && (lat100 >= (-609))){
        return "Kronjo";
      } else if ((lat100 < (-609)) && (lat100 >= (-615))){
        return "Kresek";
      } else if ((lat100 < (-615)) && (lat100 >= (-621))){
        return "Balaradja";
      } else if ((lat100 < (-621)) && (lat100 >= (-627))){
        return "Tigaraksa";
      } else if ((lat100 < (-627)) && (lat100 >= (-639))){
        return "Tendjo";
      } else if ((lat100 < (-639)) && (lat100 >= (-653))){
        return "Jasinga";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10647) && (long100<10657) ){
      if ((lat100 < (-604)) && (lat100 >= (-609))){
        return "Mauk";
      } else if ((lat100 < (-609)) && (lat100 >= (-613))){
        return "Rajeg";
      } else if ((lat100 < (-613)) && (lat100 >= (-619))){
        return "PASARKEMIS, TANGERANG";
      } else if ((lat100 < (-619)) && (lat100 >= (-625))){
        return "CIKUPA, TANGERANG";
      } else if ((lat100 < (-625)) && (lat100 >= (-631))){
        return "Korelet";
      } else if ((lat100 < (-631)) && (lat100 >= (-650))){
        return "Parung";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else  if ((long100>=10657) && (long100<10661) ){
      if ((lat100 < (-604)) && (lat100 >= (-607))){
        return "Pakuhaji";
      } else if ((lat100 < (-607)) && (lat100 >= (-613))){
        return "Sepatan";
      } else if ((lat100 < (-613)) && (lat100 >= (-617))){
        return "Kutabumi";
      } else if ((lat100 < (-617)) && (lat100 >= (-623))){
        return "Karawaci";
      } else if ((lat100 < (-623)) && (lat100 >= (-632))){
        return "Curug";
      } else if ((lat100 < (-632)) && (lat100 >= (-653))){
        return "Parung";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10661) && (long100<10688) ){
      if ((lat100 < (-604)) && (lat100 >= (-607))){
        return "Cengkareng";
      } else if ((lat100 < (-607)) && (lat100 >= (-633))){
        return "Jakarta";
      } else if ((lat100 < (-633)) && (lat100 >= (-646))){
        return "Depok";
      } else if ((lat100 < (-646)) && (lat100 >= (-667))){
        return "Bogor";
      } else if ((lat100 < (-667)) && (lat100 >= (-671))){
        return "Caringin";
      } else if ((lat100 < (-671)) && (lat100 >= (-676))){
        return "Cigombong";
      } else if ((lat100 < (-676)) && (lat100 >= (-691))){
        return "Cibadak";
      } else if ((lat100 < (-691)) && (lat100 >= (-696))){
        return "CIMANGGU, SUKABUMI";
      } else if ((lat100 < (-696)) && (lat100 >= (-705))){
        return "WARUNGKIARA, SUKABUMI"; 
      } else if ((lat100 < (-705)) && (lat100 >= (-707))){
        return "LENGKONG, SUKABUMI";
      } else if ((lat100 < (-707)) && (lat100 >= (-710))){
        return "JAMPANG, SUKABUMI";
      }else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10688) && (long100<10695) ){
      if ((lat100 < (-604)) && (lat100 >= (-626))){
        return "Jakarta Timur";
      } else if ((lat100 < (-626)) && (lat100 >= (-637))){
        return "Cibubur";
      } else if ((lat100 < (-637)) && (lat100 >= (-640))){
        return "CILEUNGSI";
      } else if ((lat100 < (-640)) && (lat100 >= (-665))){
        return "Jonggol";
      } else if ((lat100 < (-665)) && (lat100 >= (-668))){
        return "CISARUA, BOGOR";
      } else if ((lat100 < (-668)) && (lat100 >= (-682))){
        return "PUNCAK, BOGOR";
      } else if ((lat100 < (-682)) && (lat100 >= (-702))){
        return "SUKABUMI";
      } else if ((lat100 < (-702)) && (lat100 >= (-711))){
        return "Purbaya";
      } else if ((lat100 < (-711)) && (lat100 >= (-726))){
        return "Cidadap";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10695) && (long100<10725) ){
      if ((lat100 < (-594)) && (lat100 >= (-606))){
        return "Pedes";
      } else if ((lat100 < (-606)) && (lat100 >= (-643))){
        return "Bekasi";
      } else if ((lat100 < (-643)) && (lat100 >= (-675))){
        return "Jonggol";
      } else if ((lat100 < (-675)) && (lat100 >= (-735))){
        return "CIANJUR";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10725) && (long100<10730) ){
      if ((lat100 < (-594)) && (lat100 >= (-606))){
        return "PEDES, KARAWANG";
      } else if ((lat100 < (-606)) && (lat100 >= (-620))){
        return "RENGASDENGKLOK, KARAWANG";
      } else if ((lat100 < (-620)) && (lat100 >= (-655))){
        return "KARAWANG";
      } else if ((lat100 < (-655)) && (lat100 >= (-666))){
        return "PURWAKARTA";
      } else if ((lat100 < (-666)) && (lat100 >= (-692))){
        return "CIANJUR";
      } else if ((lat100 < (-692)) && (lat100 >= (-700))){
        return "BANDUNG BARAT";
      } else if ((lat100 < (-700)) && (lat100 >= (-746))){
        return "CIANJUR";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10730) && (long100<10750) ){
      if ((lat100 < (-594)) && (lat100 >= (-620))){
        return "PEDES, KARAWANG";
      } else if ((lat100 < (-620)) && (lat100 >= (-630))){
        return "KARAWANG";
      } else if ((lat100 < (-630)) && (lat100 >= (-642))){
        return "CIKAMPEK";
      } else if ((lat100 < (-642)) && (lat100 >= (-669))){
        return "PURWAKARTA";
      } else if ((lat100 < (-669)) && (lat100 >= (-724))){
        return "BANDUNG";
      } else if ((lat100 < (-724)) && (lat100 >= (-746))){
        return "GARUT";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10750) && (long100<10770) ){
      if ((lat100 < (-610)) && (lat100 >= (-678))){
        return "SUBANG";
      } else if ((lat100 < (-678)) && (lat100 >= (-684))){
        return "LEMBANG";
      } else if ((lat100 < (-684)) && (lat100 >= (-726))){
        return "BANDUNG";
      } else if ((lat100 < (-726)) && (lat100 >= (-760))){
        return "GARUT";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10770) && (long100<10810) ){
      if ((lat100 < (-621)) && (lat100 >= (-659))){
        return "INDRAMAYU";
      } else if ((lat100 < (-659)) && (lat100 >= (-693))){
        return "SUMEDANG";
      } else if ((lat100 < (-693)) && (lat100 >= (-732))){
        return "GARUT";
      } else if ((lat100 < (-732)) && (lat100 >= (-773))){
        return "TASIKMALAYA";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10810) && (long100<10845) ){
      if ((lat100 < (-621)) && (lat100 >= (-657))){
        return "INDRAMAYU";
      } else if ((lat100 < (-657)) && (lat100 >= (-697))){
        return "MAJALENGKA";
      } else if ((lat100 < (-697)) && (lat100 >= (-727))){
        return "CIAMIS";
      } else if ((lat100 < (-727)) && (lat100 >= (-773))){
        return "TASIKMALAYA";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10845) && (long100<10875) ){
      if ((lat100 < (-621)) && (lat100 >= (-684))){
        return "CIREBON";
      } else if ((lat100 < (-684)) && (lat100 >= (-705))){
        return "KUNINGAN";
      } else if ((lat100 < (-705)) && (lat100 >= (-780))){
        return "CIAMIS";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10875) && (long100<10895) ){
      if ((lat100 < (-621)) && (lat100 >= (-725))){
        return "BREBES";
      } else if ((lat100 < (-725)) && (lat100 >= (-780))){
        return "CILACAP";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10895) && (long100<10930) ){
      if ((lat100 < (-621)) && (lat100 >= (-725))){
        return "TEGAL";
      } else if ((lat100 < (-725)) && (lat100 >= (-780))){
        return "PURWOKERTO";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10930) && (long100<10950) ){
      if ((lat100 < (-680)) && (lat100 >= (-720))){
        return "PEMALANG";
      } else if ((lat100 < (-720)) && (lat100 >= (-738))){
        return "PURBALINGGA";
      } else if ((lat100 < (-738)) && (lat100 >= (-775))){
        return "KEBUMEN";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10950) && (long100<10990) ){
      if ((lat100 < (-680)) && (lat100 >= (-720))){
        return "PEKALONGAN";
      } else if ((lat100 < (-720)) && (lat100 >= (-738))){
        return "BANJARNEGARA";
      } else if ((lat100 < (-738)) && (lat100 >= (-775))){
        return "KEBUMEN";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=10990) && (long100<11030) ){
      if ((lat100 < (-680)) && (lat100 >= (-713))){
        return "KENDAL";
      } else if ((lat100 < (-713)) && (lat100 >= (-735))){
        return "TEMANGGUNG";
      } else if ((lat100 < (-735)) && (lat100 >= (-764))){
        return "MAGELANG";
      } else if ((lat100 < (-764)) && (lat100 >= (-799))){
        return "KULONPROGO";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=11030) && (long100<11060) ){
      if ((lat100 < (-680)) && (lat100 >= (-721))){
        return "SEMARANG";
      } else if ((lat100 < (-721)) && (lat100 >= (-737))){
        return "SALATIGA";
      } else if ((lat100 < (-737)) && (lat100 >= (-760))){
        return "BOYOLALI";
      } else if ((lat100 < (-760)) && (lat100 >= (-775))){
        return "KLATEN";
      } else if ((lat100 < (-775)) && (lat100 >= (-810))){
        return "YOGYAKARTA";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=11060) && (long100<11100) ){
      if ((lat100 < (-640)) && (lat100 >= (-672))){
        return "JEPARA";
      } else if ((lat100 < (-672)) && (lat100 >= (-693))){
        return "KUDUS";
      } else if ((lat100 < (-693)) && (lat100 >= (-740))){
        return "SRAGEN";
      } else if ((lat100 < (-740)) && (lat100 >= (-773))){
        return "SURAKARTA";
      } else if ((lat100 < (-773)) && (lat100 >= (-820))){
        return "WONOGIRI";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=11100) && (long100<11160) ){
      if ((lat100 < (-640)) && (lat100 >= (-672))){
        return "PATI / REMBANG";
      } else if ((lat100 < (-672)) && (lat100 >= (-714))){
        return "BLORA";
      } else if ((lat100 < (-714)) && (lat100 >= (-749))){
        return "NGAWI";
      } else if ((lat100 < (-749)) && (lat100 >= (-769))){
        return "MADIUN";
      } else if ((lat100 < (-769)) && (lat100 >= (-820))){
        return "PONOROGO";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=11160) && (long100<11220) ){
      if ((lat100 < (-640)) && (lat100 >= (-705))){
        return "TUBAN";
      } else if ((lat100 < (-705)) && (lat100 >= (-732))){
        return "BOJONEGORO";
      } else if ((lat100 < (-732)) && (lat100 >= (-763))){
        return "NGANJUK";
      } else if ((lat100 < (-763)) && (lat100 >= (-793))){
        return "KEDIRI";
      } else if ((lat100 < (-793)) && (lat100 >= (-820))){
        return "TULUNGAGUNG";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else if ((long100>=11220) && (long100<11260) ){
      if ((lat100 < (-640)) && (lat100 >= (-732))){
        return "SURABAYA";
      } else if ((lat100 < (-732)) && (lat100 >= (-763))){
        return "SIDOARJO";
      } else if ((lat100 < (-763)) && (lat100 >= (-778))){
        return "PASURUAN";
      } else if ((lat100 < (-778)) && (lat100 >= (-820))){
        return "MALANG";
      } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    } else {
        return "@"+String(flat)+" , "+String(flong);
      }
    
  }
}
