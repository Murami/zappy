#ifndef GAMEPLAY_IA_CALLBACKS
# define GAMEPLAY_IA_CALLBACK

#include "gameplay_object_callback.h"

void	gameplay_command_move(t_gameplay*,
			      struct s_player*);
void	gameplay_command_avance(t_gameplay*,
				struct s_player_command*);
void	gameplay_command_droite(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_command_gauche(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_command_voir(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_inventaire(t_gameplay* this,
				    struct s_player_command* command);
void	gameplay_command_prend(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_command_pose(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_expulse(t_gameplay* this,
				 struct s_player_command* command);
void	gameplay_command_broadcast(t_gameplay* this,
				   struct s_player_command* command);
void	gameplay_command_incantation(t_gameplay* this,
				     struct s_player_command* command);
void	gameplay_command_fork(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_connect_nbr(t_gameplay* this,
				     struct s_player_command* command);

#endif /* GAMEPLAY_IA_CALLBACK */
