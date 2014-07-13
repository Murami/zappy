/*
** gameplay_object_callback.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:24:27 2014 otoshigami
** Last update Sun Jul 13 17:24:28 2014 otoshigami
*/

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
