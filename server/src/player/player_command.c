/*
** player_command.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:07:35 2014 otoshigami
** Last update Sun Jul 13 23:06:54 2014 Desabre Quentin
*/

#include <stdlib.h>
#include <string.h>
#include "player_command.h"
#include "gameplay.h"
#include "client_player.h"
#include "time_val.h"

t_player_command_binding	g_player_commands[] =
  {
    {0, 7, "avance", gameplay_command_avance},
    {0, 7, "droite", gameplay_command_droite},
    {0, 7, "gauche", gameplay_command_gauche},
    {0, 7, "voir", gameplay_command_voir},
    {0, 1, "inventaire", gameplay_command_inventaire},
    {1, 7, "prend", gameplay_command_prend},
    {1, 7, "pose", gameplay_command_pose},
    {0, 7, "expulse", gameplay_command_expulse},
    {1, 7, "broadcast", gameplay_command_broadcast},
    {0, 300, "incantation", gameplay_command_incantation},
    {0, 42, "fork", gameplay_command_fork},
    {0, 0, "connect_nbr", gameplay_command_connect_nbr},
    {0, 0, NULL, NULL}
  };

void			player_command_execute(t_player_command* this,
					       t_gameplay* gameplay)
{
  g_player_commands[this->id_command].callback(gameplay, this);
}

struct timeval		player_command_remaining_time(t_player_command* this,
						      struct timeval time)
{
  return (timeval_sub(time, this->expiration_time));
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
  command->expiration_time.tv_usec =
    (g_player_commands[id_command].time * 1000000) / gameplay->delay;
  command->expiration_time.tv_sec = 0;
  command->expiration_time =
    timeval_add(command->expiration_time, gameplay->time);
  command->player = client->player;
  if (data)
    command->data = strdup(data);
  else
    command->data = NULL;
  command->id_command = id_command;
  return (command);
}

void			player_command_delete(t_player_command* command)
{
  if (command->data)
    free(command->data);
  free(command);
}
