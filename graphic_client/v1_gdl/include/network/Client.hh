//
// client.hh for client in /home/desabr_q/Desktop/tmp/server
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Tue May 13 18:35:03 2014 quentin desabre
// Last update Mon Jul  7 17:14:23 2014 Desabre Quentin
//

#ifndef				_CLIENT_HH_
# define			_CLIENT_HH_

# include			<string>
# include			<SFML/Network.hpp>
# include			"network/Socket.hh"
# include			"network/SafeQueue.hpp"

class				Client
{
public:
  Client(int ac, char **av);
  ~Client();

  void				connectServer();
  SafeQueue<std::string>& 	getQueue();

public:
  Socket			_socket;
  SafeQueue<std::string>       	_queue;
};

#endif			/* _CLIENT_HH_ */
