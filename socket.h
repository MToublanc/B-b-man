#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <stdbool.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF		"\r\n"
#define PORT	 	2000
#define BUF_SIZE	512

#define MAP_SIZE 9  /// Défini le nombre de case dans le map.
#define MAX_PLAYERS 4
#define MAX_BOMBS 12

#define FACING_UP 0
#define FACING_RIGHT 1
#define FACING_DOWN 2
#define FACING_LEFT 3

typedef struct
{
    SOCKET  sock;
    char    name[BUF_SIZE];
}           Client;

typedef struct  s_client_request
{
  int           player_number;           /// {0,1,2,3}
  bool          move;
  int           dir;                    /* La direction souhaitée par le client */
  bool          place_bomb;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  //int           speed;                  /* La vitesse du joueur */
  //int           checksum;               /* Un checksum simple */
}               t_client_request;

typedef int t_map[14][14];

typedef struct  s_player_infos
{
  bool      connected;
  bool      alive;
  int       x_pos;
  int       y_pos;
  int       current_dir;
  //int       current_speed;
  //int       max_speed;
  int       bombs_left;
  int       bombs_capacity;
  int       frags;
}         t_player_infos;


typedef struct s_my_bomb
{
  int           x_pos;
  int           y_pos;
  unsigned int  timer;
  bool          placed;

}t_my_bomb;

typedef struct          s_game
{
	t_player_infos       player_infos[MAX_PLAYERS];
	t_map                map;
  t_my_bomb            bombs[MAX_BOMBS];
	//t_other             infos;
  int                  actual; 
}               		t_game;

void server_app();
int init_connection(int maxClients);
void end_connection(int sock);
int read_client(SOCKET sock, char *buffer);
int read_client2(SOCKET sock, void *buffer);
void write_client(SOCKET sock, const char *buffer);
void write_client2(SOCKET sock, t_game *game);
void send_message_to_all_clients(Client *clients, Client client, int actual, const char *buffer, char from_server);
void remove_client(Client *clients, int to_remove, int *actual);
void clear_clients(Client *clients, int actual);
int getMaxClient(int argc, char **argv);
int my_getnbr(char *str);
void my_putstr(const char *str);
char *my_strncpy(char *dest, char *src, int n);
char *my_strncat(char *dest, const char *src, int nb);
int test_name_availability(Client *clients, SOCKET sock, const char *name, int actual);
int isNumber(char *str);
void usage_message(char **argv);
t_game* init_game();
int is_bomb_at_position_2(t_my_bomb bombs[MAX_BOMBS], int x, int y);
int check_game_over(t_game *game);


void client_app(const char *name);
int init_connection_client(const char *address);
int read_server(SOCKET sock, char *buffer);
void read_server2(SOCKET sock, t_game *game);
void write_server(SOCKET sock, const char *buffer);
void write_server2(SOCKET sock, t_client_request *request);
move_request(SOCKET sock, int player_number, int move);
bomb_request(SOCKET sock, int player_number);

#endif