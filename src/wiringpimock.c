#include <stdio.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"

#define CMDSETPAGEADR 0xB0

unsigned char display[128][64];
int modus = 0;
int page = 0;

int di = 0;
int led = 1;
int reset = 2;

void mockTest() {
    int x, y;
    for (y=0; y < 64; y++) {
        for(x=0; x < 128; x++) {
            printf("%i", display[x][y]);
        }
        printf("\n");
    }
    printf("\n");
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
//    printf("PIN %u => VALUE %u\n", pin, value);
    if (pin == di) {
        modus = value;
    }

    if (pin == 0 && value == 0) {
        printf("COMMAND: ");
    }
    if (pin == 0 && value == 1) {
        printf("WriteDisplay: \n");
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
    if (modus == 0) {
        cmd = (int)data[0];
        if (cmd <= CMDSETPAGEADR+7 && cmd >= CMDSETPAGEADR) {
            page = cmd - CMDSETPAGEADR;
        }
    } else {
        writePage(data, len);
    }

    for (c = 0; c < len; c++) {
        printf("%X", data[c]);
    }
    printf("\n");
    if (page == 7 && modus == 1) {
        mockTest();
    }
    return 3;
}

int wiringPiSPISetup (int channel, int speed) {
    return 3;
}