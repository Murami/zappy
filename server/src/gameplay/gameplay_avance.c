#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "map.h"
#include "client.h"

void			bind_command_avance(t_gameplay *this, t_player_command *command)
{
 t_list_iterator	it;
 t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      monitor_send_player_position(this, command->player->id, monitor);
      it = list_iterator_next(it);
    }
}

void			gameplay_command_avance(t_gameplay* this, t_player_command* command)
{
  command->player->y +=
    (command->player->direction == NORTH) ? 1 :
    (command->player->direction == SOUTH) ? -1 : 0;
  command->player->x +=
    (command->player->direction == EAST) ? 1 :
    (command->player->direction == WEST) ? -1 : 0;
  if (command->player->y >= this->map.height)
    command->player->y = 0;
  if (command->player->y < 0)
    command->player->y = this->map.height;
  if (command->player->x >= this->map.width)
    command->player->x = 0;
  if (command->player->x < 0)
    command->player->x = this->map.width;
  bind_command_avance(this, command);
}
