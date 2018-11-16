#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define READ  0
#define WRITE 1

int main(int argc, char const *argv[]) {
    char *eos = "eos";
    if (argc < 2) {
        perror("Need. More. Param-eaters.");
        exit(1);
    }
    char inputFilePath[20];
    char outputFilePath[20];
    strcpy(inputFilePath, argv[1]);
    strcpy(outputFilePath, argv[2]);

    int pipeItUp[2];
    int pipeItUp2[2];
    pipe(pipeItUp);
    pipe(pipeItUp2);

    printf("Data Pipe fd: %d, %d\n", pipeItUp[READ], pipeItUp[WRITE]);
    printf("Ack Pipe fd: %d, %d\n", pipeItUp2[READ], pipeItUp2[WRITE]);

    int pid = fork();

    if (pid > 0) {  
        /* parent process */
        int sum = 0; // Keep track of sum
        char streamBuffer[256]; // stream buffer same as line len
        int ack = 1; // val to send as ack
        // Close all un-needed pipe ends
        close(pipeItUp[WRITE]);
        close(pipeItUp2[READ]);
        while(1) {
            // Write ack to ack pipe
            write(pipeItUp2[WRITE],&ack,sizeof(ack));
            // read data from the data pipe, adding to sum
            // If the other end is closed, break loop
            if (read(pipeItUp[READ],&streamBuffer,sizeof(streamBuffer)) > 0) {
                sum += atoi(streamBuffer);
            } else {
                break;
            }
        }
        // Show sum on stdout
        printf("Sum: %d\n", sum);
        // Print sum to out file
        char outData[10];
        sprintf(outData, "Sum: %d", sum);
        write(open(outputFilePath, O_CREAT | O_WRONLY | O_TRUNC, 00600), outData, strlen(outData));
        // Close all pipes when done
        close(pipeItUp[READ]);
        close(pipeItUp2[WRITE]);
    } else { 
        /* child process */
        int childAck = 0; // Ack for data resp
        // Close all un-needed pipe ends
        close(pipeItUp[READ]);
        close(pipeItUp2[WRITE]);
        // Open the file
        FILE *inputFile = fopen(inputFilePath, "r");
        char line[256]; // Line buffer
        // While still lines in file
        while(fgets(line, sizeof(line), inputFile)) {
            // Read ack from pipe, if other end ends, break
            if (read(pipeItUp2[READ],&childAck,sizeof(childAck)) <= 0) {
                break;
            }
            // remove non-alphanumeric
            int i = 0, j = 0;
            char c;
            while ((c = line[i++]) != '\0') {
                if (isalnum(c)) { line[j++] = c; }
            }
            line[j] = '\0';
            // Write to the data pipe
            write(pipeItUp[1], &line, strlen(line));
        }
        // Close all pipes when done
        close(pipeItUp[WRITE]);
        close(pipeItUp2[READ]);
    }
    // Done
    return 0;
}
