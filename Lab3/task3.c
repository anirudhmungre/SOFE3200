#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

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


void main()
{
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

    char parentBuff[fileStat.st_size];
    char childBuff[fileStat.st_size];
    int fd[2], bytes, eFile;

    pipe(fd);

    if(fork()) {
    //Parent closes write
    close(fd[0]);
    bytes = read(file, parentBuff, sizeof(parentBuff));
    // Puts data in pipe
    write(fd[1], parentBuff, bytes);
    } else {
    // Child closes read
    close(fd[1]);

    read(fd[0], childBuff, sizeof(childBuff)); //reads from pipe
    close(fd[0]);

    replaceAll(childBuff, "Inferno", "Paradisio");
    replaceAll(childBuff, "In dark woods", "using Windows 8.1");
    replaceAll(childBuff, "those woods", "Windows 8.1");
    replaceAll(childBuff, "to enter", "to use 8.1");
    replaceAll(childBuff, "crest", "screen");
    replaceAll(childBuff, "Below a hill", "Before a monitor");
    replaceAll(childBuff, "shoulders", "GUI");
    replaceAll(childBuff, "planet", "UNIX");
    replaceAll(childBuff, "dante", "Shakespeare");

    printf("%s", childBuff);
    eFile = open("Dante.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    write(eFile, childBuff, strlen(childBuff)-1);
    }
}