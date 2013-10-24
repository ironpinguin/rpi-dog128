#include <stdio.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"

#define CMDSETPAGEADR 0xB0

#define DISPLAYFILE "display.log"
#define COMMANDFILE "command.log"

unsigned char display[128][64];
int modus = 0;
int page = 0;

int di = 0;
int led = 1;
int reset = 2;
FILE *displayfd;
FILE *commandfd;

FILE *checkAndOpenFile(FILE *fd, char* file)
{
    if (fd == NULL) {
        fd = fopen(file, "w");
    }

    return fd;
}

void mockTest() {
    int x, y;
    displayfd = checkAndOpenFile(displayfd, DISPLAYFILE);
    fprintf(displayfd, "DISPLAY:\n");
    for (y=0; y < 64; y++) {
        for(x=0; x < 128; x++) {
            fprintf(displayfd, "%i", display[x][y]);
        }
        fprintf(displayfd, "\n");
    }
}

void writePage(unsigned char *data, int len) {
    int column, row, byte, value;
    // TODO write data to page (8x128 bit)
    for(row=0; row < 128; row++) {
        column = page * 8;
        byte = data[row];
        for(int i = 0; i < 8; i++) {
            value = byte&1;
            byte = byte>>1;
            display[row][column+i] = value;
        }
    }
}

int digitalRead(int pin) {
    return (pin % 2);
}

void digitalWrite(int pin, int value) {
    commandfd = checkAndOpenFile(commandfd, COMMANDFILE);

    if (pin == di) {
        modus = value;
    }

    if (pin == 0 && value == 0) {
        fprintf(commandfd, "SET COMMAND\n");
    }
    if (pin == 0 && value == 1) {
        fprintf(commandfd, "SET WRITE\n");
    }
}

void pwmWrite(int pin, int value) {
}

void pinMode(int pin, int mode) {
}

int wiringPiSetupGpio () {
    return 1;
}

int wiringPiSetup () {
    return 1;
}

int wpiPinToGpio (int wpiPin)
{
      return wpiPin & 63;
}

int wiringPiSPIGetFd (int channel) {
    return 3;
}

int wiringPiSPIDataRW(int channel, unsigned char *data, int len) {
    int c, cmd;

    commandfd = checkAndOpenFile(commandfd, COMMANDFILE);
    if (modus == 0) {
        fprintf(commandfd, "COMMAND: ");
        cmd = (int)data[0];
        if (cmd <= CMDSETPAGEADR+7 && cmd >= CMDSETPAGEADR) {
            page = cmd - CMDSETPAGEADR;
        }
    } else {
        fprintf(commandfd, "WIRTE: ");
        writePage(data, len);
    }

    for (c = 0; c < len; c++) {
        fprintf(commandfd, "%X", data[c]);
    }
    fprintf(commandfd, "\n");
    if (page == 7 && modus == 1) {
        mockTest();
    }
    return 3;
}

int wiringPiSPISetup (int channel, int speed) {
    return 3;
}