#include <stdio.h>
#include "player.h"
#include "gameplay.h"
#include "client.h"

void			gameplay_send_case(t_client *monitor, t_case *c)
{
  char			buff[4096];

  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
  client_send_msg(monitor, buff);
}

void			gameplay_send_case_all(t_gameplay *this, t_player *player)
{
  t_list_iterator	it;
  t_client*		monitor;

  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      gameplay_send_case(monitor,
			 &this->map.map[player->x + player->y * this->map.width]);
      it = list_iterator_next(it);
    }
}
