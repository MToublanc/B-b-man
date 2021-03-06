#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"

int             test_name_availability(Client *clients, SOCKET sock, const char *name, int actual)
{
    int         i;
    for (i = 0; i < actual; i++)
    {
        if (strcmp(clients[i].name, name) == 0)
        {
            write_client(sock, "This username is already used");
            shutdown(sock, SHUT_RDWR);
            remove_client(clients, i, &actual);
            return 0;
        }
    }
    return 1;
}

void            clear_clients(Client *clients, int actual)
{
    int         i;
    for (i = 0; i < actual; i++)
    {
        closesocket(clients[i].sock);
    }
}

void            remove_client(Client *clients, int to_remove, int *actual)
{
    memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
    (*actual)--;
}

void            send_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server)
{
    int         i;
    char        message[BUF_SIZE];

    message[0] = 0;
    for (i = 0; i < actual; i++)
    {
        if (sender.sock != clients[i].sock)
        {
            if (from_server == 0)
            {
                my_strncpy(message, sender.name, BUF_SIZE - 1);
                my_strncat(message, " : ", sizeof message - strlen(message) - 1);
            }
            my_strncat(message, buffer, sizeof message - strlen(message) - 1);
            write_client(clients[i].sock, message);
        }
        if (sender.sock == clients[i].sock)
        {
            my_strncpy(message, "You sent", BUF_SIZE - 1);
            my_strncat(message, " : ", sizeof message - strlen(message) - 1);
            my_strncat(message, buffer, sizeof message - strlen(message) - 1);
            write_client(clients[i].sock, message);
        }

    }
}

/*
void            send_message_to_all_clients2(Client *clients, int actual, t_client_request *request)
{
    int         i;
    t_game      *game;
    
    // we'll analyse the request here, update the response, then send it in the loop 

    game = init_game();
    for (i = 0; i < actual; i++)
    {
        write_client2(clients[i].sock, game);
    }
} */

int             init_connection(int maxClients)
{
    SOCKET      sock;
    SOCKADDR_IN sin;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    if (bind(sock, (SOCKADDR *)&sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }
    if (listen(sock, maxClients) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }
    return sock;
}
/*
void            end_connection(int sock)
{
    closesocket(sock);
}*/

int             read_client(SOCKET sock, char *buffer)
{
    int n = 0;
    my_putstr("read_client activated\n");
    if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv() read_client");
        n = 0;
    }
    buffer[n] = 0;

    return n;
}

int             read_client2(SOCKET sock, void *buffer2)
{
    int n = 0;
    my_putstr("read_client2 activated\n");
    if ((n = recv(sock, buffer2, sizeof(t_game), 0)) < 0)
    {
        perror("recv() read_client2");
        n = 0;
    }
    //buffer[n] = 0;
    return 10;
}

void            write_client(SOCKET sock, const char *buffer)
{
    my_putstr("write_client activated\n");
    if (send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
    
}


void            write_client2(SOCKET sock, t_game *response)
{
    my_putstr("write_client2 activated\n");
    if (send(sock, response, sizeof(t_game), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
    

}
int             isNumber(char *str)
{
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int             getMaxClient(int argc, char **argv)
{
    int         maxClients;

    maxClients = 0;
    if (argc > 1)
    {
        maxClients = my_getnbr(argv[1]);
        if (maxClients < 2 || maxClients > 100)
        {
            my_putstr("Please enter a number between 2 and 100\n");
            exit(EXIT_FAILURE);
        }
    }
    my_putstr("Maximum clients : ");
    my_putstr(argv[1]);
    return maxClients;
}


