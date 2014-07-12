#include <stdio.h>
#include "client.h"
#include "player_command.h"
#include "player.h"

void		gameplay_send_drop(t_client *monitor, t_player_command *command, int id)
{
  char		buffer[4096];

  sprintf(buffer, "pdr %d %d\n", command->player->id, id);
  client_send_msg(monitor, buffer);
}
