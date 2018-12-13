#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "socket.h"
#include "constants.h"

static bool in_game = true;






void        server_app()
{
    SOCKET  sock = init_connection(MAX_PLAYERS);
    char    buffer[BUF_SIZE];
    void    *buffer2;
    int     actual = 0;
    int     max = sock;
    Client  clients[MAX_PLAYERS];
    fd_set  rdfs;
    t_game  *game_state = init_game(); // variable qui contient toutes les informations du jeu à transfer
    my_putstr("\nServeur run...\n");
    int     game_over = 0;

    while (!game_over)
    {
        int i;
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(sock, &rdfs);
        for (i = 0; i < actual; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }
        if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }
        if (FD_ISSET(STDIN_FILENO, &rdfs))
        {
            break;
        }
        else if (FD_ISSET(sock, &rdfs))
        {
            SOCKADDR_IN csin;
            unsigned int sinsize = sizeof csin;
            int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
            int test = 0;
            if (csock == SOCKET_ERROR)
            {
                perror("accept()");
                continue;
            }
            if (read_client(csock, buffer) == -1)
            {
                continue;
            }
            max = csock > max ? csock : max;
            FD_SET(csock, &rdfs);
            Client c = {csock, ""};
            my_strncpy(c.name, buffer, BUF_SIZE - 1);
            //test = test_name_availability(clients, c.sock, c.name, actual);
            clients[actual] = c;
            game_state->player_infos[actual].connected = true;
            actual++;
            game_state->actual = actual;
            my_putstr("\nSomeone connected to the server\n");
            send_response_to_all(clients, game_state);
            if( actual > 1 ) in_game = true;
        }
        else
        {
            int i = 0;
            for (i = 0; i < actual; i++)
            {
                if (FD_ISSET(clients[i].sock, &rdfs))
                {
                    Client client = clients[i];
                    buffer2 = malloc(sizeof(t_client_request));
                    int c = read_client2(clients[i].sock, buffer2); //reads what's in the socket and put into the void* buffer2 
                    if(in_game)
                    {
                        //send_message_to_all_clients(clients, client, actual, buffer, 0);
                        t_client_request *request = (t_client_request *)buffer2; // turn void* into  t_client_request*
                        handle_request(request, game_state);
                        send_response_to_all(clients, game_state);
                        //t_game *request = (t_game *)buffer2;
                        //printf("map tile 1 = %c\n", request->map[0] ); // print int from the request
                        //game_over = check_game_over(game_state);
                    }                    
                    free(buffer2);
                    break;
                }
            }
        }
    }
    free(game_state);
    clear_clients(clients, actual);
    end_connection(sock);
}


t_game *init_game()
{
    t_game *game = malloc(sizeof(t_game));
    int     i,j;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        game->player_infos[i].connected = false;
        game->player_infos[i].alive = true;
        game->player_infos[i].current_dir = FACING_DOWN;
        //game->player_infos[i].current_speed = 0;
        //game->player_infos[i].max_speed = 3;
        game->player_infos[i].bombs_left = 10;
        game->player_infos[i].bombs_capacity = 10;
        game->player_infos[i].frags = 0;
    }
    game->player_infos[0].x_pos = 1;
    game->player_infos[0].y_pos = 1;
    game->player_infos[1].x_pos = 12;
    game->player_infos[1].y_pos = 1;
    game->player_infos[2].x_pos = 12;
    game->player_infos[2].y_pos = 12;
    game->player_infos[3].x_pos = 1;
    game->player_infos[3].y_pos = 12;

    for(i = 0; i < MAX_BOMBS; i++)
    {
        game->bombs[i].placed = false;
        game->bombs[i].x_pos = 0;
        game->bombs[i].y_pos = 0;
        game->bombs[i].timer = 0;
    }
    
    printf("before the loop for map\n");
    for(i = 0; i < 13 ; i++)
    {
        for (j = 0; j < 13; j++)
        {
            //printf("[i][j] = [%d][%d] = ", i,j);
            game->map[i][j] = 1;
            //printf("%d\n", game->map[i][j]);

        }
    }
    //printf("outside the loops %d\n", game->map[5][5]);

    return game;
}

void handle_request(t_client_request *request, t_game* game_state)
{
    //game_state->player_infos[request->player_number].x_pos = request->x_pos;
    //game_state->player_infos[request->player_number].y_pos = request->y_pos;
    printf("Server :inside handle_request \n");
    if(request->move)
    {
        printf("Server : inside request move \n");
        int y = game_state->player_infos[request->player_number].y_pos;
        int x = game_state->player_infos[request->player_number].x_pos;
        switch(request->dir)
        {
            case UP:
                game_state->player_infos[request->player_number].current_dir = UP;
                printf("Server : inside case up \n");
                if ((y - 1 < 0) || (game_state->map[y - 1][x] != EMPTY))
                    break;
                else if (is_bomb_at_position_2(game_state->bombs, x, y - 1))
                    break;
                game_state->player_infos[request->player_number].y_pos--;
                printf("Server : pos_y = %d\n", game_state->player_infos[request->player_number].y_pos);
                //character->y--;
                //character->screen_position.y = character->y * BLOCK_SIZE - BLOCK_SIZE;
                break;

            case DOWN:
                printf("Server : inside case down \n");
                game_state->player_infos[request->player_number].current_dir = DOWN;
                if ((y + 1 >= NB_BLOCK_HEIGHT) || (game_state->map[y + 1][x] != EMPTY))
                    break;
                else if (is_bomb_at_position_2(game_state->bombs, x, y + 1))
                    break;
                game_state->player_infos[request->player_number].y_pos++;
                printf("Server : pos_y = %d\n", game_state->player_infos[request->player_number].y_pos);
                //character->screen_position.y = character->y * BLOCK_SIZE - BLOCK_SIZE;
                break;

            case LEFT:
                game_state->player_infos[request->player_number].current_dir = LEFT;
                if ((x - 1 < 0) || (game_state->map[y][x - 1] != EMPTY))
                    break;
                else if (is_bomb_at_position_2(game_state->bombs, x - 1, y))
                    break;
                game_state->player_infos[request->player_number].x_pos--;
                //character->screen_position.x = character->x * BLOCK_SIZE;
                break;

            case RIGHT:
                game_state->player_infos[request->player_number].current_dir = RIGHT;
                if ((x + 1 >= NB_BLOCK_WIDTH) || (game_state->map[y][x + 1] != EMPTY))
                    break;
                else if (is_bomb_at_position_2(game_state->bombs, x + 1, y))
                    break;
                game_state->player_infos[request->player_number].x_pos++;
                //character->screen_position.x = character->x * BLOCK_SIZE;
                break;
        }
    }
    if(request->place_bomb)
    {
        place_bomb(game_state->bombs, 
            game_state->player_infos[request->player_number].x_pos, 
            game_state->player_infos[request->player_number].y_pos );
    }
}


int is_bomb_at_position_2(t_my_bomb bombs[MAX_BOMBS], int x, int y)
{
    int i;
    for(i = 0; i < MAX_BOMBS; i++)
    {
        if(bombs[i].placed && bombs[i].x_pos == x && bombs[i].y_pos == y)
        {
            return 1;
        }
    }
    return 0;
}

int place_bomb(t_game *game, int x, int y)
{
    int i;
    for(i = 0; i < MAX_BOMBS; i++)
    {
        if(game->bombs[i].placed == false)
        {
            game->bombs[i].placed = true;
            game->bombs[i].x_pos = x;
            game->bombs[i].y_pos = y;
            return 1;
        }
    }
    return 0;
}

void send_response_to_all(Client *clients, t_game *game)
{
    int i;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(game->player_infos[i].connected)
        {
            write_client2(clients[i].sock, game);
            my_putstr("\n response sent\n");
        }
    }
}

int check_game_over(t_game *game)
{
    int i,alive = 0;
    for(i = 0; i < MAX_PLAYERS; i++ )
    {
        if(game->player_infos[i].connected) 
            {
                if(game->player_infos[i].alive) alive++;
            }
        
    }
    if(alive < 2 ) return 1;
    return 0;
}


