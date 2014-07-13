//
// Mutex.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/network
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:03:54 2014 Manu
// Last update Sun Jul 13 23:03:54 2014 Manu
//

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
