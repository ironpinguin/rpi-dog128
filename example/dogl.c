#include <stdio.h>
#include <string.h>
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

  show();

  return 0;
}
