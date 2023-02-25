static char *teks[] = {"PT. GINSA INTI PRATAMA","MANUFACTURER OF FASTENERS"};
//static char *teksultah[] = {"SELAMAT ULANG TAHUN YANG KE"};

void TeksJalan(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  static bool mulaijalan;
  static byte urutan;

  if (!mulaijalan){
    mulaijalan=true;
    urutan=0;
    x=0;
  }
  int width = Disp.width();
  Disp.setFont(ArialRoundedMTBold16b);
  int fullScroll = Disp.textWidth(teks[urutan]) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      urutan++;
      if (urutan==2){
        prognumber++;
        mulaijalan=false;
        return;
      } 
    }
    Disp.drawText(width - x, y, teks[urutan]);
  }  

}

void ultah(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  static bool mulaijalan;
  static byte urutan;
  static String UcapanULTAH;
  String karyawan;
  
  switch (MM.toInt()){
    case 1:switch (DD.toInt()){
            case 13:karyawan = "Yanti";break;
            case 24:karyawan = "Bapak Andriansyah & Josad Siturus";break;
            case 31:karyawan = "Puji Listiono";break;
           }
           break;
    case 2: if (DD.toInt()==13)karyawan = "Safahrudin";break;
    case 3: switch (DD.toInt()){
            case 13:karyawan = "BAPAK ARIFIN PRASE TEA";break;
            case 12:karyawan = "Mahmud Sutisna";break;
            case 15:karyawan = "Abdul Kohar";break;
            case 27:karyawan = "IBU JULIATI";break;
            case 28:karyawan = "Rega Romdoni";break;  
           } 
           break;
    case 4: switch (DD.toInt()){
            case 16:karyawan = "Apriliana";break;
            case 20:karyawan = "Kresna";break;
           }
    case 5: switch (DD.toInt()){
            case 7:karyawan = "Hendri Irawan";break;
            case 16:karyawan = "Aas Nina Tri Utami";break;
            case 20:karyawan = "Trias Anitasari";break;
            case 23:karyawan = "Nur Halim";break;
            case 25:karyawan = "IBU LIM CIN MEY";break;
 
           }
           break;
    case 6: if (DD.toInt()==30) karyawan = "BAPAK HENDRY HOTMAN HUTABARAT";break;
           
    case 7: switch (DD.toInt()){
            case 1:karyawan = "Ivan Lorensius";break;
            case 6:karyawan = "Yulia Harmonis";break;
            case 15:karyawan = "FX Yuliandaru";break;
           }
           break;
    case 8: switch (DD.toInt()){
            //case 3:karyawan = "Tanto";break;
            case 9:karyawan = "Wilianita";break;
            case 12:karyawan = "Yudha Ardian";break;
            case 27:karyawan = "Siti Khodijah & Liana Puspita";break;
           }
           break;
    case 9: switch (DD.toInt()){
            case 8:karyawan = "Katherina Edyanto";break;
            case 12:karyawan = "Fatmawati";break;
            case 18:karyawan = "Ratih";break;
            case 22:karyawan = "BAPAK SUPRIH CAHYO H.";break;
           }
           break;
    case 10:if (DD.toInt()==17) karyawan = "BAPAK HENDIK TEA";break;
    case 11:switch (DD.toInt()){
            case 4:karyawan = "Hennye";break;
            case 10:karyawan = "Lili Atikah";break;
            case 23:karyawan = "BAPAK YANTO SOEHARDI";break;
            case 26:karyawan = "IBU EVI SETIORINI";break;
            case 29:karyawan = "Pengikhan Panji";break;
           }
           break;
    case 12:switch (DD.toInt()){
            case 3:karyawan = "BAPAK WENDY TIO (TIO KIM HUAT)";break;
            case 8:karyawan = "IBU LINDA (LO LIE SON)";break;
            case 11:karyawan = "Anda Bin Mandroi";break;
            case 13:karyawan = "Desi Fitriyani";break;
            case 20:karyawan = "Dadi Mulyana";break;
           }
           break;
  }
  if (!mulaijalan){
    mulaijalan=true;
    urutan=0;
    x=0;
  }
  int width = Disp.width();
  if (urutan==0){
    UcapanULTAH="SELAMAT ULANG TAHUN UNTUK "+karyawan+" ";
  } else {
    UcapanULTAH="SUKSES & SEHAT SELALU, SEMOGA PANJANG UMUR ";
  }
  Disp.setFont(ArialRoundedMTBold16b);
  int fullScroll = Disp.textWidth(UcapanULTAH) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      urutan++;
      if (urutan==2){
        prognumber++;
        mulaijalan=false;
        return;
      } 
    }
      Disp.drawText(width - x, y, UcapanULTAH);

  }  

}


void DisplayPengumuman(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  static byte urutan;
  static bool mulaijalan;

  if (!mulaijalan){
    mulaijalan=true;
    urutan=0;
    x=0;
    Disp.clear();
  }
  if (epengumuman.length()>10){
  int width = Disp.width();
  //UpdateClockFromRTC();
  //Disp.setFont(ArialRoundedMTBold16b);
  if (tipefont==1){
    Disp.setFont(EMSansSP8x16);
  } else if (tipefont==2){
    Disp.setFont(EMSansSP10x16);
  } else if (tipefont==3){
    Disp.setFont(Verdana14b);
  } else if (tipefont==4){
    Disp.setFont(Verdana18);
  } else if (tipefont==5){
    Disp.setFont(Verdana18b);
  } else if (tipefont==6){
    Disp.setFont(Droid_Sans_24);
  } else if (tipefont==7){
    Disp.setFont(CooperBlack16);
  } else if (tipefont==8){
    Disp.setFont(ArialRoundedMTBold16b);
  }
  int fullScroll = Disp.textWidth(epengumuman) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      urutan++;
      if (urutan>1){
        prognumber++;
        urutan=0;
        mulaijalan=false;
        return;  
      } 
     }
    Disp.drawText(width - x, y, epengumuman);
  }  
  } else {
    prognumber++;
    urutan=0;
    mulaijalan=false;
  }

}


void agendaharian(int y, uint8_t kecepatan,String isiagenda) {

  static uint32_t pM;
  static uint32_t x;
  static byte urutan;
  static bool mulaijalan;

  if (!mulaijalan){
    mulaijalan=true;
    urutan=0;
    x=0;
  }
  int width = Disp.width();
  //UpdateClockFromRTC();
  Disp.setFont(ArialRoundedMTBold16b);
  int fullScroll = Disp.textWidth(isiagenda) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      urutan++;
      if (urutan>4){
        prognumber++;
        urutan=0;
        mulaijalan=false;
        return;  
      }
     }
    Disp.drawText(width - x, y, isiagenda);
  }  

}

void Kalender(uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  static byte urutan;
  static bool mulaijalan;

  if (!mulaijalan){
    mulaijalan=true;
    urutan=0;
    x=0;
  }
  int width = Disp.width();
  UpdateClockFromRTC();
  Disp.setFont(SystemFont5x7);
  Disp.drawText((Disp.width()- Disp.textWidth(jamStr))/2, 0, jamStr);
  int fullScroll = Disp.textWidth(tgl) + width;
  Disp.drawText(width - x, 9, tgl);
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      //urutan++;
      //if (urutan>3){
        prognumber++;
        urutan=0;
        mulaijalan=false;
        return;  
      //}
      
    }
    
  }  

}

void jambesar(){
  static uint32_t millisjam;
  if (!jamstart){
    jamstart=true;
    millisjam=millis();
    Disp.clear();
    //Disp.drawRect(0,0,Disp.width()-1,Disp.height()-1);
  }
  if (tipejam==1){
    Disp.setFont(EMSansSP8x16);
  } else if (tipejam==2){
    Disp.setFont(EMSansSP10x16);
  } else if (tipejam==3){
    Disp.setFont(Verdana14b);
  } else if (tipejam==4){
    Disp.setFont(Verdana18);
  } else if (tipejam==5){
    Disp.setFont(Verdana18b);
  } else if (tipejam==6){
    Disp.setFont(Droid_Sans_24);
  } else if (tipejam==7){
    Disp.setFont(CooperBlack16);
  } else if (tipejam==8){
    Disp.setFont(ArialRoundedMTBold16b);
  }
  int xx;
  UpdateClockFromRTC();
  if (hh<10) xx= int(((Disp.width())- Disp.textWidth("00:00:00"))/2);
  else if ((hh>=10) && (hh<20)) xx= int(((Disp.width())- Disp.textWidth("10:10:00"))/2);
  else xx= int(((Disp.width())- Disp.textWidth("20:00:00"))/2);
  //Serial.println("jam Besar");
  
  Disp.drawText(xx,0,jamStr);

  //Disp.drawRect(0,0,Disp.width()-1,Disp.height()-1);
  if ((millis()-millisjam) > (LAMAJAM*1000)){
    prognumber++;
    jamstart=false;
    Disp.clear();
    return;
  }
}

void jambesar2(){
  
  static uint32_t millisjam;
  if (!jamstart){
    jamstart=true;
    millisjam=millis();
    Disp.clear();
  }
  UpdateClockFromRTC();
  Disp.setFont(EMSansSP8x16);
  int xx = int((Disp.width()- Disp.textWidth("00:00:00"))/2);
  //Serial.println("jam Besar 2");
  Disp.drawText(xx,0,jamStr);
  //Disp.drawRect(0,0,Disp.width()-1,Disp.height()-1);
  if ((millis()-millisjam) > (LAMAJAM*1000)){
    prognumber++;
    jamstart=false;
    Disp.clear();
    return;
  }
}

void jambesar3(){
  static uint32_t millisjam;
  static uint32_t millisdtk;
  if (!jamstart){
    jamstart=true;
    millisjam=millis();
    millisdtk=millis();
    Disp.clear();
    //Disp.drawRect(0,0,Disp.width()-1,Disp.height()-1);
  }
  Disp.setFont(EMSansSP8x16);
  int xx;
  if ((millis()-millisdtk) > 999){
    UpdateClockFromRTC();
    millisdtk=millis();
  }
  Disp.drawText(0,0,hhstr);//Serial.println(ss);
  if ((ss % 2)==0){
    Disp.drawText(20,0,":");//Serial.println(":");
  } else {
    Disp.drawText(20,0," ");
    //Serial.println("spasi");
  }
  Disp.drawText(26,0,mmstr);
  Disp.setFont(SystemFont5x7);
  int posisijws = Disp.width()-45;
  if ((hh>hhI) || (hh<hhS) || ((hh==hhS) && (mm<mmS))){Disp.drawText(posisijws,0,"SUBUH");Disp.drawText(posisijws,9,subuh);}
  else if ((hh<hhD) || ((hh==hhD) && (mm<mmD))) {Disp.drawText(posisijws,0,"DZUHUR");Disp.drawText(posisijws,9,dzuhur);}
  else if ((hh<hhA) || ((hh==hhA) && (mm<mmA))){Disp.drawText(posisijws,0,"ASHAR");Disp.drawText(posisijws,9,ashar);}
  else if ((hh<hhM) || ((hh==hhM) && (mm<mmM))){Disp.drawText(posisijws,0,"MAGHRIB");Disp.drawText(posisijws,9,maghrib);}
  else if ((hh<hhI) || ((hh==hhI) && (mm<mmI))){Disp.drawText(posisijws,0,"ISYA");Disp.drawText(posisijws,9,isya);}
  else {
    prognumber++;
    jamstart=false;
    Disp.clear();
    return;
  }
  if ((millis()-millisjam) > 30000){
    prognumber++;
    jamstart=false;
    Disp.clear();
    return;
  }
}
