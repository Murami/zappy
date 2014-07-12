#include <stdio.h>
#include "team.h"
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"

void			monitor_send_teams(t_gameplay *this, t_client *client)
{
  char			buff[4096];
  t_team		*team;
  t_list_iterator	it;

  it = list_begin(this->teams);
  while (it != list_end(this->teams))
    {
      team = it->data;
      sprintf(buff, "tna %s\n", team->name);
      client_send_msg(client, buff);
      it = list_iterator_next(it);
    }
}