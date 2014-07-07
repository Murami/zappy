#ifndef		_MUTEX_HH_
# define	_MUTEX_HH_

# include	<pthread.h>

class		Mutex
{
public:
  Mutex();
  ~Mutex();

public:
  void		lock();
  bool		trylock();
  void		unlock();

private:
  pthread_mutex_t	_mutex;
};

#endif
