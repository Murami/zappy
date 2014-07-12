#include <stdio.h>
#include "player.h"
#include "team.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"

void			monitor_send_case(t_client *client, t_case *c)
{
  char			buff[4096];

  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
  client_send_msg(client, buff);
}

void			monitor_send_map(t_gameplay *this, t_client *client)
{
  int			x;
  int			y;

  y = 0;
  while (y != this->map.height)
    {
      x = 0;
      while (x != this->map.width)
	{
	  monitor_send_case(client,
			    &this->map.map[x + y * this->map.width]);
	  x++;
	}
      y++;
    }
}
