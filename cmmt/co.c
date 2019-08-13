#include <stdio.h>
#include <stdlib.h>

int main (void) {
	int c;
	putchar('/'); putchar('*'); 
	while ((c = getchar()) != EOF) {
		putchar(c);
	}
	putchar('*'); putchar('/');

	return EXIT_SUCCESS;
}