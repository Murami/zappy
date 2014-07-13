/*
** time_val.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:23:55 2014 otoshigami
** Last update Sun Jul 13 17:24:02 2014 otoshigami
*/

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>

struct timeval	timeval_add(struct timeval t1, struct timeval t2);
struct timeval	timeval_sub(struct timeval t1, struct timeval t2);
int		timeval_comp(struct timeval t1, struct timeval t2);
struct timeval	timeval_min_nz(struct timeval t1, struct timeval t2);

#endif /* TIME_H */
