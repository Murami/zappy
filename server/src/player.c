#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "client.h"
#include "team.h"
#include "gameplay.h"
#include "socketstream.h"
#include "client_player.h"

void		player_initialize(t_player *this, t_gameplay *gameplay,
				  t_client *client, t_team *team)
{
  char		buffer[4096];

  ((t_client_player*)client)->player = this;
  this->id = client->socketstream->socket;
  this->direction = rand() % 4 + 1;
  this->x = rand() % gameplay->map.width;
  this->y = rand() % gameplay->map.height;
  this->level = 1;
  this->team = team;
  team->nb_slots--;
  case_initialize(&this->inventory, this->x, this->y);
  sprintf(buffer, "%d\n", team->nb_slots);
  client_send_msg(client, buffer);
  sprintf(buffer, "%d %d\n", this->x, this->y);
  client_send_msg(client, buffer);


  printf("[NEW PLAYER]\n");
  printf("pos x [%d] --- pos y [%d]\n", this->x, this->y);
  printf("level [%d]\n", this->level);
  printf("team [%s] - nb slot [%d]\n", this->team->name, this->team->nb_slots);
}

t_player*	player_new(t_gameplay *gameplay, t_client *client, t_team *team)
{
  t_player	*player;

  player = malloc(sizeof(t_player));
  if (player == NULL)
    return (NULL);
  player_initialize(player, gameplay, client, team);
  return (player);
}
