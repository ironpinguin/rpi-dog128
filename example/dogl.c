#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../src/dog128.h"

int main()
{
  char *buff = "Hallo";

  initFonts();

  init(0, 1, 2, 0);
  selectFont(FONT16x26_1);
  pwmWrite(LED, 250);
  clear();

  show();
  
  writeText(buff, 1, 1); 
  buff = "Alex!";
  writeText(buff, 1, 27);
  //rect(10,10,100,40, false);
  //circle(50, 30, 15, false);

  show();

  return 0;
}
