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
  egg->id = gameplay_get_new_id(this);
  egg->id_player = command->player->id;
  list_push_back(this->eggs, egg);
  gameplay_send_egg_lay(this, command->player);
}

int			count_taken_slot(t_gameplay* this, t_team* team)
{
  t_list_iterator	it;
  t_player*		player;
  int			i;

  i = 0;
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (!player->is_egg && player->team == team)
	i++;
      it = list_iterator_next(it);
    }
  it = list_begin(this->ghosts);
  while (it != list_end(this->ghosts))
    {
      player = it->data;
      if (!player->is_egg && player->team == team)
	i++;
      it = list_iterator_next(it);
    }
  return (i);
}

void			gameplay_command_connect_nbr(t_gameplay* this,
						     t_player_command* command)
{
  char			buffer[4096];

  sprintf(buffer, "%d", list_size(this->ghosts)
	  + command->player->team->nb_slots
	  - count_taken_slot(this, command->player->team));
  client_send_msg(command->player->client, buffer);
}
