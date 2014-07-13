/*
** gameplay_voir.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:07:52 2014 otoshigami
<<<<<<< HEAD
** Last update Sun Jul 13 23:02:57 2014 Desabre Quentin
=======
** Last update Sun Jul 13 20:14:45 2014 otoshigami
>>>>>>> 58f2b3e522fb05934a773d1712fb0a3a2a1b0866
*/

#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

int	gameplay_voir_case_x(t_player_command* command, int line, int c)
{
  int	sign;

  if (command->player->direction == NORTH ||
      command->player->direction == EAST)
    sign = 1;
  else
    sign = -1;

  if (command->player->direction == NORTH ||
      command->player->direction == SOUTH)
    return (sign * line);
  else
    return (sign * c);
}

int	gameplay_voir_case_y(t_player_command* command, int line, int c)
{
  int	sign;

  if (command->player->direction == NORTH ||
      command->player->direction == WEST)
    sign = 1;
  else
    sign = -1;

  if (command->player->direction == NORTH ||
      command->player->direction == SOUTH)
    return (sign * c);
  else

    return (sign * line);
}

void	gameplay_voir(t_gameplay* this, t_player_command* command,
		      char* buffer)
{
  int	i;
  int	j;
  int	x;
  int	y;

  i = 0;
  while (i <= command->player->level)
    {
      j = -i;
      while (j <= i)
	{
	  x = command->player->x +
	    gameplay_voir_case_x(command, i, j) %
	    this->map.width;
	  y = command->player->y +
	    gameplay_voir_case_y(command, i, j) %
	    this->map.height;
	  if (x < 0)
	    x += this->map.width;
	  if (y < 0)
	    y += this->map.height;
	  put_case_content(this, buffer, x, y);
	  j++;
	}
      i++;
    }
}

void	gameplay_command_voir(t_gameplay* this, t_player_command* command)
{
  char	buffer[4096];

  memset(buffer, 0, 4096);
  buffer[0] = '{';
  gameplay_voir(this, command, buffer);
  buffer[strnlen(buffer, 4094) - 1] = '}';
  strncat(buffer, "\n", 4096);
  buffer[4094] = '\n';
  buffer[4095] = '\0';
  client_send_msg(command->player->client, buffer);
}
