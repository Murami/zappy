#include <stdio.h>
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "socketstream.h"
#include "gameplay.h"

void			monitor_initialize(t_gameplay *this, t_client *client)
{
  printf("new monitor connected [%d]\n", client->socketstream->socket);
  monitor_send_size(this, client);
  monitor_send_delay(this, client);
  monitor_send_map(this, client);
  monitor_send_teams(this, client);
  monitor_send_players(this, client);
  monitor_send_eggs(this, client);
}
