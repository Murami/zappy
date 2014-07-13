#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			put_case_content_x(char* buffer_msg, int val, char* str)
{
  while (val > 0)
    {
      strcat(buffer_msg, " ");
      strcat(buffer_msg, str);
      val--;
    }
}

void			put_case_content(t_gameplay* this,
					 char* buffer_msg, int x, int y)
{
  t_case*		contents;
  t_list_iterator	it;

  contents = &this->map.map[x + y * this->map.width];
  put_case_content_x(buffer_msg, contents->linemate, "linemate");
  put_case_content_x(buffer_msg, contents->linemate, "deraumere");
  put_case_content_x(buffer_msg, contents->linemate, "sibur");
  put_case_content_x(buffer_msg, contents->linemate, "phiras");
  put_case_content_x(buffer_msg, contents->linemate, "thystame");
  put_case_content_x(buffer_msg, contents->linemate, "linemate");
  put_case_content_x(buffer_msg, contents->linemate, "nourriture");
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      strncat(buffer_msg, " player", 4095);
      it = list_iterator_next(it);
    }
  strncat(buffer_msg, ",", 4095);
}

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
	  x = gameplay_voir_case_x(command, i, j);
	  y = gameplay_voir_case_y(command, i, j);
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
  buffer[4094] = '\n';
  buffer[4095] = '\0';
  client_send_msg(command->player->client, buffer);
}
