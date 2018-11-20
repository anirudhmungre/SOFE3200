/*
    C socket server example updated
	it can now handle multiple clients using thread
*/

#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h>   //for threading

//the thread function
void *connection_handler(void *);

int main(int argc, char *argv[])
{
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *)new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int *)socket_desc;
    int read_size;
    char *answer, *message, client_message[2000];

    //Receive a message from client
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0)
    {
        // All of my questions
        if (strstr(client_message, "Do I code well?") != NULL)
        {
            strcpy(answer, "Yes, you are very good, but never comment.\n");
        }
        else if (strstr(client_message, "How good?") != NULL)
        {
            strcpy(answer, "Oh, it's pretty good.\n");
        }
        else if (strstr(client_message, "How many error?") != NULL)
        {
            strcpy(answer, "So many errors. WOW.\n");
        }
        else if (strstr(client_message, "Why?") != NULL)
        {
            strcpy(answer, "Just because. Next Question.\n");
        }
        else if (strstr(client_message, "Do you love me?") != NULL)
        {
            strcpy(answer, "You can never be loved.\n");
        }
        else
        {
            strcpy(answer, "Question not known, please try again.\n");
        }

        write(sock, answer, strlen(answer));
        memset(answer, 0, strlen(answer));
        memset(client_message, 0, strlen(client_message));
        // strcpy(client_message, "");
        // strcpy(answer, "");
    }

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}