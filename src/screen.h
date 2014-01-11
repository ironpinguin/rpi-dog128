#ifndef DOGL_SCREEN
#define DOGL_SCREEN
#define _GNU_SOURCE 1
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fonts.h"

extern unsigned char ram[128][64];

extern unsigned char *font;
extern int fontWidth;
extern int fontHight;
extern int fontLength;
extern int penColor;

#ifndef DOG_SCREEN
#define DOG_SCREEN
void clear();

void initFonts();
void selectFont(int fontId);
void setChar(char character, int xpos, int ypos);
void writeText(char *buff, int xpos, int ypos);
void setPenColor(int color);
void dot(int xpos, int ypos);
void line(int startxpos, int startypos, int endxpos, int endypos);
void rect(int startxpos, int startypos, int endxpos, int endypos, bool full);
void circle(int centerx, int centery, int radius, bool fill);
void ellipse (int cx, int cy, int xRadius, int yRadius, int filled);

#endif

#endif
