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
	  std::cerr << "\033[31mConnection to server "
	    "closed unexpectedly\033[0m" << std::endl;
	  return (NULL);
	}
      std::size_t nbLines = countLines(&buff[0]);
      ss << buff;
      std::vector<std::string> cmds;
      while (std::getline(ss, tmp))
	cmds.push_back(tmp);
      ss.clear();
      if (cmds.size() > nbLines)
	cmds.pop_back();
      std::memset(&buff[0], 0, 8192);
      strcpy(&buff[0], tmp.c_str());
      ndx = tmp.size();
      for (size_t s = 0; s < cmds.size(); s++)
      	client->getQueue().push(cmds[s]);
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
