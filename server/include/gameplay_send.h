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
void	gameplay_send_egg_hatch(t_gameplay*, struct s_egg*);
void	gameplay_send_egg(t_gameplay*, struct s_player*);
void	gameplay_send_egg_lay(t_gameplay*, struct s_player*, struct s_egg*);

#endif /* GAMEPLAY_SEND_H */
