#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			put_case_content(t_gameplay* this, char* buffer_msg, int x, int y)
{
  t_case*		contents;
  t_list_iterator	it;

  contents = &this->map.map[x + y * this->map.width];
  if (contents->linemate)
    strncat(buffer_msg, "linemate ", 4095);
  if (contents->deraumere)
    strncat(buffer_msg, "deraumere ", 4095);
  if (contents->sibur)
    strncat(buffer_msg, "sibur ", 4095);
  if (contents->phiras)
    strncat(buffer_msg, "phiras ", 4095);
  if (contents->thystame)
    strncat(buffer_msg, "thystame ", 4095);
  if (contents->linemate)
    strncat(buffer_msg, "linemate ", 4095);
  if (contents->food)
    strncat(buffer_msg, "nourriture ", 4095);
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      strncat(buffer_msg, "player ", 4095);
      it = list_iterator_next(it);
    }
  strncat(buffer_msg, ",", 4095);
}

void			gameplay_command_voir(t_gameplay* this, t_player_command* command)
{
  char			buffer[4069];
  int			i;
  int			j;
  int			x;
  int			y;

  i = 0;
  memset(buffer, 0, 4096);
  buffer[0] = '{';
  while (i < command->player->level)
    {
      j = -i;
      while (j <= i)
	{
	  if (command->player->direction == NORTH)
	    {
	      x = command->player->x + j % this->map.width;
	      y = command->player->y + i % this->map.height;
	    }
	  else if (command->player->direction == SOUTH)
	    {
	      x = command->player->x - j % this->map.width;
	      y = command->player->y - i % this->map.height;
	    }
	  else if (command->player->direction == EAST)
	    {
	      x = command->player->x + i % this->map.width;
	      y = command->player->y - j % this->map.height;
	    }
	  else if (command->player->direction == WEST)
	    {
	      x = command->player->x - i % this->map.width;
	      y = command->player->y + j % this->map.height;
	    }
	  if (x < 0)
	    x += this->map.width;
	  if (y < 0)
	    y += this->map.height;
	  put_case_content(this, buffer, x, y);
	  j++;
	}
      i++;
    }
  buffer[strnlen(buffer, 4094) - 1] = '}';
  buffer[4094] = '\n';
  buffer[4095] = '\0';
  client_send_msg(command->player->client, buffer);
}
