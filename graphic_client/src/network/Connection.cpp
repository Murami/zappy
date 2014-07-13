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
