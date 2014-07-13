/*
** case.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:27:55 2014 otoshigami
** Last update Sun Jul 13 17:27:56 2014 otoshigami
*/

#ifndef		_CASE_H_
# define	_CASE_H_

typedef struct	s_case
{
  int		x;
  int		y;
  int		food;
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
}		t_case;

typedef t_case t_inventory;

void		case_initialize(t_case *this, int x, int y);
void		case_randomize(t_case *this, int x, int y);

#endif	/* _CASE_H_ */
