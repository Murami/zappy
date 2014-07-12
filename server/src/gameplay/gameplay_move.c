#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "map.h"
#include "client.h"

void			gameplay_send_pos(t_gameplay *this, t_player *player)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_client*		monitor;

  sprintf(buffer, "ppo %d %d %d %d\n",
	  player->id,
	  player->x,
	  player->y,
	  player->direction);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_command_move(t_gameplay* this, t_player* player)
{
  player->y +=
    (player->direction == NORTH) ? 1 :
    (player->direction == SOUTH) ? -1 : 0;
  player->x +=
    (player->direction == EAST) ? 1 :
    (player->direction == WEST) ? -1 : 0;
  if (player->y >= this->map.height)
    player->y = 0;
  if (player->y < 0)
    player->y = this->map.height;
  if (player->x >= this->map.width)
    player->x = 0;
  if (player->x < 0)
    player->x = this->map.width;
}
