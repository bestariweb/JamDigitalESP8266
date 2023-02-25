void baca(int awal,int lebar,String *hasil){
  *hasil = "";
  //char hasilbaca;
  Serial.print("Read EERPOM from ");
  Serial.print(awal);
  Serial.print(" to ");
  Serial.print(int(awal+lebar));
  Serial.println("");
  for (int i = 0; i < lebar; ++i){
    Serial.print(i);
    if ((EEPROM.read(i+awal)>0) && (EEPROM.read(i+awal) < 255)){
     // hasilbaca = char(EEPROM.read(i));
      //Serial.println(char(EEPROM.read(i+awal)));
      *hasil += char(EEPROM.read(i+awal));
      Serial.print("READ: [");Serial.print(String(i));Serial.print("] => ");
      Serial.println(*hasil);
      delay(1);
    }
    Serial.println(" SKIP");  
  }
  delay(2);
  //return true;
}


void tulis(int awal,String datanya){
  for (int i = 0; i < datanya.length(); ++i)
  {
    EEPROM.write(i+awal, datanya[i]);
    Serial.print("Wrote: [");Serial.print(String(i+awal));Serial.print("] <= ");
    Serial.println(datanya[i]);
  }
}

void readeeprom(){
 Serial.println("reading EEPROM Data");
 
  baca(0,32,&essid);
  baca(32,16,&epass);
  baca(64,32,&eblauth);
  baca(96,32,&eblserver);
  baca(160,32,&ehssid);
  baca(192,32,&ehpass);
  baca(224,100,&epengumuman);
  baca(324,8,&tampilkanPengumumanStr);
  baca(332,8,&tampilkanUcapanStr);
  baca(340,8,&tampilkanJWSStr);
  baca(348,8,&tipejamStr);
  baca(356,8,&tampilkanKalenderStr);
  baca(364,8,&lamajamStr);
  baca(372,8,&tipefontstr);
  baca(380,8,&iptype);
  baca(388,20,&ipstr);
  baca(408,20,&subnetstr);
  baca(428,20,&gatewaystr);
  baca(448,20,&primaryDNSstr);
  Serial.print("IP Type: ");Serial.println(iptype);
  Serial.print("IP: ");Serial.println(ipstr);
  Serial.print("Subnet: ");Serial.println(subnetstr);
  Serial.print("Gateway: ");Serial.println(gatewaystr);
  Serial.print("Primary DNS: ");Serial.println(primaryDNSstr);
  tipefont = tipefontstr.toInt();
  if ((tipefont<1) || (tipefont>8))  tipefont=8;
  tipejam = tipejamStr.toInt();
  if (tampilkanJWSStr=="1") tampilkanJWS = true;
  else tampilkanJWS = false;

  if (tampilkanUcapanStr=="1") tampilkanUcapan=true;
  else tampilkanUcapan = false;

  if (tampilkanPengumumanStr=="1") tampilkanPengumuman=true;
  else tampilkanPengumuman=false;

  if (tampilkanKalenderStr=="1") tampilkanKalender=true;
  else tampilkanKalender=false;

  LAMAJAM = lamajamStr.toInt();
  if (LAMAJAM<2)  LAMAJAM=30;
  
  
  epengumuman +=" ";
  Serial.print("epass: ");Serial.println(epass);
  Serial.print("essid: ");Serial.println(essid);
  Serial.print("Blynk Server: ");Serial.println(eblserver);
  Serial.print("Blynk Auth: ");Serial.println(eblauth);
  Serial.print("ehssid: ");Serial.println(ehssid);
  Serial.print("ehpass: ");Serial.println(ehpass);
  epengumuman+=" ";
  Serial.print("epengumuman: ");Serial.println(epengumuman);
  Serial.print("Font Pengumuman: ");Serial.println(tipefont);
  Serial.print("Font JAM: ");Serial.println(tipejam);
  Serial.print("Lama Tampil JAM: ");Serial.println(LAMAJAM);
  Serial.print("tampilkanPengumumanStr: ");Serial.println(tampilkanPengumumanStr);
}

void scanssid(){
  int n = WiFi.scanNetworks();
  if (n == 0){
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  //st = "<form method='get' action='savesetting'>";
  st = "<p><label>Wifi SSID: </label>";
  st += "<select name=\"ssid\" id=\"ssid\">";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    
    st +="\t<option value=";
    st +="\"";
    st += WiFi.SSID(i);
    st += "\"";
    if (WiFi.SSID(i)==essid){
      st += " selected ";
    }
    st += ">";
    st += WiFi.SSID(i);
    st += " (Strength: ";
    st += WiFi.RSSI(i);
    st += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st +="</option>\n";
  }
  st += "</select></p>";
  delay(100);
}


void createWebServer()
{
 {
    scanssid();
    server.on("/", []() {
 
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
// AWAL ISI WEB ======================
      content = "<!DOCTYPE HTML>\r\n<html>\r\n";
      content += "<head>\r\n<title>Bestariweb ioT Connection Seting</title>\r\n";
      content += "<meta http-equiv=\"refresh\" content=\"0;url=/setting\">";
      content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";

      content += "<style>\r\n";
      content += "\r\n</style>\r\n</head>\r\n<body></BODY></HTML>\r\n";
      
// AKHIR ISI WEB ======================
      server.send(200, "text/html", content);
    });

    server.on("/dashboard", []() {
      webopened = true;
      
      content = "<!DOCTYPE HTML>\r\n<html>\r\n";
      content += "<head>\r\n<title>Bestariweb ioT Connection Seting</title>\r\n";
      content += "<meta http-equiv=\"refresh\" content=\"0;url=/setting\">";
      content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";

      content += "<style>\r\n";
      content += "\r\n</style>\r\n</head>\r\n<body></BODY></HTML>\r\n";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      webopened = true;
      content = "<!DOCTYPE HTML>\r\n<html>\r\n";
      content += "<head>\r\n<title>Bestariweb ioT SETTING</title>\r\n";
      content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
      content += "<style>\r\n";
      content += "html{background:#333;color:#fff;}body{font-family:arial;margin:0;min-height:800px;}#manualonly{display:none;}form{margin:10px 10px 150px 10px;}label{font-size:14px;width:140px;float:left;padding:8px;}input[type=password],input[type=number],input[type=text]{font-size:16px;border: none;padding: 8px;width:45%;float:left;background: #dbdb07;box-shadow: inset 2px 2px 2px rgba(0,0,0,0.5);border-radius: 6px;color: #333;max-width:150px}h1{font-size:18px;border-bottom: solid 1px #aaa;padding: 5px 0;margin: 10px 0;text-transform: uppercase;}";
      content += "input[type=number]::-webkit-inner-spin-button {opacity: 1;}p{float:left;width:100%}";
      content += ".vleft{font-size:16px;padding: 8px;margin: 10px 0;text-transform: uppercase;width:45%;float:left;text-align:right;}.vright{font-size:16px;border: none;padding: 8px;margin: 10px 0;text-transform: uppercase;width:45%;float:left;background: #dbdb07;box-shadow: inset 2px 2px 2px rgba(0,0,0,0.5);border-radius: 6px;color: #333;max-width:150px}";
      content += ".tombol{width:90%;max-width:300px;clear:both;background:#aa0000;color:#ffffff;margin:10px auto;border-radius:10px;}.tombol a{color:#fff;text-align:center;display:block;padding:20px;text-decoration:none}";
      content += ".topmenu{width:95%;margin:10px auto;border-bottom:solid 1px #aaf;height:29px;}.menuitem{border-radius:5px 5px 0 0;float:left;background:#007;color:#fff;padding:5px 8px;margin:0 3px 0 0;}";
      content += ".menuitem a{text-decoration:none;color:#aac}.topmenu > .active {background:#00a!important;border: 1px #aaf solid;border-bottom:none;box-shadow: 10px -1px 3px rgba(0,0,0,0.6);z-index: 1000;position: relative;}";
      content += "\r\n</style>\r\n";
      content += "</head><body><div class=\"topmenu\"><div class=\"menuitem \"><a href=\"/dashboard\">DASHBOARD</a></div><div class=\"menuitem active\">SETTING</div></div>";
      content += "<form action=\"/savesetting\">";
      content += "<h1>Access Point Setting</h1>"+st;
      content += "<p><label>Wifi Password: </label><input type='password' name='pass' value='"+epass+"' length=64></p>";
      content += "<h1>IP Setting</h1>";
      content += "<p><label>IP Type: </label><select name=\"iptype\" id=\"iptype\" onchange=\"showDiv('manualonly', this)\">";
      content += "<option value='dhcp' selected>DHCP</option>";
      content += "<option value='manual'>Manual</option></select></p>";
      content += "<div id='manualonly'>";
      content += "<p><label>IP: </label><input type='text' value='"+ipstr+"' name='ipstr' length=64></p>"; 
      content += "<p><label>Subnet: </label><input type='text' value='"+subnetstr+"' name='subnetstr' length=64></p>"; 
      content += "<p><label>Gateway: </label><input type='text' value='"+gatewaystr+"' name='gatewaystr' length=64></p>"; 
      content += "<p><label>Primary DNS: </label><input type='text' value='"+primaryDNSstr+"' name='primaryDNSstr' length=64></p>";
      content += "</div>"; 
      content += "<p><label>Blynk Server: </label><input type='text' value='"+eblserver+"' name='blserver' length=64></p>";
      content += "<p><label>Blynk Auth: </label><input type='text' value='"+eblauth+"' name='blauth' length=64></p>"; 
      content += "<h1>Tulis Pengumuman</h1>";
      content += "<p><label>Teks Pengumuman: </label><input type='text' name='pengumuman' value='"+epengumuman+"' length=64></p>";
      content += "<h1>Hotspot Setting</h1>";
      if (ehssid.length() > 2){
        content += "<p><label>SSID: </label><input type='text' name='hssid' value='"+ehssid+"' length=64></p>";
        content += "<p><label>Password: </label><input type='password' name='hpass' value='"+ehpass+"' length=64></p>";
      } else {
        content += "<p><label>SSID: </label><input type='text' name='hssid' value='"+String(AP_SSID)+"' length=64></p>";
        content += "<p><label>Password: </label><input type='password' name='hpass' value='"+String(AP_PASS)+"' length=64></p>";
      }
      content += "<input type='submit' name='tombol' value='SAVE'><input type='submit' value='SAVE &amp; REBOOT'><div style=\"clear:both;margin:150px 0;height:200px;\"></div></form>";
      
      content += "<div style=\"position:fixed;bottom:0;display:block;font-size:10px;background:#ff6000;color:#ffffff;width:100%;padding:8px 0;text-align:center;\">";
      content += "MAC:";
      content += WiFi.macAddress();
      content += "  IP: "+ipstrap+" / "+ ipstrhs;
      content += "<br>Copyright&copy;2022 Bestariweb</div>";
      content += "<script>";
      content += "function showDiv(divId, element)";
      content += "{";
      content += "document.getElementById(divId).style.display = element.value == 'dhcp' ? 'none' : 'block';";
      content += "}";
      content += "</script>";
      content += "</body></html>";
      server.send(200, "text/html", content);
    });
 server.on("/reboot", []() {
  content = "{\"Success\":\"Device akan segera reboot\"}";
  server.send(200, "text/json", content);
  ESP.reset();
 });
 
 server.on("/savesetting", []() {
      String qssid = server.arg("ssid");
      String qpass = server.arg("pass");
      String qblauth = server.arg("blauth");
      String qblserver = server.arg("blserver");
      String qpengumuman = server.arg("pengumuman");
      String qhssid = server.arg("hssid");
      String qhpass = server.arg("hpass");
      
      String qiptype = server.arg("iptype");
      String qipstr = server.arg("ipstr");
      String qsubnetstr = server.arg("subnetstr");
      String qgatewaystr = server.arg("gatewaystr");
      String qprimaryDNSstr = server.arg("primaryDNSstr");
      
      String qbtn = server.arg("tombol");

      if (qssid.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 256; ++i) {
          EEPROM.write(i, 0);
        }

        tulis(0,qssid);
        tulis(32,qpass);
        tulis(64,qblauth);
        tulis(96,qblserver);
        tulis(160,qhssid);
        tulis(192,qhpass);
        tulis(224,qpengumuman); //8digit
        tulis(324,tampilkanPengumumanStr);
        tulis(332,tampilkanUcapanStr);
        tulis(340,tampilkanJWSStr);
        tulis(348,tipejamStr);
        tulis(356,tampilkanKalenderStr);
        tulis(364,lamajamStr);
        tulis(372,tipefontstr);

        tulis(380,qiptype); // 8 bit 380+8 = 388
        tulis(388,qipstr);  // 20 bit  388+20 = 408
        tulis(408,qsubnetstr); // 20 bit  408+20 = 428
        tulis(428,qgatewaystr); // 20 bit  428+20 = 448
        tulis(448,qprimaryDNSstr); // 20 bit  448+20 = 468

  
    
        EEPROM.commit();
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
      }
      
      //server.send(200, "text/html", content);
      if (qbtn !="SAVE") {
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        server.send(200, "text/html", content);
        ESP.reset();
      } else {
      content = "<!DOCTYPE HTML>\r\n<html>\r\n";
      content += "<head>\r\n<title>Bestariweb ioT Connection Seting</title>\r\n";
      content += "<meta http-equiv=\"refresh\" content=\"0;url=/setting\">";
      content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";

      content += "<style>\r\n";
      content += "\r\n</style>\r\n</head>\r\n<body></BODY></HTML>\r\n";
      
// AKHIR ISI WEB ======================
      server.send(200, "text/html", content);
      }
    });



 }
}
