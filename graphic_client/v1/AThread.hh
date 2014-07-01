#ifndef		__ATHREAD_HH__
# define	__ATHREAD_HH__

# include	<stdexcept>
# include	<pthread.h>

class		AThread
{
private :
  pthread_t	_thread;

public :
  AThread();
  virtual ~AThread();

public :
  void	start();
  void	stop();

public :
  virtual void	run() = 0;
};

void		*start_thread(void*);

#endif
