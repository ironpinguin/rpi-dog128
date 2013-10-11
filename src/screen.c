#include <string.h>

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

void initFont(int fontId, int fontSize, char *buf) {
  int i;
  fontData[fontId] = malloc(256*sizeof(char *));
  for (i=0; i<256; i++) {
    fontData[fontId][i] = malloc(fontSize*sizeof(char));
    memcpy(fontData[fontId][i], buf + i*fontSize*sizeof(char), fontSize
        *sizeof(char));
  }
}

void initFonts() {
  fontData = malloc(MAX_FONTS*sizeof(char *));
  initFont(20, 32, (char *)font20);
  initFont(26, 52, (char *)font26);
  // TODO Add remaining fonts...
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
