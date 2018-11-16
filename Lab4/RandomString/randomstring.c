#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    // Seed the randomness
    srand(time(NULL));

    // Create arrays for adjectives and nouns
    char adjectives[3][10];
    char nouns[3][15];

    // Load words into arrays
    strcpy(adjectives[0], "puffy");
    strcpy(adjectives[1], "sad");
    strcpy(adjectives[2], "moist");
    strcpy(nouns[0], "tank");
    strcpy(nouns[1], "cat");
    strcpy(nouns[2], "rabbit");

    // Create a string for the final random string
    char rsbuff[100];

    // concat all the things
    strcpy(rsbuff, "the ");
    strcat(rsbuff, adjectives[rand()%3]);
    strcat(rsbuff, " ");
    strcat(rsbuff, adjectives[rand()%3]);
    strcat(rsbuff, " ");
    strcat(rsbuff, nouns[rand()%3]);
    strcat(rsbuff, " jumped over the ");
    strcat(rsbuff, adjectives[rand()%3]);
    strcat(rsbuff, " ");
    strcat(rsbuff, nouns[rand()%3]);
    strcat(rsbuff, "\n");
    
    // write that sentence to the screen
    write(1, rsbuff, strlen(rsbuff));
    return 0;
}

// EOF