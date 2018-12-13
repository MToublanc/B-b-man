#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "constants.h"
#include "game.h"
#include "bomb.h"
#include "character.h"
#include "map.h"
#include "socket.h"
#include "constants.h"



void game(SDL_Surface *screen, const char *name, int client_number)
{
    SDL_Event event;
    bool playing = true;
    int i = 0, j = 0;
    int **map = load_map();

    t_bomb_node *bomb_list = NULL;
    t_character_node *character_list = NULL; 

    t_game *game = malloc(sizeof(t_game));
    
    add_character_to_list(&character_list, 4, 1);

    SOCKET              sock = init_connection_client("127.0.0.1");
    char                buffer[BUF_SIZE];
    //void *              buffer2;
    int                 command_input = 0;

    fd_set              rdfs;
    my_putstr("client : Connection to the server...\n");
    printf("client : sock = %d\n", sock);
    write_server(sock, name);
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    FD_SET(sock, &rdfs);

    if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
    {
        perror("select()");
        exit(errno);
    }
    //my_putstr("client : Before the second IF\n");
    if (FD_ISSET(sock, &rdfs))
    {
        my_putstr("client : inside the second IF\n");
        read_server2(sock, game);
        printf("client : response gotten, pos_y = %d pos_x = %d\n", 
            game->player_infos[client_number].y_pos, game->player_infos[client_number].x_pos);
    }
    if (!map)
        exit(EXIT_FAILURE);

    while (playing)
    {
        
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(sock, &rdfs);
        /// add client handling of response sent


        //my_putstr("before the while\n");
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    playing = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            playing = 0;
                            break;
                        case SDLK_UP:
                            //moveCharacter(map, character_list->character, bomb_list, UP);
                            //my_putstr("client : Before up_request\n");
                            move_request(sock, client_number, UP);
                            //my_putstr("Before the first IF\n");
                            if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
                            {
                                perror("select()");
                                exit(errno);
                            }
                            //my_putstr("client : Before the second IF\n");
                            if (FD_ISSET(sock, &rdfs))
                            {
                                my_putstr("client : inside the second IF\n");
                                read_server2(sock, game);
                                printf("client : response gotten, pos_y = %d pos_x = %d\n", 
                                    game->player_infos[client_number].y_pos, game->player_infos[client_number].x_pos);
                            }
                            break;
                        case SDLK_DOWN:
                            //moveCharacter(map, character_list->character, bomb_list, DOWN);
                            move_request(sock, client_number, DOWN);
                            //my_putstr("Before the first IF\n");
                            if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
                            {
                                perror("select()");
                                exit(errno);
                            }
                            //my_putstr("client : Before the second IF\n");
                            if (FD_ISSET(sock, &rdfs))
                            {
                                my_putstr("client : inside the second IF\n");
                                read_server2(sock, game);
                                printf("client : response gotten, pos_y = %d pos_x = %d\n", 
                                    game->player_infos[client_number].y_pos, game->player_infos[client_number].x_pos);
                            }
                            break;
                        case SDLK_RIGHT:
                            //moveCharacter(map, character_list->character, bomb_list, RIGHT);
                            move_request(sock, client_number, RIGHT);
                            //my_putstr("Before the first IF\n");
                            if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
                            {
                                perror("select()");
                                exit(errno);
                            }
                            //my_putstr("client : Before the second IF\n");
                            if (FD_ISSET(sock, &rdfs))
                            {
                                my_putstr("client : inside the second IF\n");
                                read_server2(sock, game);
                                printf("client : response gotten, pos_y = %d pos_x = %d\n", 
                                    game->player_infos[client_number].y_pos, game->player_infos[client_number].x_pos);
                            }
                            break;
                        case SDLK_LEFT:
                            //moveCharacter(map, character_list->character, bomb_list, LEFT);
                            move_request(sock, client_number, LEFT);
                            //my_putstr("Before the first IF\n");
                            if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
                            {
                                perror("select()");
                                exit(errno);
                            }
                            //my_putstr("client : Before the second IF\n");
                            if (FD_ISSET(sock, &rdfs))
                            {
                                my_putstr("client : inside the second IF\n");
                                read_server2(sock, game);
                                printf("client : response gotten, pos_y = %d pos_x = %d\n", 
                                    game->player_infos[client_number].y_pos, game->player_infos[client_number].x_pos);
                            }
                            break;
                        case SDLK_SPACE:
                            //add_bomb_to_list(&bomb_list, character_list->character->x, character_list->character->y);
                            bomb_request(sock, client_number);
                            //my_putstr("Before the first IF\n");
                            if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
                            {
                                perror("select()");
                                exit(errno);
                            }
                            //my_putstr("client : Before the second IF\n");
                            if (FD_ISSET(sock, &rdfs))
                            {
                                my_putstr("client : inside the second IF\n");
                                read_server2(sock, game);
                                printf("client : response gotten, actual = %d\n", game->actual);
                            }
                            break;
                    }
                    break;
            }
        }
        /*read_server()*/
        draw_map(map, screen);
        draw_bombs_on_screen(screen, &bomb_list, map);
        if (character_list != NULL) {
            draw_characters_on_screen(screen, &character_list, map);
        } else {
            playing = false;
        } 
        SDL_Flip(screen);
    }
    SDL_Delay(500);
    free_map(map);
    end_connection(sock); /// end of connection
}
