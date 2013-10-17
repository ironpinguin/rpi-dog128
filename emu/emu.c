#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#endif

#include "../src/screen.h"

#define PIXEL_WIDTH   128
#define PIXEL_HEIGHT  64

#define SCREEN_HEIGHT 1.6
#define SCREEN_WIDTH  2.0

#define XOFFSET       -1.0
#define YOFFSET       0.8

#define BGCOLOR       0.8,0.8,0.1
#define PIXEL_COLOR   0.3,0.3,0.3

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

static void display(void) {
  int x, y;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(BGCOLOR);
  renderQuad(XOFFSET, YOFFSET, XOFFSET+SCREEN_WIDTH, YOFFSET-SCREEN_HEIGHT);

  for (x=0; x<PIXEL_WIDTH; x++) {
    for (y=0; y<PIXEL_HEIGHT; y++) {
      if (ram[x][y] > 0) {
        renderDisplayPixel(y, x, PIXEL_COLOR);
      }
    }
  }

  glutSwapBuffers();
}

int main(int argc, char * argv[]) {
  initFonts();
  char *buff = "Hallo";
  // Set display:
  clear();
  selectFont(FONT10x16_1);
  writeText(buff, 1, 1);
  buff = "Michele!";
  writeText(buff, 1, 27);
  //circle(50, 30, 15, true);

  // GL init:
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow("cpi_dogl emu");

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}
