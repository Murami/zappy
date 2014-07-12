#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"
#include "time_val.h"

void			bind_command_object(t_gameplay *this, t_player_command *command,
					    t_case *c, int id)
{
  t_list_iterator	it;
  t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      if (command->id_command == 5)
	gameplay_send_take(monitor, command, id);
      else if (command->id_command == 6)
	gameplay_send_drop(monitor, command, id);
      gameplay_send_inventory(monitor, command);
      gameplay_send_case(monitor, c);
      it = list_iterator_next(it);
    }
}

void			gameplay_take_food(t_gameplay *this, t_player_command *command)
{
  int			x;
  int			y;
  struct timeval	t;

  x = command->player->x;
  y = command->player->y;
  t.tv_usec = (126 * 1000000) / this->delay;
  t.tv_sec %= 10000000;
  if (this->map.map[x + y * this->map.width].food != 0)
    {
      this->map.map[x + y * this->map.width].food--;
      command->player->death_time = timeval_add(command->player->death_time, t);
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 0);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_food(t_gameplay *this, t_player_command *command)
{
  int			x;
  int			y;
  struct timeval	t;
  struct timeval	remaining_time;

  x = command->player->x;
  y = command->player->y;
  remaining_time = timeval_sub(this->time, command->player->death_time);
  t.tv_usec = (126 * 1000000) / this->delay;
  t.tv_sec %= 10000000;
  if (timeval_comp(t, remaining_time) < 1)
    {
      this->map.map[command->player->x + command->player-> y *
		    this->map.width].food++;
      command->player->death_time = timeval_sub(command->player->death_time, t);
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 0);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
