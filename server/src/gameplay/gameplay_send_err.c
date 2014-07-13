#include <stdio.h>
#include <string.h>
#include "client.h"

void	gameplay_send_sbp(t_client* client)
{
  char	buffer[4096];

  sprintf(buffer, "spb\n");
  client_send_msg(client, buffer);
}


void	gameplay_send_suc(t_client* client)
{
  char	buffer[4096];

  sprintf(buffer, "suc\n");
  client_send_msg(client, buffer);
}
