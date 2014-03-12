/* 
 * File:   wiringpimock.h
 * Author: michele
 *
 * Created on 21. Januar 2014, 10:27
 */

#ifndef WIRINGPIMOCK_H
#define	WIRINGPIMOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef GLMOCK

#include <sys/ipc.h>
#include <sys/shm.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#endif

#endif

#include "wiringPi.h"
#include "wiringPiSPI.h"

#define CMDSETPAGEADR 0xB0

#define DISPLAYFILE "display.log"
#define COMMANDFILE "command.log"
    
#ifdef GLMOCK
#define PIXEL_WIDTH   128
#define PIXEL_HEIGHT  64

#define SCREEN_HEIGHT 1.6
#define SCREEN_WIDTH  2.0

#define XOFFSET       -1.0
#define YOFFSET       0.8

#define BGCOLOR       0.8,0.8,0.1
#define PIXEL_COLOR   0.3,0.3,0.3

#define SHMKEY  2014
#define SHMSIZE 128*64

int shmid;

unsigned char *display;
#else
unsigned char display[128][64];
#endif
int modus = 0;
int page = 0;

int di = 6;
int led = 1;
int reset = 2;
FILE *displayfd;
FILE *commandfd;
    
#ifdef	__cplusplus
}
#endif

#endif	/* WIRINGPIMOCK_H */

