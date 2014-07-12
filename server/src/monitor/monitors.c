#include <stdio.h>
#include "player.h"
#include "team.h"
#include "client.h"
#include "client_graphic.h"
#include "monitors.h"

void		monitor_initialize(t_gameplay *this, t_client *client)
{
  monitor_send_size(this, client);
  monitor_send_delay(this, client);
  monitor_send_map(this, client);
  monitor_send_teams(this, client);
  monitor_send_players(this, client);
}



void		monitor_send_size(t_gameplay *this, t_client *client)
{
  char		buff[4096];

  sprintf(buff, "msz %d %d\n", this->map.width, this->map.height);
  client_send_msg(client, buff);

}

void		monitor_send_delay(t_gameplay *this, t_client *client)
{
  char		buff[4096];

  sprintf(buff, "sgt %d\n", this->delay);
  client_send_msg(client, buff);
}

void			monitor_send_teams(t_gameplay *this, t_client *client)
{
  char			buff[4096];
  t_team		*team;
  t_list_iterator	it;

  it = list_begin(this->teams);
  while (it != list_end(this->teams))
    {
      team = it->data;
      sprintf(buff, "tna %s\n", team->name);
      client_send_msg(client, buff);
      it = list_iterator_next(it);
    }
}

void		monitor_send_player_position(t_gameplay *this, int id, t_client* client)
{
  char			buffer[4096];

  (void)this;
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  printf("SEND POSITION\n");
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id == id)
	{
	  sprintf(buffer, "ppo %d %d %d\n",
		  player->id,
		  player->x,
		  player->y);
	}
      it = list_iterator_next(it);
   }
  client_send_msg(client, buffer);
}

void		monitor_send_player(t_player *player, t_client* client)
{
  char			buffer[4096];

  sprintf(buffer, "pnw %d %d %d %d %d %s\n",
	  player->id,
	  player->x,
	  player->y,
	  player->direction,
	  player->level,
	  player->team->name);
  client_send_msg(client, buffer);
}

void		monitor_send_players(t_gameplay *this, t_client *client)
{
  t_list_iterator	it;
  t_player*		player;

  (void)client;
  printf("send players\n");
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      monitor_send_player(player, client);
      it = list_iterator_next(it);
    }
}

void		monitor_send_eggs(t_gameplay *this, t_client *client)
{
  t_list_iterator	it;
  t_player*		player;

  (void)client;
  printf("send players\n");
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      monitor_send_player(player, client);
      it = list_iterator_next(it);
    }
}

void		monitor_send_case(t_gameplay *this, t_client *client, t_case *c)
{
  char		buff[4096];

  (void)this;
  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
  client_send_msg(client, buff);
}

void		monitor_send_map(t_gameplay *this, t_client *client)
{
  int		x;
  int		y;

  y = 0;
  while (y != this->map.height)
    {
      x = 0;
      while (x != this->map.width)
	{
	  monitor_send_case(this, client,
			    &this->map.map[x + y * this->map.width]);
	  x++;
	}
      y++;
    }
}
