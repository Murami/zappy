#include <stdio.h>
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"

void			monitor_send_eggs(t_gameplay *this, t_client *client)
{
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      monitor_send_player(player, client);
      it = list_iterator_next(it);
    }
}
