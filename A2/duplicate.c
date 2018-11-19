#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    FILE    *in, *out;
    char    *buffer;
    long    numbytes;

    // Open file to read 
    in = fopen(argv[1], "r");
    if(in == NULL){
        perror("File Not Found");
        return 1;
    }
    // Find bytes in file
    fseek(in, 0L, SEEK_END);
    numbytes = ftell(in);
    // Reset file posistion to beginning of file
    fseek(in, 0L, SEEK_SET);	
    // Create buffer
    buffer = (char*)calloc(numbytes, sizeof(char));	
    // Copy text into a buffer
    fread(buffer, sizeof(char), numbytes, in);
    fclose(in);
    printf("%s", buffer);

    printf("%d", argc);
    // out = fopen(argv[2], "w");
    // fprintf(out, buffer);
}