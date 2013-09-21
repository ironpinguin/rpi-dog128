#include <dogl.h>

unsigned char ram[128][64];

void clear()
{
  int y = 0;
  int x = 0;

  for (y=0;y<64;y++)
  {
    for (x=0;x<128;x++)
    {
      ram[x][y] = 0;
    }
  }
}

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
  char cmd;
  cmdMode();
  cmd = CMDSETPAGEADR + page;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETCOLADRHI + colhi;
  wiringPiSPIDataRW(0, &cmd, 1);
  cmd = CMDSETCOLADRLO + collo;
  wiringPiSPIDataRW(0, &cmd, 1);
}

void setChar(character, xpos, ypos)
{
  int x = 0, y = 0;
  int value, position = 0, startXPosition;
  unsigned char byte;

  startXPosition = xpos;
  //for (x = 0; x < 212; x++) {
  for (x = 0; x < 120; x++) {
    byte = font[character][x];
    for (y = 0; y < 8; y++) {
      value = byte&1;
      byte = byte>>1;
      ram[xpos][ypos] = value;
      position++;
      xpos++;
      //if (position == 32) {
      if (position == 24) {
        position = 0;
        xpos = startXPosition;
        ypos++;
      }
    }
  }
}

void print()
{
  int page, p, byte;
  int x = 0;
  char pixelstowrite[8];
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
  char cmd;

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
  int start = 5;
  int c1, c2;

  init();
  pwmWrite(LED, 150);
  clear();

  print();
  
  setChar('A', 2, 5);
  setChar('l', 34, 5);
  setChar('e', 66, 5);
  setChar('x', 98, 5);

  print();

  

  return 0;
}
