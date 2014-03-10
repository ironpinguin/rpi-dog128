#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "../src/dog128.h"

void usage()
{
  printf("Usage: dogl.sh [ -h ] [ -c command ] [ -d data ]\n");
}

int main(int argc, char **argv)
{
  char *command, *data;
  int  ch, with_command = 0, with_data = 0;
  char *buff = "Hallo";

  while ((ch = getopt(argc, argv, "hc:d:")) != -1) {
    switch (ch) {
      case 'h':
        usage();
        return 0;
        break;
      case 'c':
        command = optarg;
	with_command = 1;
        break;
      case 'd':
        data = optarg;
	with_data = 1;
        break;
      default:
        usage();
        exit(1);
	break;
    }
  }

  if (with_command == 1 && with_data == 0) {
    printf("ERROR Command need data\n");
    usage();
    exit(1);
  }

  initFonts();

  init(6, 1, 0);
  selectFont(FONT16x26_1);
  pwmWrite(LED, 250);
  clear();

  show();

  if (with_command == 0) {
    writeText(buff, 1, 1);
    buff = "Alex!";
    writeText(buff, 1, 27);
    //rect(10,10,100,40, false);
    //circle(50, 30, 15, false);
  } else {
    if (strncmp(strtolower(command), 'line', 7) == 0) { 
      
    }
  }

  show();

  return 0;
}
