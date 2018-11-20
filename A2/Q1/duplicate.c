#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *in, *out;
    char *buffer;
    long numbytes;
    char line[256];
    int pid;

    //Error check for correct number of args
    if (argc > 3)
    {
        printf("duplicate: Too many args!\nusage: duplicate <sourcefile> <targetfile>\n");
        return 0;
    }
    else if (argc < 3)
    {
        printf("duplicate: Not enough args!\nusage: duplicate <sourcefile> <targetfile>\n");
        return 0;
    }

    // Open file to read
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        perror("duplicate: File Error");
        exit(1);
    }
    // Open an output file
    out = fopen(argv[2], "w");
    if (out == NULL){
        perror("duplicate: Write Error");
        exit(1);
    }

    if ((pid = fork()) < 0)
    { // CHeck that fork works
        perror("duplicate: Error forking");
        kill(pid, SIGQUIT);
        exit(1);
    }
    else if (pid == 0)
    { // Parent
        while (1)
        {
            sleep(1); // Waits every second to print
            printf("duplicate: still duplicating...\n");
        }
        return 0;
    }
    else
    { // Child

        // Find bytes in file
        fseek(in, 0L, SEEK_END);
        numbytes = ftell(in);
        // Reset file posistion to beginning of file
        fseek(in, 0L, SEEK_SET);
        // Create buffer
        buffer = (char *)calloc(numbytes, sizeof(char));
        // Copy text into a buffer
        fread(buffer, sizeof(char), numbytes, in);
        fclose(in);

        // Print to the output file
        fprintf(out, "%s", buffer);
        fclose(out);
        kill(pid, SIGQUIT);                                                      // Send signal to kill parent once done
        printf("duplicate: Copied %ld bytes from %s to %s.\n", numbytes, argv[1], argv[2]); // Output requested
        return 0;                                                                //End program
    }
    return 0;
}