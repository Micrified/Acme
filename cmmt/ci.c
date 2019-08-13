#include <stdio.h>
#include <stdlib.h>

int main (void) {
	int cs[3] = {0};
	
	// drop first two: {/,*}
	getchar(); getchar();

	// get next three (must be at least {*,/} then EOF)
	cs[0] = getchar();
	cs[1] = getchar();
	cs[2] = getchar();

	while (cs[2] != EOF) {
		putchar(cs[0]);
		cs[0] = cs[1];
		cs[1] = cs[2];
		cs[2] = getchar();
	}

	return EXIT_SUCCESS;
}