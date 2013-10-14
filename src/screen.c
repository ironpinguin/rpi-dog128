#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "screen.h"

#define MAX_FONTS 100

unsigned char ram[128][64];

char ***fontData;
int fontWidth;
int fontHight;
int fontLength;
int fontId;

void clear() {
  int y = 0;
  int x = 0;

  for (y=0; y<64; y++) {
    for (x=0; x<128; x++) {
      ram[x][y] = 0;
    }
  }
}

void initFont(int fontId, char *buf) {
  int i;
  int fontSize = fontListe[fontId][2];
  fontData[fontId] = malloc(256*sizeof(char *));
  for (i=0; i<256; i++) {
    fontData[fontId][i] = malloc(fontSize*sizeof(char));
    memcpy(fontData[fontId][i], buf + i*fontSize*sizeof(char), fontSize
        *sizeof(char));
  }
}

void initFonts() {
  fontData = malloc(MAX_FONTS*sizeof(char *));

  initFont(0, (char *)font0);
  initFont(1, (char *)font1);
  initFont(2, (char *)font2);
  initFont(3, (char *)font3);
  initFont(4, (char *)font4);
  initFont(5, (char *)font5);
  initFont(6, (char *)font6);
  initFont(7, (char *)font7);
  initFont(8, (char *)font8);
  initFont(9, (char *)font9);
  initFont(10, (char *)font10);
  initFont(11, (char *)font11);
  initFont(12, (char *)font12);
  initFont(13, (char *)font13);
  initFont(14, (char *)font14);
  initFont(15, (char *)font15);
  initFont(16, (char *)font16);
  initFont(17, (char *)font17);
  initFont(18, (char *)font18);
  initFont(19, (char *)font19);
  initFont(20, (char *)font20);
  initFont(21, (char *)font21);
  initFont(22, (char *)font22);
  initFont(23, (char *)font23);
  initFont(24, (char *)font24);
  initFont(25, (char *)font25);
  initFont(26, (char *)font26);
  initFont(27, (char *)font27);
  initFont(28, (char *)font28);
  initFont(29, (char *)font29);
  initFont(30, (char *)font30);
  initFont(31, (char *)font31);
  initFont(32, (char *)font32);
  initFont(33, (char *)font33);
}

void selectFont(int newFontId) {
  fontId = newFontId;
  fontWidth = fontListe[fontId][0];
  fontHight = fontListe[fontId][1];
  fontLength = fontListe[fontId][2];
}

void setChar(char character, int xpos, int ypos) {
  int x = 0, y = 0;
  int value, position = 0, startXPosition;
  unsigned char byte;
  unsigned char bits = 8;

  startXPosition = xpos;
  for (x = 0; x < fontLength; x++) {
    printf("trace font %i , char %c [%i] and x %i\n", fontId, character, (int)character, x);
    byte = fontData[fontId][(int)character][x];
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

void writeText(char *buff, int xpos, int ypos) {
  int len, x;
  len = strlen(buff);

  for (x=0; x < len; x++) {
    if (x != 0)
      xpos += fontWidth;
    setChar(buff[x], xpos, ypos);
  }
}
