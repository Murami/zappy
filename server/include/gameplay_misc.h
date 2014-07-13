/*
** gameplay_misc.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:24:56 2014 otoshigami
** Last update Sun Jul 13 21:17:35 2014 otoshigami
*/

#ifndef GAMEPLAY_MISC_H
# define GAMEPLAY_MISC_H

bool	check_stone1(t_gameplay* this, int x, int y);
bool	check_stone2(t_gameplay* this, int x, int y);
bool	check_stone3(t_gameplay* this, int x, int y);
bool	check_stone4(t_gameplay* this, int x, int y);
bool	check_stone5(t_gameplay* this, int x, int y);
bool	check_stone6(t_gameplay* this, int x, int y);
bool	check_stone7(t_gameplay* this, int x, int y);
void	put_case_content(t_gameplay* this,  char* buffer_msg, int x, int y);
struct s_player*	gameplay_get_ghost(t_gameplay* gameplay,
					   struct s_team* team);

#endif /* GAMEPLAY_MISC_H */
