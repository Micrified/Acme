#include <stdio.h>
#include <stdlib.h>

/* Program which prints which flags are set in the x86-64 eflags register */

// Placeholder.
#define UNSET	"Reserved"

// Maximum defined number of flags (rest unused).
#define MAX_DEFINED_FLAGS	22

// Flag descriptions.
const char *flags[MAX_DEFINED_FLAGS] = 
{
	"Carry",		// Carry Flag
	UNSET, 			// -
	"Parity",		// Parity Flag (T if $set bigs in LSB multiple of 2)
	UNSET,			// -
	"Adjust",		// Adjust Flag (set in add if carry in low 4 bits to high 4 bits, or borrow from high to low in sub).
	UNSET, 			// - 
	"Zero",			// Zero flag.
	"Sign",			// Sign flag.
	"Trap",			// Trap flag (permits operation of processor in single-step mode).
	"Interrupt",	// Interrupt enable flag.
	"Direction",
	"Overflow",
	"I/O Prililege",
	"I/O Privilege",
	"Nested Task",
	UNSET,
	"Resume",
	"Virtual 8086 mode",
	"Alignment check",
	"Virtual Interrupt Flag",
	"Virtual Interrupt Pending",
	"Able to use CPUID instruction"
};


// Reads a binary string from standard input. Returns integer form (unnecessary but eh).
int readEFlags (void) {
	unsigned int c, d = 0;
	while ((c = getchar()) == '0' || c == '1')
		d = (d << 1) + (c - '0');
	if (c != EOF && c != '\n') {
		fprintf(stderr, "Error: Unknown symbol ('%c'| # %d)!\n", c, c);
		exit(EXIT_FAILURE);
	}
	return d;
}

// Processes binary string on stdin, and displays set flags on stdout. 
int main (int argc, const char *argv[]) {
	int eflags = readEFlags();
	for (int i = 0; i < MAX_DEFINED_FLAGS; ++i) {
		if (eflags % 2) {
			fprintf(stdout, "%02d: %s flag is set.\n", i, flags[i]);
		}
		eflags /= 2;
	}
	return EXIT_SUCCESS;
}
