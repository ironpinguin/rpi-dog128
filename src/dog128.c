#include "dog128.h"
#include "screen.h"

bool dog128init = 0;

struct Configuration dog128config;

/*
 * internal function to set the dogl|m128 display in write mode.
 */
void writeMode()
{
  digitalWrite(dog128config.di, 1);
}

/*
 * internal function to set the dogl|m128 display in command mode.
 */
void cmdMode()
{
  digitalWrite(dog128config.di, 0);
}

/*
 * internal function to set the position for the next writing pixels.
 */
void setAdr(int page, int colhi, int collo)
{
  unsigned char cmd;
  cmdMode();
  cmd = CMDSETPAGEADR + page;
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
  cmd = CMDSETCOLADRHI + colhi;
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
  cmd = CMDSETCOLADRLO + collo;
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
}

/*
 * external function to write the content of the internal memory to the display.
 */
void show()
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
    wiringPiSPIDataRW(dog128config.spiCS, line[page], 128);
  }
}

/*
 * external function to initialing the dogl display in only 3.3V not flipped.
 */
void init(int di, int led, int spiCS)
{
  unsigned char cmd;

  dog128config.di = di;
  dog128config.led = led;
  dog128config.spiCS = spiCS;

  wiringPiSetup();

  pinMode(di, OUTPUT);
  pinMode(led, PWM_OUTPUT);
  wiringPiSPISetup(spiCS, 10000000);
  cmdMode();
  cmd = CMDSETSTARTLINE;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDADCREVERSE;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDCOMOUTMODE;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDDISPLAYNORMAL;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETLCDBIAS;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETPOWERCTRL;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETBOOSTERRATIO;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETBOOSTERRATIOVAL;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETRESISTORRATIO + 7;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETVOLMODE;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDSETVOLMODEVAL + 13;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDINDICATOROFF;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDINDICATORVAL;
  wiringPiSPIDataRW(spiCS, &cmd, 1);
  cmd = CMDDISPLON;
  wiringPiSPIDataRW(spiCS, &cmd, 1);

  writeMode();

  dog128init = true;
}

void backlight(int value) {
  if (value < 0 || value > 100) {
    // TODO error handling
    return;
  }
  pwmWrite(dog128config.led, abs(10.10 * value));
}

void contrast(int value) {
  unsigned char cmd;
  if (value < 5 || value > 25) {
    // TODO error handling
    return;
  }
  cmdMode();
  cmd = CMDSETVOLMODE;
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
  cmd = CMDSETVOLMODEVAL + value;
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
  writeMode();
}

void displaynormal(bool value) {
  unsigned char cmd;

  if (value) {
    cmd = CMDDISPLAYNORMAL;
  } else {
    cmd = CMDDISPLAYREVERSE;
  }
  cmdMode();
  wiringPiSPIDataRW(dog128config.spiCS, &cmd, 1);
  writeMode();
}

void invert() {
  for(int x=0; x < 128; x++) {
    for(int y=0; y < 64; y++) {
      if (ram[x][y] == 1) {
        ram[x][y] = 0;
      } else {
        ram[x][y] = 1;
      }
    }
  }
}
