#include "pathfinder.h"

static void printLineNumberError(int lineNumber) {
    lineNumber++;
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(lineNumber));
    mx_printerr(" is not valid\n");
    exit(0);
}

static void checkEmptyLines(char **lines, char *fileContent) {
    char *filePtr = fileContent;
    char **linePtr = lines;
    int index = 0;
    int length = 0;

    if (*filePtr == '\n')
        printLineNumberError(0);
    while (*filePtr) {
        if (*filePtr == '\n' && *(filePtr + 1) == '\n')
            while (linePtr[index]) {
                length = mx_strlen(linePtr[index]);
                if (mx_strncmp(filePtr - length, linePtr[index], mx_strlen(linePtr[index])) == 0)
                    printLineNumberError(index + 1);
                index++;
            }
        filePtr++;
    }
}

static void validateLine(char **lines, int lineNumber) {
    int i = 0;
    int copy_i = 0;

    for (int n = 1; n <= lineNumber; n++) {
        i = 0;
        copy_i = 0;

        while (mx_isalpha(lines[n][i]))
            i++;
        if (i == 0 || lines[n][i] != '-')
            printLineNumberError(n);
        i++;

        copy_i = i;
        while (mx_isalpha(lines[n][copy_i]))
            copy_i++;
        if (copy_i - i == 0 || lines[n][copy_i] != ',')
            printLineNumberError(n);
        copy_i++;
        i = copy_i;

        while (mx_isdigit(lines[n][copy_i]))
            copy_i++;
        if (copy_i - i == 0 || lines[n][copy_i] != '\0')
            printLineNumberError(n);
    }
}

static void parseFile(char *fileContent) {
    char **lines = mx_strsplit(fileContent, '\n');
    int lineNumber = 0;
    int index = 0;

    while (lines[lineNumber])
        lineNumber++;

    if (lines[0][0] == '0') {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    while (lines[0][index]) {
        if (!mx_isdigit(lines[0][index])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
        index++;
    }

    validateLine(lines, lineNumber - 1);
    checkEmptyLines(lines, fileContent);
    mx_del_strarr(&lines);
}

void handleErrors(int argc, char *fileContent, char **argv) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    if (!fileContent) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
    }
    if (mx_strlen(fileContent) == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }
    parseFile(fileContent);
}
