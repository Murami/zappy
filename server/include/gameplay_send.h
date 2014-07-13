#ifndef GAMEPLAY_SEND_H
#define GAMEPLAY_SEND_H

void	gameplay_send_drop(struct s_client*, struct s_player_command*, int);
void	gameplay_send_take(struct s_client*, struct s_player_command*, int);
void	gameplay_send_inventory(struct s_client*, struct s_player_command*);
void	gameplay_send_pos(t_gameplay*, struct s_player*);
void	gameplay_send_res(struct s_client*, bool);
void	gameplay_send_case(struct s_client*, struct s_case*);
void	gameplay_send_case_all(t_gameplay*, struct s_player*);
void	gameplay_send_lvl_all(t_gameplay*, struct s_player*);
void	gameplay_send_res_incant(t_gameplay*, struct s_player_command*, bool);

#endif /* GAMEPLAY_SEND_H */
