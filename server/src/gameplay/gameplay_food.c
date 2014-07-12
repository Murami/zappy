#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"
#include "time_val.h"

void		bind_command_take(t_gameplay *this, t_case *c)
{
  char			buff[4096];
  t_list_iterator	it;
  t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
      client_send_msg(monitor, buff);
      it = list_iterator_next(it);
    }
}

void		gameplay_take_food(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];
  struct timeval	time_food;

  time_food.tv_usec = (126 * 1000000) / this->delay;
  time_food.tv_sec %= 10000000;
  if (this->map.map[command->player->x + command->player->y *
		    this->map.width].food != 0)
    {
      printf("[TAKE FOOD]\n");
      this->map.map[command->player->x + command->player->y *
      		    this->map.width].food--;
      command->player->death_time = timeval_add(command->player->death_time,
						time_food);
      sprintf(buffer, "ok\n");
      bind_command_take(this,
			&this->map.map[command->player->x + this->map.width * command->player->y]);
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko\n");
      client_send_msg(command->player->client, buffer);
    }
}

void		gameplay_drop_food(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];
  struct timeval	time_food;
  struct timeval	remaining_time;

  remaining_time = timeval_sub(this->time, command->player->death_time);
  time_food.tv_usec = (126 * 1000000) / this->delay;
  time_food.tv_sec %= 10000000;
  if (timeval_comp(time_food, remaining_time) < 1)
    {
      this->map.map[command->player->x + command->player-> y *
		    this->map.width].food++;
      command->player->death_time = timeval_sub(command->player->death_time,
						time_food);
      bind_command_take(this,
			&this->map.map[command->player->x + this->map.width * command->player->y]);
      sprintf(buffer, "ok\n");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko\n");
      client_send_msg(command->player->client, buffer);
    }
}
