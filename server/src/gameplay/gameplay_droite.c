#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			gameplay_command_droite(t_gameplay* this, t_player_command* command)
{
  command->player->direction += 1;
  if (command->player->direction >= 5)
    command->player->direction = 1;
  client_send_msg(command->player->client, "ok\n");
  gameplay_send_pos(this, command->player);
}
