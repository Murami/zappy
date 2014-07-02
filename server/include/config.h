#ifndef		_CONFIG_H_
# define	_CONFIG_H_

# include	"list.h"

typedef struct	s_config
{
  int		port;
  int		width;
  int		height;
  int		delay;
  t_list	*teams;
}		t_config;

#endif	/* _CONFIG_H_ */
