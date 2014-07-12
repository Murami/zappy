#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			gameplay_command_gauche(t_gameplay* this, t_player_command* command)
{
  command->player->direction -= 1;
  if (command->player->direction <= 0)
    command->player->direction = 4;
  client_send_msg(command->player->client, "ok");
  gameplay_send_pos(this, command->player);
}
