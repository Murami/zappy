#include <stdlib.h>
#include <string.h>
#include "monitor_command.h"
#include "gameplay.h"
#include "client_graphic.h"

t_monitor_command_binding	g_monitor_commands[] =
  {
    {0, "msz", gameplay_command_msz},
    {2, "bct", gameplay_command_bct},
    {0, "mct", gameplay_command_mct},
    {0, "tna", gameplay_command_tna},
    {1, "ppo", gameplay_command_ppo},
    {1, "plv", gameplay_command_plv},
    {1, "pin", gameplay_command_pin},
    {0, "sgt", gameplay_command_sgt},
    {0, "sst", gameplay_command_sst},
    {0, NULL, NULL}
  };

void			monitor_command_execute(t_monitor_command* this,
						t_gameplay* gameplay)
{
  (void) this;
  (void) gameplay;
  g_monitor_commands[this->id_command].callback(gameplay, this);
}

t_monitor_command*	monitor_command_new(t_client_graphic* client,
					    char* data[2], int id_command)
{
  t_monitor_command*	command;

  command = malloc(sizeof(t_monitor_command));
  if (data[0])
    command->data[0] = strdup(data[0]);
  else
    command->data[0] = NULL;
  if (data[1])
    command->data[1] = strdup(data[1]);
  else
    command->data[1] = NULL;
  command->id_command = id_command;
  command->client = client;
  return (command);
}

void			monitor_command_delete(t_monitor_command* command)
{
  if (command->data[0])
    free(command->data[0]);
  if (command->data[1])
    free(command->data[1]);
  free(command);
}
