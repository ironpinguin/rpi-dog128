#include "wiringPi.h"
#include "wiringPiSPI.h"

void (*pinMode)     (int pin, int mode);
int  (*digitalRead) (int pin);
void (*digitalWrite)(int pin, int value);

int digitalReadWMock(int pin) {
    return (pin % 2);
}

void digitalWriteWMock(int pin, int value) {
}

void pwmWrite(int pin, int value) {
}

void pinModeWMock(int pin, int mode) {
}

int wiringPiSetupGpio () {
    pinMode      = pinModeWMock;
    digitalRead  = digitalReadWMock;
    digitalWrite = digitalWriteWMock;

    return 1;
}

int wiringPiSetup () {
    pinMode      = pinModeWMock;
    digitalRead  = digitalReadWMock;
    digitalWrite = digitalWriteWMock;

    return 1;
}

int wpiPinToGpio (int wpiPin)
{
      return wpiPin & 63;
}

int wiringPiSPIGetFd (int channel) {
}

int wirignPiSPIDataRW (int channel, unsigned char *data, int len) {
}

int wiringPiSPISetup (int channel, int speed) {
}