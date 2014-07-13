//
// Connection.cpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/src/network
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:00:30 2014 Manu
// Last update Sun Jul 13 23:00:31 2014 Manu
//

#include		"network/Connection.hh"

namespace	Zappy
{
  Connection::Connection()
  {
  }

  void		Connection::initialize(int argc, char **argv)
  {
    if (argc < 3)
      throw (std::runtime_error(std::string("Usage : ") + argv[0] + std::string(" <ip> <port>")));
    std::stringstream ss;
    ss << argv[2];
    ss >> _port;
    _ip = argv[1];
  }

  Connection::~Connection()
  {
  }
}
