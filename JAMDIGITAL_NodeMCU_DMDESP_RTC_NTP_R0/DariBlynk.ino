BLYNK_WRITE(V0)
  {   
   String nilaipin = param.asString();

   epengumuman = nilaipin+" ";
   Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 224; i < 324; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(224,String(nilaipin)); //8digit
   EEPROM.commit();

  }

BLYNK_WRITE(V1)
  {   
   int nilaipin = param.asInt();

   if (nilaipin==1) {
    tampilkanPengumuman=true;
   } else {
    tampilkanPengumuman=false;
   }
   //Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 324; i < 332; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(324,String(tampilkanPengumuman)); //8digit
   EEPROM.commit();

  }

BLYNK_WRITE(V2)
  {   
   int nilaipin = param.asInt();

   if (nilaipin==1) {
    tampilkanUcapan=true;
   } else {
    tampilkanUcapan=false;
   }
   //Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 332; i < 340; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(332,String(tampilkanUcapan)); //8digit
   EEPROM.commit();

  }


BLYNK_WRITE(V3)
  {   
   int nilaipin = param.asInt();

   if (nilaipin==1) {
    tampilkanJWS=true;
   } else {
    tampilkanJWS=false;
   }
   //Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 340; i < 348; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(340,String(tampilkanJWS)); //8digit
   EEPROM.commit();

  }

BLYNK_WRITE(V4)
  {   
   int nilaipin = param.asInt();

   tipejam = nilaipin;
   //Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 348; i < 356; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(348,String(tipejam)); //8digit
   EEPROM.commit();
   Disp.clear();
   //prognumber++;
   //jamstart=false;
  }

BLYNK_WRITE(V5)
  {   
   int nilaipin = param.asInt();

   if (nilaipin==1) {
    tampilkanKalender=true;
   } else {
    tampilkanKalender=false;
   }
   //Serial.print("Perubahan isi Pengumuman jadi: ");Serial.println(epengumuman);
   for (int i = 356; i < 364; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(356,String(tampilkanKalender)); //8digit
   EEPROM.commit();

  }

BLYNK_WRITE(V6)
  {   
   int nilaipin = param.asInt();
   LAMAJAM = nilaipin;
   for (int i = 364; i < 372; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(364,String(LAMAJAM)); //8digit
   EEPROM.commit();

  }

BLYNK_WRITE(V7)
  {   
   int nilaipin = param.asInt();
   tipefont = nilaipin;
   for (int i = 372; i < 372; ++i) {
          EEPROM.write(i, 0);
        }   
   tulis(372,String(tipefont)); //8digit
   EEPROM.commit();

  } 
