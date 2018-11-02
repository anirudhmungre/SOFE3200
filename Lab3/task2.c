#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void replaceAll(char *stringToReplace, const char *wordToReplace, const char *replaceWith) {
    char t[1024], * p;
    int i = 0;
    while ((p = strstr(stringToReplace, wordToReplace)) != NULL) {
        strcpy(t, stringToReplace);
        i = p - stringToReplace;
        stringToReplace[i] = '\0';
        strcat(stringToReplace, replaceWith);
        strcat(stringToReplace, t + i + strlen(wordToReplace));
    }
}

int main() {
    int file = open("input.txt", O_RDONLY);
    if (file < 0) {
        perror("FileNotFound");
        exit(1);
    }

    struct stat fileStat;
    if (fstat(file, &fileStat) < 0) { 
        perror("FileNotFound");
        exit(1);
    }
    char fileData[fileStat.st_size + 5];

    int fileLength = read(file, fileData, sizeof(fileData));
    fileData[fileLength] = '\0';
    
    replaceAll(fileData, "Inferno", "Paradisio");
    replaceAll(fileData, "In dark woods", "using Windows 8.1");
    replaceAll(fileData, "those woods", "Windows 8.1");
    replaceAll(fileData, "to enter", "to use 8.1");
    replaceAll(fileData, "crest", "screen");
    replaceAll(fileData, "Below a hill", "Before a monitor");
    replaceAll(fileData, "shoulders", "GUI");
    replaceAll(fileData, "planet", "UNIX");
    replaceAll(fileData, "dante", "Shakespeare");

    write(open("Dante.txt", O_CREAT | O_WRONLY | O_TRUNC, 00600), fileData, sizeof(fileData));
}
