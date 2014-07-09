#include <stdlib.h>
#include "player_command.h"
#include "gameplay.h"
#include "client_player.h"

/*
** FAIRE LES BINDS
*/

t_player_command_binding	g_player_commands[] =
  {
    {7, "avance", gameplay_command_avance},
    {7, "droite", gameplay_command_droite},
    {7, "gauche", gameplay_command_gauche},
    {7, "voir", gameplay_command_voir},
    {1, "inventaire", gameplay_command_inventaire},
    {7, "prend objet", gameplay_command_prend_objet},
    {7, "expulse", gameplay_command_expulse},
    {7, "broadcast", gameplay_command_broadcast},
    {300, "incantation", gameplay_command_incantation},
    {42, "fork", gameplay_command_fork},
    {0, "connect_nbr", gameplay_command_connect_nbr},
    {0, NULL, NULL}
  };

void			player_command_execute(t_player_command* this, t_gameplay* gameplay)
{
  g_player_commands[this->id_command].callback(gameplay, this);
}

struct timeval		player_command_remaining_time(t_player_command* this, struct timeval time)
{
  time.tv_usec -= this->expiration_time.tv_usec;
  if (time.tv_usec < 0)
    {
      time.tv_usec += 1000000;
      time.tv_sec -= 1;
    }
  time.tv_sec -= this->expiration_time.tv_sec;
  return (time);
}

t_player_command*	player_command_new(t_client_player* client,
					   t_gameplay* gameplay,
					   char* data,
					   int id_command)
{
  t_player_command*	command;

  command = malloc(sizeof(t_player_command));
  if (command == NULL)
    return (NULL);
  command->expiration_time.tv_usec = gameplay->time.tv_usec + (g_player_commands[id_command].time * 1000000) / gameplay->delay;
  command->expiration_time.tv_sec = command->expiration_time.tv_usec / 1000000;
  command->expiration_time.tv_usec %= 1000000;
  command->player = client->player;
  command->data = data;
  command->id_command = id_command;
  return (command);
}

void			player_command_delete(t_player_command* command)
{
  free(command);
}
