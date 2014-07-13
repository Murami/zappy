/*
** gameplay_object.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:35:33 2014 otoshigami
** Last update Sun Jul 13 17:35:34 2014 otoshigami
*/

#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"
#include "time_val.h"

t_object_binding object_bindings[] =
  {
    {gameplay_drop_food, gameplay_take_food, "nourriture"},
    {gameplay_drop_linemate, gameplay_take_linemate, "linemate"},
    {gameplay_drop_deraumere, gameplay_take_deraumere, "deraumere"},
    {gameplay_drop_sibur, gameplay_take_sibur, "sibur"},
    {gameplay_drop_mendiane, gameplay_take_mendiane, "mendiane"},
    {gameplay_drop_phiras, gameplay_take_phiras, "phiras"},
    {gameplay_drop_thystame, gameplay_take_thystame, "thystame"},
    {NULL, NULL, NULL}
  };

void			gameplay_command_inventaire(t_gameplay* this,
						    t_player_command* command)
{
  char			buffer[4096];
  struct timeval	time;
  float			foods;

  (void)this;
  time = timeval_sub(command->player->death_time, time);
  foods = time.tv_sec + ((float)time.tv_usec) / 1000000.f;
  foods /=  (126.f / ((float)this->delay));
  if (foods < 0)
    foods = 0;
  sprintf(buffer, "{nourriture %d, linemate %d, deraumere %d, "
	  "sibur %d, mendiane %d, phiras %d, thystame %d}",
	  (int)foods,
	  command->player->inventory.linemate,
	  command->player->inventory.deraumere,
	  command->player->inventory.sibur,
	  command->player->inventory.mendiane,
	  command->player->inventory.phiras,
	  command->player->inventory.thystame);
  client_send_msg(command->player->client, buffer);
}

void			gameplay_command_pose(t_gameplay* this,
					      t_player_command* command)
{
  int			i = 0;

  while (object_bindings[i].object)
    {
      if ((strcmp(command->data, object_bindings[i].object)) == 0)
	{
	  object_bindings[i].put(this, command);
	  return;
	}
      i++;
    }
}

void			gameplay_command_prend(t_gameplay* this,
					       t_player_command* command)
{
  int			i = 0;

  while (object_bindings[i].object)
    {
      if ((strcmp(command->data, object_bindings[i].object)) == 0)
	{
	  object_bindings[i].take(this, command);
	  return;
	}
      i++;
    }
}
