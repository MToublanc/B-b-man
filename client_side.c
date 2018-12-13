#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"
#include "constants.h"


move_request(SOCKET sock, int player_number, int move)
{
	t_client_request *request = malloc(sizeof(t_client_request));
	request->dir = move;
	request->move =  true;
	request->place_bomb = false;
	request->player_number = player_number;
	write_server2(sock, request);
	free(request);
}

bomb_request(SOCKET sock, int player_number)
{
	t_client_request *request = malloc(sizeof(t_client_request));
	request->move =  false;
	request->place_bomb = true;
	request->player_number = player_number;
	write_server2(sock, request);
	free(request);
}


