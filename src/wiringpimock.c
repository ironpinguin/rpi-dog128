#include <stdio.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"

int digitalRead(int pin) {
    return (pin % 2);
}

void digitalWrite(int pin, int value) {
//    printf("PIN %u => VALUE %u\n", pin, value);
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
    int c;
    for (c = 0; c < len; c++) {
        printf("%X", data[c]);
    }
    printf("\n");
    return 3;
}

int wiringPiSPISetup (int channel, int speed) {
    return 3;
}