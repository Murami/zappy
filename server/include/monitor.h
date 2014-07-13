#ifndef		_MONITOR_H_
# define	_MONITOR_H_

struct s_gameplay;
struct s_client;
struct s_player;
struct s_case;

void	monitor_initialize(struct s_gameplay*, struct s_client*);
void	monitor_send_size(struct s_gameplay*, struct s_client*);
void	monitor_send_delay(struct s_gameplay*, struct s_client*);
void	monitor_send_teams(struct s_gameplay*, struct s_client*);
void	monitor_send_case(struct s_client*, struct s_case*);
void	monitor_send_map(struct s_gameplay*, struct s_client*);
void	monitor_send_player(struct s_player*, struct s_client*);
void	monitor_send_players(struct s_gameplay*, struct s_client*);
void	monitor_send_eggs(struct s_gameplay*, struct s_client *);
void	monitor_send_pdi(struct s_gameplay*, struct s_player*);
void	monitor_send_edi(struct s_gameplay*, struct s_player*);
void	monitor_send_egg_connect(struct s_player*, struct s_client*);

#endif /* _MONITOR_H_ */
