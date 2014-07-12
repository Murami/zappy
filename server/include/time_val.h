#ifndef TIME_H
# define TIME_H

#include <sys/time.h>

struct timeval	timeval_add(struct timeval t1, struct timeval t2);
struct timeval	timeval_sub(struct timeval t1, struct timeval t2);
int		timeval_comp(struct timeval t1, struct timeval t2);
struct timeval	timeval_min_nz(struct timeval t1, struct timeval t2);

#endif /* TIME_H */
