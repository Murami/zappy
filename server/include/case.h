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

void		case_initialize(t_case *this, int x, int y);

#endif	/* _CASE_H_ */
