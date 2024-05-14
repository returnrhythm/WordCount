#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word

// Function to count characters and words in a file
void countCharactersAndWords(FILE *file, int *charCount, int *wordCount) {
    char c;
    int state = OUT;

    *charCount = 0;
    *wordCount = 0;

    while ((c = fgetc(file)) != EOF) {
        // Count characters
        (*charCount)++;

        // Check for word boundaries
        if (c == ' ' || c == '\n' || c == '\t' || c == ',') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            (*wordCount)++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] <filename>\n", argv[0]);
        return 1;
    }

    // Determine if we are counting characters or words
    int countChars = 0;
    if (strcmp(argv[1], "-c") == 0) {
        countChars = 1;
    } else if (strcmp(argv[1], "-w") != 0) {
        printf("Invalid option: %s. Use -c for characters or -w for words.\n", argv[1]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int charCount, wordCount;
    countCharactersAndWords(file, &charCount, &wordCount);

    if (countChars) {
        printf("×Ö·ûÊý£º%d\n", charCount);
    } else {
        printf("µ¥´ÊÊý£º%d\n", wordCount);
    }

    fclose(file);
    return 0;
}

