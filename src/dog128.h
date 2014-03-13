#define _GNU_SOURCE 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"

#ifndef DOGL_H
#define DOGL_H

struct Configuration
{
	int di;
	int led; 
	int spiCS;
};

extern struct Configuration dog128config;

// GPIO PINs numbering from wiringPi
#define DI    6
#define LED   1
#define SPICS 0

// LCD display commands
#define CMDDISPLOFF 0xAE
#define CMDDISPLON  0xAF
// startline address + line (0 to 63) 
#define CMDSETSTARTLINE 0x40
// +pagenumber (0 to 7)
#define CMDSETPAGEADR 0xB0
// + colnr_hi
#define CMDSETCOLADRHI 0x10
// + colnr_lo
#define CMDSETCOLADRLO 0x00
#define CMDADCNORMAL 0xA0
#define CMDADCREVERSE 0xA1
#define CMDDISPLAYNORMAL 0xA6
#define CMDDISPLAYREVERSE 0xA7
#define CMDALLPOINTSOFF 0xA4
#define CMDALLPOINTSON 0xA5
#define CMDSETLCDBIAS 0xA2
#define CMDRESET 0xE2
#define CMDCOMOUTMODE 0xC0
#define CMDSETPOWERCTRL 0x2F
// + ratio (0 to 7)
#define CMDSETRESISTORRATIO 0x20
#define CMDSETVOLMODE 0x81
// + val (0 to 63)
#define CMDSETVOLMODEVAL 0x00
#define CMDINDICATOROFF 0xAC
#define CMDINDICATORVAL 0x00
#define CMDSETBOOSTERRATIO 0xF8
// + val (0 to 3)
#define CMDSETBOOSTERRATIOVAL 0x00
#define CMDNOP 0xE3

#ifndef FONT_LIST_H
#define FONT_LIST_H

#define FONT4x6_1 0
#define FONT4x6_2 1
#define FONT5x12_1 2
#define FONT5x12_2 3
#define FONT5x8_1 4
#define FONT5x8_2 5
#define FONT6x10_1 6
#define FONT6x10_2 7
#define FONT6x8_1 8
#define FONT6x8_2 9
#define FONT7x12_1 10
#define FONT7x12_2 11
#define FONT7x12b_1 12
#define FONT7x12b_2 13
#define FONT8x12_1 14
#define FONT8x12_2 15
#define FONT8x14_1 16
#define FONT8x14_2 17
#define FONT8x8_1 18
#define FONT8x8_2 19
#define FONT10x16_1 20
#define FONT10x16_2 21
#define FONT12x16_1 22
#define FONT12x16_2 23
#define FONT12x20_1 24
#define FONT12x20_2 25
#define FONT16x26_1 26
#define FONT16x26_2 27
#define FONT22x36_1 28
#define FONT22x36_2 29
#define FONT24x40_1 30
#define FONT24x40_2 31
#define FONT32x53_1 32
#define FONT32x53_2 33

#endif /* FONT_LIST_H */

extern void show();

extern void init(int di, int led, int spiCS);
extern void backlight(int value);
extern void contrast(int value);
extern void displaynormal(bool value);
extern void invert();

extern void digitalWrite(int di, value);

#ifndef DOG_SCREEN
#define DOG_SCREEN

extern void clear();

extern void initFonts();
extern void selectFont(int fontId);
extern void setChar(char character, int xpos, int ypos);
extern void writeText(char *buff, int xpos, int ypos);
extern void setPenColor(int color);
extern void dot(int xpos, int ypos);
extern void line(int startxpos, int startypos, int endxpos, int endypos);
extern void rect(int startxpos, int startypos, int endxpos, int endypos, bool full);
extern void circle(int centerx, int centery, int radius, bool fill);
extern void ellipse (int cx, int cy, int xRadius, int yRadius, int filled);

#endif /* DOG_SCREEN */

#endif /* DOGL_H */
