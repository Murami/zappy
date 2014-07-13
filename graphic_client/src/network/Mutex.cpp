#include <iostream>
#include <cstring>
#include <stdexcept>
#include "network/Mutex.hh"

Mutex::Mutex()
{
  std::memset(&this->_mutex, 0, sizeof(pthread_mutex_t));
}

Mutex::~Mutex()
{

}

void			Mutex::lock()
{
  try
    {
      if (pthread_mutex_lock(&this->_mutex) != 0)
	throw (std::runtime_error("Mutex lock failed"));
    }
  catch (std::runtime_error e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void			Mutex::unlock()
{
  try
    {
      if (pthread_mutex_unlock(&this->_mutex) != 0)
	throw (std::runtime_error("Mutex unlock failed"));
    }
  catch (std::runtime_error e)
    {
      std::cerr << e.what() << std::endl;
    }
}

bool			Mutex::trylock()
{
  return (pthread_mutex_trylock(&this->_mutex));
}
