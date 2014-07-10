#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"
#include "time_val.h"

void		gameplay_take_food(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];
  struct timeval	time_food;

  time_food.tv_usec = (126 * 1000000) / this->delay;
  time_food.tv_sec %= 10000000;
  if (this->map.map[command->player->x + command->player->y *
		    this->map.width].food != 0)
    {
      this->map.map[command->player->x + command->player->y *
      		    this->map.width].food--;
      command->player->death_time = timeval_add(command->player->death_time,
						time_food);
      /* command->player->inventory.food++; */
      sprintf(buffer, "ok");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko");
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
      /* command->player->inventory.food--; */
      sprintf(buffer, "ok");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko");
      client_send_msg(command->player->client, buffer);
    }
}
