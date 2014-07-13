//
// SafeQueue.hpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/network
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:03:51 2014 Manu
// Last update Sun Jul 13 23:03:51 2014 Manu
//

#ifndef		_SAFE_QUEUE_HH_
# define	_SAFE_QUEUE_HH_

# include	<queue>
# include	"network/Mutex.hh"

template <typename T>
class		SafeQueue
{
public:
  SafeQueue();
  ~SafeQueue();

public :
  void		push(T);
  void		pop();
  T		front();
  std::size_t	size();
  bool		empty();

private:
  std::queue<T>	_cmd;
  Mutex		_mutex;
};

template <typename T>
SafeQueue<T>::SafeQueue()
{

}

template <typename T>
void		SafeQueue<T>::push(T elem)
{
  _mutex.lock();
  _cmd.push(elem);
  _mutex.unlock();
}

template <typename T>
void		SafeQueue<T>::pop()
{
  _mutex.lock();
  _cmd.pop();
  _mutex.unlock();
}

template <typename T>
T		SafeQueue<T>::front()
{
  T		elem;

  _mutex.lock();
  elem = _cmd.front();
  _mutex.unlock();
  return (elem);
}

template <typename T>
std::size_t	SafeQueue<T>::size()
{
  std::size_t	size;

  _mutex.lock();
  size = _cmd.size();
  _mutex.unlock();
  return (size);
}

template <typename T>
bool		SafeQueue<T>::empty()
{
  bool		ret;

  _mutex.lock();
  ret = _cmd.empty();
  _mutex.unlock();
  return (ret);
}

template <typename T>
SafeQueue<T>::~SafeQueue()
{
}

#endif
