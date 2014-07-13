#ifndef GAMEPLAY_CALLBACK_OBJECT_H
# define GAMEPLAY_CALLBACK_OBJECT_H

void	gameplay_take_food(t_gameplay* this,
			   struct s_player_command* command);
void	gameplay_take_linemate(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_take_deraumere(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_take_sibur(t_gameplay* this,
			    struct s_player_command* command);
void	gameplay_take_mendiane(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_take_phiras(t_gameplay* this,
			     struct s_player_command* command);
void	gameplay_take_thystame(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_drop_food(t_gameplay* this,
			   struct s_player_command* command);
void	gameplay_drop_linemate(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_drop_deraumere(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_drop_sibur(t_gameplay* this,
			    struct s_player_command* command);
void	gameplay_drop_mendiane(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_drop_phiras(t_gameplay* this,
			     struct s_player_command* command);
void	gameplay_drop_thystame(t_gameplay* this,
			       struct s_player_command* command);

#endif /* GAMEPLAY_CALLBACK_OBJECT_H */
