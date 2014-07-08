
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include "network/Client.hh"

void			*launchListen(void *attr)
{
  Client		*client;
  char			buff[8192];

  client = reinterpret_cast<Client *>(attr);
  while (42)
    {
      std::memset(buff, 0, 8192);
      read(client->_socket.getFd(), buff, 4096);
      client->getQueue().push(std::string(buff));
      std::cout << client->getQueue().front();
      client->getQueue().pop();
      // std::cout << buff;
    }
  return (attr);
}

void			*launchWrite(void *attr)
{
  std::string		input;
  Client		*client;

  client = reinterpret_cast<Client *>(attr);
  while (1)
    {
      std::cin >> input;
      std::cout << input << std::endl;
      write(client->_socket.getFd(), input.c_str(), input.size());
    }
  return (attr);
}

Client::Client(int argc, char **argv)
{
  pthread_t		thread;
  pthread_t		thread2;
  std::stringstream	ss;
  std::string		ip;
  int			port;

  if (argc < 3)
    throw (std::runtime_error(std::string("Usage : ") +
			      argv[0] + std::string(" <ip> <port>")));
  ss << argv[2];
  ss >> port;
  ip = argv[1];
  _socket.create(port, ip.c_str());
  this->connectServer();
  pthread_create(&thread, NULL, &launchListen, this);
  pthread_create(&thread2, NULL, &launchWrite, this);
}

Client::~Client()
{
  close(this->_socket.getFd());
}

void				Client::connectServer()
{
  int				ret;

  std::cout <<  "socket client " << _socket.getFd() << std::endl;
  ret = connect(this->_socket.getFd(),
  	  (const struct sockaddr *)&this->_socket.getSin(),
  	  sizeof(this->_socket.getSin()));
  if (ret == -1)
    std::cerr << "Error Connect" << std::endl;
}

SafeQueue<std::string>&		Client::getQueue()
{
  return (_queue);
}
