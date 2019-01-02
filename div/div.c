#include <stdio.h>

#define MAX_LINE    512
#define CMT_STRT    "/*"
#define CMT_STOP    "*/"
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#define MIN(a,b)    ((a) < (b) ? (a) : (b))

// Global line buffer.
char b[MAX_LINE];

// Converts string to natural number. Returns -1 on error. 
int getNat (const char *s) {
    int n = 0;
    while (*s != '\0') {
        if (*s < '0' || *s > '9') return -1;
        n *= 10;
        n += *s - '0';
        s++;
    }
    return n; 
}

int main (int argc, const char *argv[]) {
    int a, i, j, n, offset, len = 80;

    // Verify parameters: Only optional line-length.
    if (argc == 2 && (len = getNat(argv[1])) == -1) {
        fprintf(stderr, "Usage: div [len]\n");
        return -1;
    }

    // Read in line [ambiguous EOF on getchar!].
    for (i = 0; i < MAX_LINE; i++) {
        b[i] = getchar();
        if (b[i] < ' ' || b[i] > '~') break;
    }

    // Compute offset: (len - (" * " + n + " *")) / 2
    n = i;
    offset = MAX(0, (len - 5 - n) / 2);
 
    // Compute adjustment.
    a = (len - 5 - n) % 2;

    // Write divider.
    printf("%s\n ", CMT_STRT);
    for (i = 0; i < len - 1; i++) putchar('*'); putchar('\n');
    printf(" * ");
    for (i = 0; i < offset; i++) putchar(' ');
    for (j = 0; i < (len - offset - 5); i++, j++) {
        if (b[j] < ' ' || b[j] > '~') {
            break;
        }
        putchar(b[j]);
    }
    for (i = 0; i < offset; i++) putchar(' ');
    printf("%s*\n ", a == 1 ? "  " : " ");
    for (i = 0; i < len - 1; i++) putchar('*');
    fprintf(stdout, "\n%s\n", CMT_STOP);

    return 0;
}