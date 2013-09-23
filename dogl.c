#include "dogl.h"
#include "screen.h"

void writeMode()
{
  digitalWrite(DI, 1);
}

void cmdMode()
{
  digitalWrite(DI, 0);
}

void setAdr(page, colhi, collo)
{
  unsigned char cmd;
  cmdMode();
  cmd = CMDSETPAGEADR + page;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETCOLADRHI + colhi;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETCOLADRLO + collo;
  wiringPiSPIDataRW(0, &cmd, 1);
}

void print()
{
  int page, byte;
  int x = 0;
  unsigned char line[8][128];
  int bit;

  for (page = 0; page < 8; page++)
  {
    for (x = 0;x < 128; x++)
    {
      byte = 0;
      for (bit = 0; bit < 8; bit++)
      {
        byte = byte + (ram[x][page * 8 + bit] << bit);
      }
      line[page][x] = byte;
    }
  }

  for (page = 0;page<8;page++)
  {
    setAdr(page, 0, 0);
    writeMode();
    wiringPiSPIDataRW(0, line[page], 128);
  }
}

void init()
{
  unsigned char cmd;

  wiringPiSetup();

  pinMode(DI, OUTPUT);
  pinMode(LED, PWM_OUTPUT);
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, 1);
  wiringPiSPISetup(0, 10000000);
  cmdMode();
  cmd = CMDSETSTARTLINE;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDADCREVERSE;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDCOMOUTMODE;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDDISPLAYNORMAL;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETLCDBIAS;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETPOWERCTRL;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETBOOSTERRATIO;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETBOOSTERRATIOVAL;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETRESISTORRATIO + 7;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETVOLMODE;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETVOLMODEVAL + 13;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDINDICATOROFF;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDINDICATORVAL;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDDISPLON;
  wiringPiSPIDataRW(0, &cmd, 1);
  
}

int main()
{
  char *buff = "Hallo";

  init();
  selectFont(FONT16x26_1);
  pwmWrite(LED, 250);
  clear();

  print();
  
  writeText(buff, 1, 1); 
  buff = "Alex!";
  writeText(buff, 1, 27);

  print();

  return 0;
}
