#include <stdio.h>
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"

void			monitor_send_delay(t_gameplay *this, t_client *client)
{
  char			buff[4096];

  sprintf(buff, "sgt %d\n", this->delay);
  client_send_msg(client, buff);
}
