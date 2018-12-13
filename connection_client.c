#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"

int                 init_connection_client(const char *address)
{
    SOCKET          sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN     sin;
    struct hostent  *hostinfo;

    if (sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    hostinfo = gethostbyname(address);
    if (hostinfo == NULL)
    {
        my_putstr("Unknown host ");
        my_putstr(address);
        my_putstr("\n");
        exit(EXIT_FAILURE);
    }
    sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    if (connect(sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }
    return sock;
}

void                end_connection(int sock)
{
    closesocket(sock);
}

int                 read_server(SOCKET sock, char *buffer)
{
    int n;

    n = 0;
    if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv() read_server");
        exit(errno);
    }
    buffer[n] = 0;
    my_putstr("read_server worked\n");
    return n;
}


void                read_server2(SOCKET sock, t_game *game)
{
    int n;

    n = 0;
    if ((n = recv(sock, game, sizeof(t_game), 0)) < 0)
    {
        perror("recv() read_server2");
        exit(errno);
    }
    my_putstr("read_server worked\n");
}

void                write_server(SOCKET sock, const char *buffer)
{
    if (send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
    my_putstr("write_server worked\n");
}

void                write_server2(SOCKET sock, t_client_request *request)
{
    
    if (send(sock, request, sizeof(t_client_request),0) < 0)
    {
        perror("send()");
        exit(errno);
    }    
    my_putstr("write_server2 worked\n");
}