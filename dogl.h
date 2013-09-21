#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#ifndef DOGL_H
#define DOGL_H
#include <fonts/24x40_horizontal_LSB_1.h>

// GPIO PINs numbering from wiringPi
#define DI    0
#define LED   1
#define RESET 2

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

void clear();
void show();
void init();

#endif /* DOGL_H */
