//
// client.hh for client in /home/desabr_q/Desktop/tmp/server
//
// Made by quentin desabre
// Login   <desabr_q@epitech.net>
//
// Started on  Tue May 13 18:35:03 2014 quentin desabre
// Last update Fri Jul 11 04:07:15 2014 Manu
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

public :
  void				connectServer();
  SafeQueue<std::string>& 	getQueue();
  void				sendRequest(const std::string& request);
  bool				haveToSendRequest() const;
  std::string&			getRequestToSend();
  void				resetRequest();

public :
  void				throwWriteFailure();
  void				throwConnectionLost();

public:
  Socket			_socket;
  SafeQueue<std::string>       	_queue;

private :
  bool		_sendRequest;
  std::string	_request;
};

#endif			/* _CLIENT_HH_ */
