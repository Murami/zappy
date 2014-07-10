#include "gameplay.h"
#include "player_command.h"
#include "monitor_command.h"
#include "player.h"

void			gameplay_add_player_command(t_gameplay* this,
						    t_player_command* command)
{
  player_add_action(command->player, command);
  if (list_size(command->player->command_queue) == 1)
    gameplay_update_player_position(this, command->player);
}

void			gameplay_add_monitor_command(t_gameplay* this,
						     t_monitor_command* command)
{
  monitor_command_execute(command, this);
}
