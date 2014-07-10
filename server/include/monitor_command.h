#ifndef MONITOR_COMMAND_H
# define MONITOR_COMMAND_H

#include "monitor_command_binding.h"

struct s_client_graphic;
struct s_gameplay;

typedef struct				s_monitor_command
{
  int					id_command;
  char*					data[2];
  struct s_client_graphic*		client;
}					t_monitor_command;

extern t_monitor_command_binding	g_monitor_commands[];

void			monitor_command_execute(struct s_monitor_command* this,
						struct s_gameplay* gameplay);
t_monitor_command*	monitor_command_new(struct s_client_graphic* client,
					    char* data[2], int id_command);
void			monitor_command_delete(t_monitor_command* command);
#endif /* MONITOR_COMMAND_H */
