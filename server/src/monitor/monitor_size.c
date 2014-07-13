#include <stdio.h>
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "gameplay.h"

void			monitor_send_size(t_gameplay *this, t_client *client)
{
  char			buff[4096];

  sprintf(buff, "msz %d %d\n", this->map.width, this->map.height);
  client_send_msg(client, buff);

}
