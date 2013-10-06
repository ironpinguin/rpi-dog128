#ifndef DOGL_SCREEN
#define DOGL_SCREEN

#include "fonts.h"

extern unsigned char ram[128][64];

extern unsigned char *font;
extern int fontWidth;
extern int fontHight;
extern int fontLength;

#ifndef DOG_SCREEN
#define DOG_SCREEN
void clear();

void selectFont(int fontId);
void setChar(char character, int xpos, int ypos);
void writeText(char *buff, int xpos, int ypos);

#endif

#endif
