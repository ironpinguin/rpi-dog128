#include "screen.h"

#define MAX_FONTS 100

unsigned char ram[128][64];

char ***fontData;
int fontWidth;
int fontHight;
int fontLength;
int fontId;
int penColor = 1;


void clear() {
  int y = 0;
  int x = 0;

  for (y=0; y<64; y++) {
    for (x=0; x<128; x++) {
      ram[x][y] = 0;
    }
  }
}

void initFont(int fontId, char *buf) {
  int i;
  int fontSize = fontListe[fontId][2];
  fontData[fontId] = malloc(256*sizeof(char *));
  for (i=0; i<256; i++) {
    fontData[fontId][i] = malloc(fontSize*sizeof(char));
    memcpy(fontData[fontId][i], buf + i*fontSize*sizeof(char), fontSize
        *sizeof(char));
  }
}

void initFonts() {
  fontData = malloc(MAX_FONTS*sizeof(char *));

  initFont(0, (char *)font0);
  initFont(1, (char *)font1);
  initFont(2, (char *)font2);
  initFont(3, (char *)font3);
  initFont(4, (char *)font4);
  initFont(5, (char *)font5);
  initFont(6, (char *)font6);
  initFont(7, (char *)font7);
  initFont(8, (char *)font8);
  initFont(9, (char *)font9);
  initFont(10, (char *)font10);
  initFont(11, (char *)font11);
  initFont(12, (char *)font12);
  initFont(13, (char *)font13);
  initFont(14, (char *)font14);
  initFont(15, (char *)font15);
  initFont(16, (char *)font16);
  initFont(17, (char *)font17);
  initFont(18, (char *)font18);
  initFont(19, (char *)font19);
  initFont(20, (char *)font20);
  initFont(21, (char *)font21);
  initFont(22, (char *)font22);
  initFont(23, (char *)font23);
  initFont(24, (char *)font24);
  initFont(25, (char *)font25);
  initFont(26, (char *)font26);
  initFont(27, (char *)font27);
  initFont(28, (char *)font28);
  initFont(29, (char *)font29);
  initFont(30, (char *)font30);
  initFont(31, (char *)font31);
  initFont(32, (char *)font32);
  initFont(33, (char *)font33);
}

void setPenColor(int color) {
  if (color < 0 && color > 1) {
    // TODO error handling;
    return;
  }

  penColor = color;
}

bool positionCheck(int x, int y) {
  if (x >= 0 && x <= 127) {
    if (y >= 0 && y <= 63) {
      return false;
    }
  }

  return true;
}

void selectFont(int newFontId) {
  fontId = newFontId;
  fontWidth = fontListe[fontId][0];
  fontHight = fontListe[fontId][1];
  fontLength = fontListe[fontId][2];
}

void setChar(char character, int xpos, int ypos) {
  int x = 0, y = 0;
  int value, position = 0, startXPosition;
  unsigned char byte;
  unsigned char bits = 8;

  /** Check if the given start Position is in display range **/
  if (positionCheck(xpos, ypos) && positionCheck(xpos + fontLength, ypos + fontWidth)) {
    printf("Out of position CHAR %c at %i:%i\n", character, xpos, ypos); // TODO Error message.
    return;
  }

  startXPosition = xpos;
  for (x = 0; x < fontLength; x++) {
    byte = fontData[fontId][(int)character][x];
    // fix for fonts with lesser then 8 width.
    if (fontWidth < 8) {
      bits = fontWidth;
      // move away filling bits.
      byte = byte>>(8-fontWidth);
    }
    for (y = 0; y < bits; y++) {
      value = byte&1;
      byte = byte>>1;
      ram[xpos][ypos] = value;
      position++;
      xpos++;
      if (position == fontWidth) {
        position = 0;
        xpos = startXPosition;
        ypos++;
      }
    }
  }
}

void writeText(char *buff, int xpos, int ypos) {
  int len, x;
  len = strlen(buff);

  for (x=0; x < len; x++) {
    if (x != 0)
      xpos += fontWidth;
    setChar(buff[x], xpos, ypos);
  }
}

void pen(int color) {
  if (color == 0 || color == 1) {
    penColor = color;
  }
}

void dot(int xpos, int ypos) {
  if (positionCheck(xpos, ypos)) {
    // TODO Error message.
    return;
  }
  ram[xpos][ypos] = penColor;
}

void line(int startXpos, int startYpos, int endXpos, int endYpos) {
  int dx, dy, err, sx, sy, e2;
  if (positionCheck(startXpos, startYpos) && positionCheck(endXpos, endYpos)) {
    // TODO Error message.
    return;
  }
  dx = abs(endXpos - startXpos);
  if (startXpos < endXpos) {
    sx = 1;
  } else {
    sx = -1;
  }
  dy = -abs(endYpos - startYpos);
  if (startYpos < endYpos) {
    sy = 1;
  } else {
    sy = -1;
  }
  err = dx + dy;
  while (true) {
    dot(startXpos, startYpos);
    if (startXpos == endXpos && startYpos == endYpos) break;
    e2 = 2*err;
    if (e2 > dy) {
      err += dy;
      startXpos += sx;
    }
    if (e2 < dx) {
      err += dx;
      startYpos += sy;
    }
  }
}

void rect(int startXpos, int startYpos, int endXpos, int endYpos, bool full) {
  int x1set, x2set;

  if (full) {
    if (startXpos <= endXpos) {
      x1set = startXpos;
      x2set = endXpos;
    } else {
      x1set = endXpos;
      x2set = startXpos;
    }
    for (int i=x1set; i < x2set + 1; i++) {
      line(i, startYpos, i, endYpos);
    }
  } else {
    line(startXpos, startYpos, startXpos, endYpos);
    line(startXpos, startYpos, endXpos, startYpos);
    line(startXpos, endYpos, endXpos, endYpos);
    line(endXpos, endYpos, endXpos, startYpos);
  }
}

// Purpose:       Draw a circle on a graphic LCD
// Inputs:        (x,y) - the center of the circle
//                radius - the radius of the circle
//                fill - YES or NO
void circle(int x, int y, int radius, bool fill)
{
   signed int a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;

   do
   {
      if(fill)
      {
         line(x-a, y+b, x+a, y+b);
         line(x-a, y-b, x+a, y-b);
         line(x-b, y+a, x+b, y+a);
         line(x-b, y-a, x+b, y-a);
      }
      else
      {
         dot(a+x, b+y);
         dot(b+x, a+y);
         dot(x-a, b+y);
         dot(x-b, a+y);
         dot(b+x, y-a);
         dot(a+x, y-b);
         dot(x-a, y-b);
         dot(x-b, y-a);
      }

      if(P < 0)
         P+= 3 + 2*a++;
      else
         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}

/*
 * ellipse:
 *  Fast ellipse drawing algorithm by 
 *      John Kennedy
 *  Mathematics Department
 *  Santa Monica College
 *  1900 Pico Blvd.
 *  Santa Monica, CA 90405
 *  jrkennedy6@gmail.com
 *  -Confirned in email this algorithm is in the public domain -GH-
 *********************************************************************************
 */

static void plot4ellipsePoints (int cx, int cy, int x, int y, bool filled)
{
  if (filled)
  {
    line(cx + x, cy + y, cx - x, cy + y);
    line(cx - x, cy - y, cx + x, cy - y);
  }
  else
  {
    dot(cx + x, cy + y);
    dot(cx - x, cy + y);
    dot(cx - x, cy - y);
    dot(cx + x, cy - y);
  }
}

void ellipse (int cx, int cy, int xRadius, int yRadius, int filled)
{
  int x, y ;
  int xChange, yChange, ellipseError ;
  int twoAsquare, twoBsquare ;
  int stoppingX, stoppingY ;

  twoAsquare = 2 * xRadius * xRadius ;
  twoBsquare = 2 * yRadius * yRadius ;

  x = xRadius ;
  y = 0 ;

  xChange = yRadius * yRadius * (1 - 2 * xRadius) ;
  yChange = xRadius * xRadius ;

  ellipseError = 0 ;
  stoppingX    = twoBsquare * xRadius ;
  stoppingY    = 0 ;

  while (stoppingX >= stoppingY)  // 1st set of points
  {
    plot4ellipsePoints(cx, cy, x, y, filled) ;
    ++y ;
    stoppingY    += twoAsquare ;
    ellipseError += yChange ;
    yChange      += twoAsquare ;

    if ((2 * ellipseError + xChange) > 0 )
    {
      --x ;
      stoppingX    -= twoBsquare ;
      ellipseError += xChange ;
      xChange      += twoBsquare ;
    }
  }

  x = 0 ;
  y = yRadius ;

  xChange = yRadius * yRadius ;
  yChange = xRadius * xRadius * (1 - 2 * yRadius) ;

  ellipseError = 0 ;
  stoppingX    = 0 ;
  stoppingY    = twoAsquare * yRadius ;

  while (stoppingX <= stoppingY)  //2nd set of points
  {
    plot4ellipsePoints (cx, cy, x, y, filled) ;
    ++x ;
    stoppingX    += twoBsquare ;
    ellipseError += xChange ;
    xChange      += twoBsquare ;

    if ((2 * ellipseError + yChange) > 0 )
    {
      --y ;
      stoppingY -= twoAsquare ;
      ellipseError += yChange ;
      yChange += twoAsquare ;
    }
  }
}