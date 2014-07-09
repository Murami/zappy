#ifndef MONITOR_BINDING_H
# define MONITOR_BINDING_H


struct s_gameplay;

typedef struct		s_monitor_command_binding
{
  int			has_data;
  const char*		request;
  void			(*callback)(struct s_gameplay*);
}			t_monitor_command_binding;

#endif /* MONITOR_BINDING_H */
