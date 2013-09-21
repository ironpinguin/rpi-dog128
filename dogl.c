#include <dogl.h>

unsigned char ram[128][64];
unsigned char *font;
int fontWidth;
int fontHight;
int fontLength;

void selectFont(fontId)
{
  fontWidth  = fontListe[fontId][0];
  fontHight  = fontListe[fontId][1];
  fontLength = fontListe[fontId][2];
}

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
  unsigned char bits = 8;



  startXPosition = xpos;
  for (x = 0; x < fontLength; x++) {
    byte = font26[character][x];
    // fix for fonts with lesser then 8 width.
    if (fontWidth < 8) {
      bits = fontWidth;
      // move away filling bits.
      byte = byte>>(8-fontWidth);
    }
    for (y = 0; y < bits; y++) {
      value = byte&1;
      byte = byte>>1;
      ram[xpos][ypos] = value;
      position++;
      xpos++;
      if (position == fontWidth) {
        position = 0;
        xpos = startXPosition;
        ypos++;
      }
    }
  }
}

void writeText(char *buff, int xpos, int ypos)
{
  int len, x;
  len = strlen(buff);
  
  for (x=0; x < len; x++) {
    if (x != 0) xpos += fontWidth;
    setChar(buff[x], xpos, ypos);
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
