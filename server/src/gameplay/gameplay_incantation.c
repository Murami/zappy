#include <stdio.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "map.h"
#include "client.h"

bool			check_players(t_gameplay* this,
				      t_player_command* command, int nb)
{
  int			i;
  t_list_iterator	it;
  t_player*		player;

  i = 0;
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y)
	{
	  if (command->player->level != player->level ||
	      i > nb)
	    return (false);
	  i++;
	}
      it = list_iterator_next(it);
    }
  return (i == nb);
}

bool			check_incant(t_gameplay* this, t_player_command* cmd)
{
  int			x;
  int			y;
  int			lvl;

  x = cmd->player->x;
  y = cmd->player->y;
  lvl = cmd->player->level;
  if ((lvl == 1 && check_stone1(this, x, y)) ||
      (lvl == 2 && check_stone2(this, x, y) && check_players(this, cmd, 2)) ||
      (lvl == 3 && check_stone3(this, x, y) && check_players(this, cmd, 2)) ||
      (lvl == 4 && check_stone4(this, x, y) && check_players(this, cmd, 4)) ||
      (lvl == 5 && check_stone5(this, x, y) && check_players(this, cmd, 4)) ||
      (lvl == 6 && check_stone6(this, x, y) && check_players(this, cmd, 6)) ||
      (lvl == 7 && check_stone7(this, x, y) && check_players(this, cmd, 6)))
    return (true);
  return (false);
}

void			gameplay_command_incantation(t_gameplay* this,
						     t_player_command* command)
{
  t_list_iterator	it;
  t_player*		player;
  char			buffer[4096];

  sprintf(buffer, "niveau actuel : %d\n", command->player->level + 1);
  if (check_incant(this, command))
    {
      gameplay_send_res_incant(this, command, true);
      it = list_begin(this->players);
      while (it != list_end(this->players))
	{
	  player = it->data;
	  if (player->x == command->player->x && player->y == command->player->y)
	    {
	      player->level++;
	      gameplay_send_lvl_all(this, player);
	      client_send_msg(player->client, buffer);
	    }
	  it = list_iterator_next(it);
	}
    }
  else
    gameplay_send_res_incant(this, command, false);
}
