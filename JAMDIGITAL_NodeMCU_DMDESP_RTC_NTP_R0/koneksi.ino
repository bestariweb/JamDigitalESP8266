IPAddress str2IP(String str) {

    IPAddress ret( getIpBlock(0,str),getIpBlock(1,str),getIpBlock(2,str),getIpBlock(3,str) );
    return ret;

}

int getIpBlock(int index, String str) {
    char separator = '.';
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = str.length()-1;
  
    for(int i=0; i<=maxIndex && found<=index; i++){
      if(str.charAt(i)==separator || i==maxIndex){
          found++;
          strIndex[0] = strIndex[1]+1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
    }
    
    return found>index ? str.substring(strIndex[0], strIndex[1]).toInt() : 0;
}

void checkconnection(){
  if (pernahconnect)  WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(MyapIP, MyapIP, IPAddress(255, 255, 255, 0)); 
  if (ehssid.length() > 2){   
    WiFi.softAP(ehssid,ehpass);
  } else {
    WiFi.softAP(AP_SSID, AP_PASS);
  }
  // Begin WiFi
  //lcd.clear();
  if (essid.length() > 2){
    if ((iptype=="manual") && (ipstr != "") && (gatewaystr !="") && (subnetstr !="")){
      Serial.println("");
      Serial.println("configure Static IP address...");
      if (!WiFi.config(str2IP(ipstr), str2IP(gatewaystr), str2IP(subnetstr), str2IP(primaryDNSstr), str2IP("8.8.8.8"))) {
        Serial.println("Failed to configure STATIC IP");
      }
    }
    WiFi.begin(essid,epass);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Connecting to ");
    Serial.print(essid);
  } else {
    if ((iptype=="manual") && (ipstr != "") && (gatewaystr !="") && (subnetstr !="")){
      Serial.println("");
      Serial.println("CONFIGURE TO STATIC IP");
      if (!WiFi.config(str2IP(ipstr), str2IP(gatewaystr), str2IP(subnetstr), str2IP(primaryDNSstr), str2IP("8.8.8.8"))) {
        Serial.println("Failed to configure STATIC IP");
      }
    }
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
  }
  // Connecting to WiFi...
  int i=0;
  while ((WiFi.status() != WL_CONNECTED) && (i<MAX_TRIAL))
  {
    delay(400);
    Serial.print(".");
    ++i;
  }
  if (i==MAX_TRIAL){
    pernahconnect=false;
    Serial.println("Connection FAIL");
  } else {
    pernahconnect=true;
    Serial.println("Connection SUCCESS");
    if ((eblauth.length()>5) && (eblserver.length()>5)){
      Serial.println("Connection to Blynk Server");
      Serial.print("Server: ");Serial.println(eblserver);
      Serial.print("Auth: ");Serial.println(eblauth);
      Blynk.config(eblauth.c_str(),eblserver.c_str(),8080);
      Blynk.connect();
      delay(1000);
    }
    
    ipap = WiFi.softAPIP();
    ipstrap = String(ipap[0]) + '.' + String(ipap[1]) + '.' + String(ipap[2]) + '.' + String(ipap[3]);
    //IPAddress 
    iphs = WiFi.localIP();
    ipstrhs = String(iphs[0]) + '.' + String(iphs[1]) + '.' + String(iphs[2]) + '.' + String(iphs[3]);
    Serial.println(ipstrap);Serial.println(ipstrhs);
    
  }   
  
}
