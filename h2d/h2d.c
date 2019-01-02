#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 *******************************************************************************
 *                             Symbolic Constants                              *
 *******************************************************************************
*/

// Returns nonzero if character is a hexadecimal symbol.
#define IS_HEX(c)       (((c) >= '0' && (c) <= 'f') ? xmap[(c)][0] : 0)

// Returns the base-10 representation of a hexadecimal symbol.
#define HEX_VAL(c)      xmap[(c)][1]

// Error message format for bad input.
#define ERR_BAD_CHAR    "Unrecognized symbol on input!"

/*
 *******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************
*/

// Hexadecimal Value Map [isHex][hexValue]
int xmap[104][2] = 
    {   
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {1,0x0}, {1,0x1}, {1,0x2}, {1,0x3}, {1,0x4}, {1,0x5}, {1,0x6}, {1,0x7},
        {1,0x8}, {1,0x9}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {1,0xa}, {1,0xb}, {1,0xc}, {1,0xd}, {1,0xe}, {1,0xf}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0}, {0,0x0},
        {0,0x0}, {1,0xa}, {1,0xb}, {1,0xc}, {1,0xd}, {1,0xe}, {1,0xf}, {0,0x0}
    };

/*
 *******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************
*/

// Exits with error message. Displays given character if pointer non-null.
void panic (int *p, const char *msg) {
    fprintf(stderr, "Error: %s", msg);
    if (p != NULL) fprintf(stderr, " | Last Symbol: %d:'%c'\n", *p, *p);
    fprintf(stderr, "\n");
}

int main (void) {
	unsigned long long n = 0;
	int c = getchar();

    // Accept Optional Prefix.
    if (IS_HEX(c) && c == '0') {
        c = getchar();
        if (!IS_HEX(c) && c == 'x') {
            c = getchar();
        }
        if (!IS_HEX(c)) panic(&c, ERR_BAD_CHAR);
    }

    // Discard any following zeros.
    while (c == '0') c = getchar();

	// Construct number.
	while (c != EOF && c != '\n') {
		if (!IS_HEX(c)) panic(&c, ERR_BAD_CHAR);
		n <<= 4;
		n += HEX_VAL(c);
        c = getchar();
	}
	
	printf("%llu", n);

	return 0;
}
