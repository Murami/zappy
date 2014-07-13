/*
** time_val.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:04:48 2014 quentin desabre
** Last update Sun Jul 13 22:30:58 2014 otoshigami
*/

#include "time_val.h"

struct timeval	timeval_add(struct timeval t1, struct timeval t2)
{
  t1.tv_sec += t2.tv_sec;
  t1.tv_usec += t2.tv_usec;
  t1.tv_sec += t1.tv_usec / 1000000;
  t1.tv_usec %= 1000000;
  if (t1.tv_usec < 0)
    {
      t1.tv_usec += 1000000;
      t1.tv_sec -= 1;
    }
  return (t1);
}

struct timeval	timeval_sub(struct timeval t1, struct timeval t2)
{
  t1.tv_sec -= t2.tv_sec;
  t1.tv_usec -= t2.tv_usec;
  t1.tv_sec += t1.tv_usec / 1000000;
  t1.tv_usec %= 1000000;
  if (t1.tv_usec < 0)
    {
      t1.tv_usec += 1000000;
      t1.tv_sec -= 1;
    }
  return (t1);
}

int		timeval_comp(struct timeval t1, struct timeval t2)
{
  printf("%d\n", t1.tv_sec);
  printf("%d\n", t1.tv_usec);
  printf("%d\n", t2.tv_sec);
  printf("%d\n", t2.tv_usec);
  if (t1.tv_sec ==
      t2.tv_sec &&
      t1.tv_usec ==
      t2.tv_usec)
    return (0);
  if ((t1.tv_sec == t2.tv_sec && t1.tv_usec > t2.tv_usec) ||
      (t1.tv_sec > t2.tv_sec))
    return (1);
  return (-1);
}

struct timeval	timeval_min_nz(struct timeval t1, struct timeval t2)
{
  if (t1.tv_sec == 0 && t1.tv_usec == 0)
    t1 = t2;
  if (t2.tv_sec == 0 && t2.tv_usec == 0)
    t2 = t1;
  if (timeval_comp(t1, t2) < 0)
    return (t1);
  return (t2);
}
