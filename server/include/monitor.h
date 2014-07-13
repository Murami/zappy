/*
** monitor.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:28:55 2014 otoshigami
** Last update Sun Jul 13 17:28:56 2014 otoshigami
*/

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
