#include <stdlib.h>
#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"
#include "team.h"
#include "egg.h"
#include "time_val.h"

void			gameplay_command_fork(t_gameplay* this,
					      t_player_command* command)
{
  t_egg*		egg;
  struct timeval	time;

  time.tv_usec = (600 * 1000000) / this->delay;
  time.tv_sec = 0;
  egg = malloc(sizeof(t_egg));
  egg->team = command->player->team;
  egg->time = timeval_add(this->time, time);
  egg->x = command->player->x;
  egg->y = command->player->y;
  list_push_back(this->eggs, egg);
  gameplay_send_egg_hatch(this, command->player);
}

void			gameplay_command_connect_nbr(t_gameplay* this,
						     t_player_command* command)
{
  char			buffer[4096];

  (void) this;
  sprintf(buffer, "%d", command->player->team->nb_slots);
  client_send_msg(command->player->client, buffer);
}
