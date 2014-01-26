#define GLMOCK
#include <SDL/SDL_ttf.h>

#include "wiringpimock.h"

void writePage(unsigned char *data, int len) {


  int column, row, byte, value;

    for(row=0; row < 128; row++) {
        column = page * 8;
        byte = data[row];
        for(int i = 0; i < 8; i++) {
            value = byte&1;
            byte = byte>>1;

            display[row*64+column+i] = value;
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

void pullUpDnControl(int pin, int pud) {
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

int wiringPiISR (int pin, int mode, void (*function)(void)) {
    return 1;
}

int wiringPiSPIDataRW(int channel, unsigned char *data, int len) {
    int cmd;

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

static void renderQuad(float x1, float y1, float x2, float y2) {
  float z = 0.0;

  glBegin(GL_QUADS);

  glVertex3f(x1, y1, z);
  glVertex3f(x2, y1, z);
  glVertex3f(x2, y2, z);
  glVertex3f(x1, y2, z);

  glEnd();
}

static void renderDisplayPixel(float y, float x, float r, float g, float b) {
  glColor3f(r, g, b);

  float view_width= SCREEN_WIDTH;
  float view_height= SCREEN_HEIGHT;
  float sizex = view_width / (float)PIXEL_WIDTH;
  float sizey = view_height / (float)PIXEL_HEIGHT;
  float offsetx= XOFFSET + x * sizex;
  float offsety= YOFFSET - y * sizey;

  renderQuad(offsetx, offsety, offsetx + sizex, offsety - sizey);
}

static void displayfunc(void) {
  int x, y;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(BGCOLOR);
  renderQuad(XOFFSET, YOFFSET, XOFFSET+SCREEN_WIDTH, YOFFSET-SCREEN_HEIGHT);

  for (x=0; x<PIXEL_WIDTH; x++) {
    for (y=0; y<PIXEL_HEIGHT; y++) {
      if (display[x*64+y] > 0) {
        renderDisplayPixel(y, x, PIXEL_COLOR);
      }
    }
  }

  glutSwapBuffers();

  glutPostRedisplay();
}

static void sdlDisplay(void)
{
    
}

int wiringPiSPISetup (int channel, int speed) {
  int pid, argc = 0;

  pid = fork();

  if (pid == 0) {
    // Child process, allocate shared memory executing the GLUT main loop:

    shmid = shmget(SHMKEY, SHMSIZE, 0666 | IPC_CREAT);

    if (shmid == -1) {
      printf("SHMGET ERROR (CHILD)\n");
    }

    display   = shmat(shmid, NULL, 0);
    if (display == NULL) {
      printf("SHMAT ERROR (CHILD)\n");
    }
    //shmdt(shmid);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER);
    TTF_Init();
    SDL_SetVideoMode(XOFFSET+SCREEN_WIDTH, YOFFSET-SCREEN_HEIGHT, 16, 0);
    SDL_CreateThread(&sdlDisplay());

    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("cpi_dogl emu");
    glutDisplayFunc(displayfunc);
    glutMainLoop();
  } else if (pid > 0) {
    // Init OK, act normally:
    shmid     = shmget(SHMKEY, SHMSIZE, 0);
    if (shmid == -1) {
        printf("SHMGET ERROR (PARENT)\n");
      }
    display   = shmat(shmid, NULL, 0);
      if (display == NULL) {
        printf("SHMAT ERROR (PARENT)\n");
      }
      display[2] = 1;
    return 3;
  } else {
    // Something went totally wrong
    printf ("FORK FAIL.");
    return -1;
  }

  return 0;
}
