#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAXBUF			256
#define MIN(a,b) 		((a) < (b) ? (a) : (b))
#define MAXLINE 		80
#define PADDING 		5	// (space)+*+(space)+<content>+(space)+*
#define USAGE 			"usage: %s <org> <desc> <author> [<author>]*"
#define	TRUE			1
#define FALSE			0


/* Ban(ner)
 * Prints a banner with metadata for source files
 * Arguments:
 *	1. Organization name
 *	2. Description
 *  3. First authors name
 * 
 * Simply list more authors to add them after the first-author as arguments
*/


// Writes a line of asterisks to form an upper or lower line/divider
void putdiv (size_t len) {
	putchar(' ');
	for (int i = 0; i < (len - 1); ++i) putchar('*');
	putchar('\n');
}

// Writes an empty line, beginning with a space offset and with asterisk ends
void putempty (size_t len) {
	putchar(' '); putchar('*');
	for (int i = 0; i < (len - 3); ++i) putchar(' ');
	putchar('*');
	putchar('\n');
}

// Writes given line with asterisk padding and offset; optional text centering
void putline (const char *line, int isCentered) {
	size_t len = MAXLINE - PADDING;
	size_t line_len = strlen(line);

	// Actual length is whatever fits within the length
	size_t actual_len = MIN(len, line_len);

	// Offset is only needed if you wish to center
	size_t offset = 0, rem = len - actual_len;
	if (isCentered != 0) {
		offset = rem = (len - actual_len) / 2;
		offset += (len - actual_len) % 2;
	}

	// Output the line
	printf(" * ");
	for (int i = 0; i < offset; ++i) putchar(' ');
	printf("%s", line);
	for (int i = 0; i < rem; ++i) putchar(' ');
	printf(" *\n");
}


int main (int argc, const char *argv[]) {
	char buffer[MAXBUF] = {0};
	const char *p;

	// Validate input
	if (argc < 4) {
		fprintf(stderr, USAGE "\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Get current time
	time_t t = time(NULL);
	struct tm *t_ptr = localtime(&t);

	// Set prefix for organization
	sprintf(buffer, "(C) Copyright %.2d %s", t_ptr->tm_year + 1900, argv[1]);

	// Display start of format along with organization
	printf("/*\n");
	putdiv(MAXLINE);
	putline(buffer, TRUE);

	// Set current date
	sprintf(buffer, "Created: %.2d/%.2d/%.4d", t_ptr->tm_mday, 
		t_ptr->tm_mon + 1, t_ptr->tm_year + 1900);
	putline(buffer, FALSE);

	// Display authors
	putempty(MAXLINE);
	putline("Programmer(s):", FALSE);

	for (int i = 3; i < argc; ++i) {
		snprintf(buffer, MAXBUF, "- %s", argv[i]);
		putline(buffer, FALSE);
	}

	// Display description
	putempty(MAXLINE);
	putline("Description:", FALSE);
	ssize_t d_size = strlen(argv[2]) * sizeof(char);
	ssize_t l_size = (MAXLINE - PADDING - 1);
	int n = (d_size / l_size) + ((d_size % l_size) != 0);
	buffer[0] = ' ';
	for (int i = 0; i < n; ++i) {
		ssize_t z = MIN(d_size, l_size);
		memcpy(buffer + 1, argv[2] + i * l_size, z);
		buffer[z+1] = '\0';
		putline(buffer, FALSE);
		d_size -= l_size;
	}

	putempty(MAXLINE);
	putdiv(MAXLINE);
	printf("*/\n");

	return EXIT_SUCCESS;
}