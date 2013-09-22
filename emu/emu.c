#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#define PIXEL_WIDTH  128
#define PIXEL_HEIGHT 64

// Common display functionality to be refactored:

unsigned char ram[128][64];

void clear()
{
  int y = 0;
  int x = 0;

  for (y=0;y<PIXEL_HEIGHT;y++)
  {
    for (x=0;x<PIXEL_WIDTH;x++)
    {
      ram[x][y] = 0;
    }
  }
}

// GL functionality:

static void
renderQuad(float x1, float y1, float x2, float y2)
{
    float z = 0.0;

    glBegin(GL_QUADS);
    
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
    
    glEnd();
}

static void
renderDisplayPixel(float y, float x)
{
    float sizex   = 2.0 / (float)PIXEL_WIDTH;
    float sizey   = 2.0 / (float)PIXEL_HEIGHT;
    float offsetx = -1.0 + x * sizex;
    float offsety = 1.0 - y * sizey;

    renderQuad(offsetx, offsety, offsetx + sizex, offsety - sizey); 
}

static void
display (void)
{
    int x,y;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,1,1);

    for (x=0;x<PIXEL_WIDTH;x++)
    {
        for (y=0;y<PIXEL_HEIGHT;y++)
        {
            if (ram[x][y] > 0) {
                renderDisplayPixel(y,x);
            }
        }
    }

    glutSwapBuffers();
}

int
main(int argc, char * argv[])
{
    // Set display:
    clear();
    ram[1][1] = (char)1;
    ram[2][1] = (char)1;
    ram[3][1] = (char)1;
    ram[2][2] = (char)1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Main");

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS;
}
