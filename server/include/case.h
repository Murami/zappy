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
