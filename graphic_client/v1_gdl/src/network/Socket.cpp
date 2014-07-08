//
// socket.cpp for socket in /home/desabr_q/Desktop/tmp/server
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Tue May 13 20:28:00 2014 quentin desabre
// Last update Sat Jul  5 10:14:37 2014 Desabre Quentin
//

#include "network/Socket.hh"

Socket::Socket()
{
  this->_fd = 0;
}

Socket::~Socket()
{

}

void		Socket::closeSocket()
{
  if (this->_fd != 0)
    close(this->_fd);
}

void		Socket::create(int port, const char *ip)
{
  this->_pe = getprotobyname("TCP");
  this->_fd = socket(AF_INET, SOCK_STREAM, this->_pe->p_proto);
  if (this->_fd == -1)
    std::cerr << "Error creating socket" << std::endl;
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_port = htons(port);
  if (ip == NULL)
    this->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    this->_sin.sin_addr.s_addr = inet_addr(ip);
}

void		Socket::bindSocket()
{
  int           ret;

  ret = bind(this->_fd,
             (const struct sockaddr *)&this->_sin,
             sizeof(this->_sin));
  if (ret == -1)
    {
      close(this->_fd);
      std::cerr << "Error binding socket" << std::endl;
    }
}

int		Socket::getFd() const
{
  return (this->_fd);
}

struct sockaddr_in &  		Socket::getSin()
{
  return (this->_sin);
}
