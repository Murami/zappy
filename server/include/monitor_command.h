#ifndef MONITOR_COMMAND_H
# define MONITOR_COMMAND_H

#include "monitor_command_binding.h"

struct s_client_graphic;

typedef struct		s_monitor_command
{
  int			id_command;
  char*			data[2];
  struct s_client_graphic*	client;
}			t_monitor_command;

extern t_monitor_command_binding	g_monitor_commands[];

#endif /* MONITOR_COMMAND_H */
