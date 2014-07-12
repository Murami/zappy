#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "egg.h"

void			gameplay_send_egg(t_gameplay *this, t_player *player)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  sprintf(buffer, "pfk %d\n", player->id);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_send_egg_lay(t_gameplay *this, t_player *player, t_egg *egg)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  sprintf(buffer, "enw %d %d %d %d\n", egg->id, player->id, egg->x, egg->y);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_send_egg_hatch(t_gameplay *this, t_egg *egg)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  sprintf(buffer, "eht %d\n", egg->id);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}