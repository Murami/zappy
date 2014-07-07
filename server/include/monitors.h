#ifndef		_MONITOR_H_
# define	_MONITOR_H_

# include	"server.h"
# include	"client.h"

void		monitor_initialize(t_server *this, t_client *client);
void		monitor_send_size(t_server *this, t_client *client);
void		monitor_send_delay(t_server *this, t_client *client);
void		monitor_send_teams(t_server *this, t_client *client);
void		monitor_send_case(t_server *this, t_client *client, t_case *c);
void		monitor_send_map(t_server *this, t_client *client);
void		monitor_send_players(t_server *this, t_client *client);
void		monitor_send_eggs(t_server *this, t_client *client);

#endif /* _MONITOR_H_ */
