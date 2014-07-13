#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "egg.h"

void			monitor_send_eggs(t_gameplay *this, t_client *client)
{
  t_list_iterator	it;
  t_egg*		egg;
  char			buffer[4096];

  it = list_begin(this->eggs);
  while (it != list_end(this->eggs))
    {
      egg = it->data;
      sprintf(buffer, "enw %d %d %d %d\n", egg->id, egg->id_player, egg->x, egg->y);
      client_send_msg(client, buffer);
      it = list_iterator_next(it);
    }
}
