#ifndef GAMEPPLAY_MONITOR_CALLBACKS_H
# define GAMEPLAY_MONITOR_CALLBACKS_H

void	gameplay_command_msz(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_bct(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_mct(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_tna(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_ppo(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_plv(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_pin(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_sgt(t_gameplay* this,
			     struct s_monitor_command* command);
void	gameplay_command_sst(t_gameplay* this,
			     struct s_monitor_command* command);

#endif /* GAMEPLAY_MONITOR_CALLBACKS_H */
