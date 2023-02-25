uint32_t jumlahHariDariTanggal(byte tanggal, byte bulan, uint16_t tahun)
{
  uint32_t jumlahHari = (uint32_t)tahun * 365;
  
  uint16_t jumlahHariPerBulanMasehi[]={0,31,59,90,120,151,181,212,243,273,304,334};
  
  for (uint16_t i = 0; i < tahun; i++) 
  {
    if (!(i%4))
    {
      jumlahHari++;
    }
  }
  jumlahHari += jumlahHariPerBulanMasehi[bulan-1];
  if ( (bulan >= 2) && !(tahun % 4)) 
  { 
    jumlahHari++;
  }
  jumlahHari+= tanggal;
  return jumlahHari + 259;// base 18 April 1999
}
 
void masehiKeHijriah(uint32_t HariMasehi, byte *tanggal, byte *bulan, uint16_t *tahun)
{
  uint16_t sisaHari;
  double tahunBulan = 354.367068;
  uint16_t jumlahHariPerBulanHijriah[] = {0,30,59,89,118,148,177,207,236,266,295,325,354};
  
  *tahun = floor(HariMasehi/tahunBulan);
  sisaHari = HariMasehi - (tahunBulan * *tahun);
  
  if (sisaHari==0){
    sisaHari=30;
    *bulan=12;
  } else {
    for(byte i=0;i<sizeof(jumlahHariPerBulanHijriah);i++)
  {
    if(sisaHari <= jumlahHariPerBulanHijriah[i])
    {
      sisaHari -= jumlahHariPerBulanHijriah[i-1];
      *bulan = i;
      break;
    }
  }
  }
  
  *tanggal = sisaHari;
  *tahun += 1420;
}

void GetHijriah(byte tanggalM, byte bulanM, uint16_t tahunM, byte *tanggal, byte *bulan, uint16_t *tahun){
  uint32_t jumlahHari;
  byte tanggalHijriah;
  byte bulanHijriah;
  uint16_t tahunHijriah;
  jumlahHari = jumlahHariDariTanggal(tanggalM, bulanM, tahunM - 2000);
  masehiKeHijriah(jumlahHari, &tanggalHijriah, &bulanHijriah, &tahunHijriah);
  *tanggal = tanggalHijriah;
  *bulan = bulanHijriah;
  *tahun = tahunHijriah;
}
