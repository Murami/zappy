#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "map.h"
#include "client.h"


void			gameplay_command_droite(t_gameplay* this, t_player_command* command)
{
  (void)this;
  command->player->direction += 1;
  if (command->player->direction >= 5)
    command->player->direction = 0;
  client_send_msg(command->player->client, "ok");
}

void			gameplay_command_gauche(t_gameplay* this, t_player_command* command)
{
  (void)this;
  command->player->direction -= 1;
  if (command->player->direction <= 0)
    command->player->direction = 4;
  client_send_msg(command->player->client, "ok");
}

void			gameplay_command_move(t_gameplay* this, t_player* player)
{
  player->y +=
    (player->direction == NORTH) ? 1 :
    (player->direction == SOUTH) ? -1 : 0;
  player->x +=
    (player->direction == EAST) ? 1 :
    (player->direction == WEST) ? -1 : 0;
  if (player->y >= this->map.height)
    player->y = 0;
  if (player->y < 0)
    player->y = this->map.height;
  if (player->x >= this->map.width)
    player->x = 0;
  if (player->x < 0)
    player->x = this->map.width;
}

void			gameplay_command_expulse(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  sprintf(buffer, "deplacement: %d\n", ((command->player->direction + 2) % 4));
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y &&
	  player->id != command->player->id)
	{
	  gameplay_command_move(this, player);
	  client_send_msg(player->client, buffer);
	}
      it = list_iterator_next(it);
    }
}
