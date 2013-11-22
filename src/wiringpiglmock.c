#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#endif

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

    if (pin == di) {
        modus = value;
    }

    if (pin == 0 && value == 0) {
        // GLMOCK SET COMMAND
    }
    if (pin == 0 && value == 1) {
        // GLMOCK SET WRITE
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
        // GLMOCK COMMAND
        cmd = (int)data[0];
        if (cmd <= CMDSETPAGEADR+7 && cmd >= CMDSETPAGEADR) {
            page = cmd - CMDSETPAGEADR;
        }
    } else {
      // GLMOCK WRITE
        writePage(data, len);
    }

    if (page == 7 && modus == 1) {
        // GLMOCK TEST
    }

    return 3;
}

static void displayfunc(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

int wiringPiSPISetup (int channel, int speed) {
  int pid, argc = 0;

  pid = fork();

  if (pid == 0) {
    // Child process, executing the GLUT main loop:
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("cpi_dogl emu");
    glutDisplayFunc(displayfunc);
    glutMainLoop();
  } else if (pid > 0) {
    // Init OK, act normally:
    return 3;
  } else {
    // Something went totally wrong, TODO log an error:
    printf ("FORK FAIL.");
    return -1;
  }
}