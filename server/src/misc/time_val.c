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
  if (t1.tv_sec == t2.tv_sec && t1.tv_usec == t2.tv_usec)
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
  if (timeval_comp(t1, t2) < 0)
    return (t1);
  return (t2);
}
