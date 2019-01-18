#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

/*
 * Description: Attempts to count the number of arithmetic, multiplication, and
 * conditional operators for an assembly program. In no ways accounts for all of
 * the Intel X86 syntax, but only a simple and smaller subset.
 *
 * Note: This is designed to be used with code snippets passed via stdin using
 * the following format:
 *					<whitespace> <instruction> <text> <newline>
 * The program ignores leading whitespace, grabs the instruction (first word), 
 * and discards the rest until the newline.
*/


/*
 *******************************************************************************
 *                             Symbolic Constants                              *
 *******************************************************************************
*/

// Mnemonic indexes for counts.
#define ALU				0
#define MPY				1
#define CND				2

// Largest word stored.
#define MAX_INST_LEN	8


/*
 *******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************
*/

// All tracked conditional instructions.
const char *inst_cnd[] = {"jo","jno","js","jns","je","jz","jne","jnz","jb",
	"jbna","jc","jnb","jae","jnc","jbe","jna","ja","jnbe","jl","jnge",
	"jge","jnl","jle","jng","jg","jnle","jp","jpe", "jnp", "jpo", "jcxz",
	 "jecxz", NULL};

// All tracked ALU instructions (all arithmetic/bit operations).
const char *inst_alu[] = {"ror", "rol", "shl", "sal", "shr", "sar", "not", 
	"and", "or", "xor", "neg", "sub", "add", "idiv", "cmp", "test", 
	"pslld", "psllq", "psllw", "psrad", "psraw", "psrld", "psrlq", 
	"psrlw", "paddq", "paddd", "paddw", NULL};

// All tracked multiplication instructions.
const char *inst_mpy[] = {"imul","pmuludq", NULL};


/*
 *******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************
*/


// Returns 1 if given string 'w' contained in string array 'ls'.
int in (const char *w, const char **ls) {
	const char **p;
    for (p = ls; *p != NULL && strncmp(w,*p,MAX_INST_LEN) != 0; p++);
    return (*p != NULL);
}

// Fetches the first word on a line, then discards the rest of the line.
const char *getinst () {
    static char word[MAX_INST_LEN + 1];
    unsigned int c, r = 0;

    // Skip leading whitespace.
    while (isspace((c = getchar())));

    // Return if reached end.
    if (c == EOF) return NULL;

    // Otherwise read the word in.
    do {
        word[r++] = tolower(c);
    } while (isalpha((c = getchar())) && r < MAX_INST_LEN);

    // Set null char.
    word[r] = '\0';

    // Drop until EOF or next line begins.
    while (c != EOF && c != '\n') c = getchar();

    return word;
}

int main (void) {
    int count[3] = {0};
    const char *w;

    while ((w = getinst()) != NULL) {
        count[ALU] += in(w, inst_alu);
        count[MPY] += in(w, inst_mpy);
        count[CND] += in(w, inst_cnd);
    }
    printf("Alu: %d\nMpy: %d\nCnd: %d\n", count[ALU], count[MPY], count[CND]);
    return EXIT_SUCCESS;
}
