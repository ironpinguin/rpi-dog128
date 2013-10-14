#include <stdio.h>
#include <string.h>
#include "../src/dog128.h"

int main()
{
  char *buff = "Hallo";

  initFonts();

  init();
  selectFont(FONT16x26_1);
  pwmWrite(LED, 250);
  clear();

  show();
  
  writeText(buff, 1, 1); 
  buff = "Alex!";
  writeText(buff, 1, 27);

  show();

  return 0;
}
