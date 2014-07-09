#include <stdlib.h>
#include "monitor_command.h"
#include "gameplay.h"
#include "client_graphic.h"

t_monitor_command_binding	g_monitor_commands[] =
  {
    {0, "msz", NULL},
    {2, "bct", NULL},
    {0, "mct", NULL},
    {0, "tna", NULL},
    {1, "ppo", NULL},
    {1, "plv", NULL},
    {1, "pin", NULL},
    {0, "sgt", NULL},
    {0, "slt", NULL},
    {0, NULL, NULL}
  };

void			monitor_command_execute(t_monitor_command* this, t_gameplay* gameplay)
{
  /* g_player_commands[this->id_command].callback(gameplay); */
}

t_monitor_command*	monitor_command_new(t_client_graphic* client, char* data[2], int id_command)
{
  t_monitor_command*	command;

  command = malloc(sizeof(t_monitor_command));
  command->data[0] = data[0];
  command->data[1] = data[1];
  command->id_command = id_command;
  command->client = client;
  return (command);
}
