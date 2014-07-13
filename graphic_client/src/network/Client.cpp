//
// Client.cpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/src/network
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:00:36 2014 Manu
// Last update Sun Jul 13 23:00:37 2014 Manu
//

#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include "network/Client.hh"

std::size_t		countLines(const char* str)
{
  std::size_t ret = 0;
  for (int i = 0; str[i]; i++)
    if (str[i] == '\n')
      ret++;
  return (ret);
}

void			*launchListen(void *attr)
{
  Client		*client;
  char			buff[8192];
  std::stringstream	ss;
  std::string		tmp;
  int			ndx = 0;

  client = reinterpret_cast<Client *>(attr);
  std::memset(&buff[0], 0, 8192);
  std::size_t ret = 0;
  if ((ret = read(client->_socket.getFd(), &buff[0], 8191)) == 0)
    {
      std::cerr << "\033[31mConnection to server "
	"closed unexpectedly\033[0m" << std::endl;
      return (NULL);
    }
  if (std::string(buff) == "BIENVENUE\n")
    {
      write(client->_socket.getFd(), "GRAPHIC\n", 8);
      std::memset(&buff[0], 0, 8192);
    }
  while (42)
    {
      if ((ret = read(client->_socket.getFd(), &buff[ndx], 8191 - ndx)) == 0)
	{
	  client->throwConnectionLost();
	  return (NULL);
	}
      std::size_t nbLines = countLines(&buff[0]);
      ss << buff;
      std::vector<std::string> cmds;
      while (std::getline(ss, tmp))
	{
	  std::cout << "BUFFER [" << tmp << "]" << std::endl;
	  cmds.push_back(tmp);
	}
      ss.clear();
      if (cmds.size() > nbLines)
	cmds.pop_back();
      std::memset(&buff[0], 0, 8192);
      strcpy(&buff[0], tmp.c_str());
      ndx = tmp.size();
      for (size_t s = 0; s < cmds.size(); s++)
      	client->getQueue().push(cmds[s]);
      if (client->haveToSendRequest())
      	client->resetRequest();
    }
  return (attr);
}

void			*launchWrite(void *attr)
{
  Client		*client;

  client = reinterpret_cast<Client *>(attr);
  while (1)
    {
      std::string input;
      std::getline(std::cin, input);
      input += '\n';
      write(client->_socket.getFd(), input.c_str(), input.size());
    }
  return (attr);
}

void			Client::resetRequest()
{
  _sendRequest = false;
  _request.clear();
}

bool			Client::isConnected() const
{
  return (_connected);
}

void			Client::throwWriteFailure()
{
  _connected = false;
}

void			Client::throwConnectionLost()
{
  _connected = false;
}

Client::Client(int argc, char **argv)
{
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
  pthread_create(&_thread, NULL, &launchListen, this);
  pthread_create(&_thread2, NULL, &launchWrite, this);
  _sendRequest = false;
}

std::string&		Client::getRequestToSend()
{
  return (_request);
}

bool			Client::haveToSendRequest() const
{
  return (_sendRequest);
}

void			Client::sendRequest(const std::string& request)
{
  _sendRequest = true;
  write(_socket.getFd(), request.c_str(), request.size());
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
    throw (std::runtime_error("Error while attempting to connect..."));
  _connected = true;
}

SafeQueue<std::string>&		Client::getQueue()
{
  return (_queue);
}
