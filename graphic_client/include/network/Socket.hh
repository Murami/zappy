//
// socket.hh for socket in /home/desabr_q/Desktop/tmp/server
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Tue May 13 20:27:54 2014 quentin desabre
// Last update Sat Jul  5 10:15:00 2014 Desabre Quentin
//

#ifndef		_SOCKET_HH_
# define	_SOCKET_HH_

# include	<arpa/inet.h>
# include	<netdb.h>
# include	<sys/socket.h>
# include	<unistd.h>
# include	<iostream>

class		Socket
{
 public:
  Socket();
  ~Socket();

  void				create(int, const char *);
  void				bindSocket();
  void				closeSocket();
  int				getFd() const;
  struct sockaddr_in&		getSin();

private:
  int				_fd;
  struct protoent*		_pe;
  struct sockaddr_in		_sin;

};
#endif
