#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>


/*
 *******************************************************************************
 *                             Symbolic Constants                              *
 *******************************************************************************
*/

// Panic macro.
#define PANIC(msg)         ((msg) ? (void)0 : \
    (fprintf(stderr, "Error: (%s:%d): %s\n", __FILE__, __LINE__, #msg)))

// Maximum length for a file name.
#define MAX_FILENAME    255

// Maximum length for a file path.
#define MAX_PATHNAME    4096

// Maximum file-buffer size.
#define MAX_FILEBUFF    256


/*
 *******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************
*/


// The maximum line length allowed per file. 
int g_maxcol;

// All permitted extensions
const char *g_extensions[] = {
    ".c",
    ".h",
    ".go",
    ".hs",
    ".swift",
    NULL
};


/*
 *******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************
*/


// Returns the extension on a file, or NULL if it has none. Includes .
static const char *ext (const char *pathname) {
    size_t len = strlen(pathname);
    int i, c;
    for (i = 1; i <= len; i++) {
        if ((c = pathname[len - i]) == '.' || c == '/') {
            break;
        }
    }
    return (c == '.') ? (pathname + (len - i)) : NULL;
}

// Checks if string is in NULL-terminated list of strings.
static int contains (const char *s, const char **ss) {
    if (s == NULL) return 0;
    while (*ss != NULL && strcmp(*ss, s)) {
        ss++;
    }
    return (*ss != NULL);
}

// Prints line numbers for all lines in the given file over g_maxline.
static void lint (const char *pathname) {
    int i, row = 0, col = 0, fd;
    char buf[MAX_FILEBUFF];
    ssize_t bytes;

    // Ignore bad paths or those with wrong extensions.
    if (pathname == NULL || !contains(ext(pathname), g_extensions)) {
        return;
    }

    // Open the file.
    if ((fd = open(pathname, O_RDONLY)) == -1) {
        PANIC(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Check the file.
    do {
        bytes = read(fd, buf, MAX_FILEBUFF);
        for (i = 0; i < bytes; i++) {
            if (buf[i] == '\n') {
                if (col > g_maxcol) printf("%s:%d:%d\n", pathname, row, col);
                row++;
                col = 0;
                continue;
            }
            col += (buf[i] == '\t') ? 4 : 1;     
        }
    } while (bytes > 0);


    // Check for read-error.
    if (bytes == -1) {
        PANIC(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Close the file.
    close(fd);
}

// Walks a directory. Applies f to each file.
static void walk (const char *pathname, void (*f)(const char *)) {
    DIR *directory;
    struct dirent *entry;
    char nextpath[MAX_PATHNAME], *name;

    // Open directory stream. Stage at first entry.
    if ((directory = opendir(pathname)) == NULL) {
        PANIC(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // While new entries exist, parse them.
    while ((entry = readdir(directory)) != NULL) {
        name = entry->d_name;
        if (strcmp(name, "..") == 0 || strcmp(name, ".") == 0) {
            continue;
        }

        // Construct new path.
        if (strlen(pathname) + strlen(name) + 1 >= MAX_PATHNAME) {
            fprintf(stderr, "Error: Path \"%s/%s\" is too long!\n", 
                pathname, name);
            continue;
        } else {
            snprintf(nextpath, MAX_PATHNAME, "%s/%s", pathname, name);
            f(nextpath);
        }
    }

    // Close directory stream.
    if (closedir(directory) == -1) {
        PANIC(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Either lints a file, or walks a directory.
static void peek (const char *pathname) {
    struct stat statbuf;

    if (stat(pathname, &statbuf) == -1) {
        PANIC(strerror(errno));
        exit(EXIT_FAILURE);
    }

    if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
        walk(pathname, peek);
    } else {
        lint(pathname);
    }
}

int main (int argc, const char *argv[]) {

    if (argc < 3 || sscanf(argv[1], "%d", &g_maxcol) != 1) {
        fprintf(stderr, "usage: %s <maxline> [<file>]+\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parse files.
    for (int i = 2; i < argc; i++) {
        peek(argv[i]);
    }

    return 0;
}