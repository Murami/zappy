#define  _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			gameplay_command_broadcast(t_gameplay* this,
						   t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;
  float			angle;
  int			side;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id != command->player->id)
	{
	  angle = fmod(atan2(player->x - command->player->x,
			     player->y - command->player->y) + M_PI, M_PI);
	  side =
	    (angle < M_PI / 2) ? EAST :
	    (angle < M_PI) ? NORTH :
	    (angle < 3 * M_PI / 2) ? WEST : SOUTH;
	  side += player->direction - 1;
	  sprintf(buffer, "message %d,%s\n", side, command->data);
	  client_send_msg(player->client, command->data);
	}
      it = list_iterator_next(it);
    }
}
