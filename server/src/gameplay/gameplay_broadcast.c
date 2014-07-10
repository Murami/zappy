#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			gameplay_command_broadcast(t_gameplay* this,
						   t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  // le 1 est a changer par la direction mais faut voir avec guerot
  sprintf(buffer, "message %d,%s\n", 1, command->data);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id != command->player->id)
	{
	  client_send_msg(player->client, command->data);
	}
      it = list_iterator_next(it);
    }
}
