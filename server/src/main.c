/*
** main.c for main in /home/desabr_q/Desktop/zappy/PSU_2013_zappy
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Wed Jun 25 12:03:10 2014 quentin desabre
** Last update Wed Jul  2 17:23:55 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"
#include "team.h"
#include "config.h"
#include "server.h"

int		main()
{
  t_config	config;
  t_server	server;

  /* init du t_config */
  config.port = 4242;
  config.width = 20;
  config.height = 20;
  config.delay = 100;
  config.teams = list_new();
  list_push_front(config.teams, team_new(5, "team1"));
  list_push_front(config.teams, team_new(5, "team2"));

  /* lancement server */
  server_initialize(&server, config);
  server_launch(&server);
  return (0);
}
