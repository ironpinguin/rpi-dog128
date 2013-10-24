#include "stdio.h"
#include "stdlib.h"
#include "dog128.h"


void helpText() {
	printf("Existing Commands: \n");
	printf("  line startx starty endx endy \n");
//	printf("Existing Commands: \n");
//	printf("Existing Commands: \n");
//	printf("Existing Commands: \n");
//	printf("Existing Commands: \n");
	printf("\n");
}

int main(int argc, char** argv) {
	int i;
	char *command;

    printf("argc = %d\n", argc);

    for (i = 0; i < argc; i++) {
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	}

	if (argc > 2) {
		init(DI, LED, RESET, 0);
		initFonts();
		command = argv[1];
		if (strcmp(command, "line") == 0) {
			if (argc != 6) {
				printf ("wrong argc: %d\n", argc);
				helpText();
				return 1;
			}
			line(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5])); 
		} else {
			helpText();
			return 1;
		}
		show();
	} else {
		helpText();
		return 1;
	}

	return 0;
} 