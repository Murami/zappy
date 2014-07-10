#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"
#include "team.h"

void			gameplay_command_fork(t_gameplay* this,
					      t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_connect_nbr(t_gameplay* this,
						     t_player_command* command)
{
  char			buffer[4096];

  (void) this;
  sprintf(buffer, "%d", command->player->team->nb_slots);
  client_send_msg(command->player->client, buffer);
}
