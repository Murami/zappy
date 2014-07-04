#ifndef		_CONFIG_H_
# define	_CONFIG_H_

# include	"list.h"

typedef struct	s_config
{
  long int		port;
  long int		width;
  long int		height;
  long int		delay;
  long int		nbr;
  t_list		*team_names;
  t_list		*teams;
}		t_config;

#endif	/* _CONFIG_H_ */
