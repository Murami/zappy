#include <stdio.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "map.h"
#include "client.h"

bool			check_stone_lvl1(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 0 &&
	  this->map.map[x + y * this->map.width].sibur == 0 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone_lvl2(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 1 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}


bool			check_stone_lvl3(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 2 &&
	  this->map.map[x + y * this->map.width].deraumere == 0 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 2 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}


bool			check_stone_lvl4(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 1 &&
	  this->map.map[x + y * this->map.width].sibur == 2 &&
	  this->map.map[x + y * this->map.width].mendiane == 0  &&
	  this->map.map[x + y * this->map.width].phiras == 1 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}


bool			check_stone_lvl5(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 3 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}


bool			check_stone_lvl6(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 3 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 1 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}


bool			check_stone_lvl7(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 2 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 2 &&
	  this->map.map[x + y * this->map.width].mendiane == 2 &&
	  this->map.map[x + y * this->map.width].phiras == 2 &&
	  this->map.map[x + y * this->map.width].thystame == 1);
}

bool			check_players(t_gameplay* this, t_player_command* command, int nb)
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

bool			check_incant(t_gameplay* this, t_player_command* command)
{
  int	x;
  int	y;
  int	level;

  x = command->player->x;
  y = command->player->y;
  level = command->player->level;
  if ((level == 1 && check_stone_lvl1(this, x, y)) ||
      (level == 2 && check_stone_lvl2(this, x, y) && check_players(this, command, 2)) ||
      (level == 3 && check_stone_lvl3(this, x, y) && check_players(this, command, 2)) ||
      (level == 4 && check_stone_lvl4(this, x, y) && check_players(this, command, 4)) ||
      (level == 5 && check_stone_lvl5(this, x, y) && check_players(this, command, 4)) ||
      (level == 6 && check_stone_lvl6(this, x, y) && check_players(this, command, 6)) ||
      (level == 7 && check_stone_lvl7(this, x, y) && check_players(this, command, 6)))
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
      it = list_begin(this->players);
      while (it != list_end(this->players))
	{
	  player = it->data;
	  if (player->x == command->player->x && player->y == command->player->y)
	    {
	      player->level++;
	      client_send_msg(player->client, buffer);
	    }
	  it = list_iterator_next(it);
	}
    }
}
