#include		<iostream>
#include		<cstring>
#include		<unistd.h>
#include		"Connection.hh"
#include		"Monitor.hh"

namespace		graphic
{
  const boost::regex	Connection::REGEX[] =
    {
      boost::regex("msz*"), boost::regex("bct*"), boost::regex("tna*"),
      boost::regex("pnw*"), boost::regex("ppo*"), boost::regex("plv*"),
      boost::regex("pin*"), boost::regex("pex*"), boost::regex("pbc*"),
      boost::regex("pic*"), boost::regex("pie*"), boost::regex("pfk*"),
      boost::regex("pdr*"), boost::regex("pgt*"), boost::regex("pdi*"),
      boost::regex("enw*"), boost::regex("eht*"), boost::regex("ebo*"),
      boost::regex("edi*"), boost::regex("sgt*"), boost::regex("seg*"),
      boost::regex("smg*"), boost::regex("suc*"), boost::regex("sbp*")
    };

  void			Connection::getMapSize(const std::string & str)
  {
    int			x;
    int			y;
    std::stringstream	ss;
    std::string		width;
    std::string		height;
    ss << str;
    std::getline(ss, width, ' ');
    std::getline(ss, width, ' ');
    std::getline(ss, height, ' ');
    std::stringstream wss, hss;
    wss << width;
    hss << height;
    wss >> x;
    hss >> y;
    _monitor.setMapSizeX(x);
    _monitor.setMapSizeY(y);
  }

  void			Connection::getCaseContent(const std::string & str)
  {
    std::cout << "getCaseContent : " << str;
  }

  void			Connection::getTeamName(const std::string&)
  {
    //std::cout << "getTeamName" << std::endl;
  }

  void			Connection::getTimeUnit(const std::string&)
  {
    //std::cout << "getTimeUnit" << std::endl;
  }

  void			Connection::_createRegexFuncMap()
  {
    regexFunc[REGEX[0]] = &Connection::getMapSize;
    regexFunc[REGEX[1]] = &Connection::getCaseContent;
    regexFunc[REGEX[2]] = &Connection::getTeamName;
    regexFunc[REGEX[3]] = &Connection::getMapSize;
    regexFunc[REGEX[4]] = &Connection::getMapSize;
    regexFunc[REGEX[5]] = &Connection::getMapSize;
    regexFunc[REGEX[6]] = &Connection::getMapSize;
    regexFunc[REGEX[7]] = &Connection::getMapSize;
    regexFunc[REGEX[8]] = &Connection::getMapSize;
    regexFunc[REGEX[9]] = &Connection::getMapSize;
    regexFunc[REGEX[10]] = &Connection::getMapSize;
    regexFunc[REGEX[11]] = &Connection::getMapSize;
    regexFunc[REGEX[12]] = &Connection::getMapSize;
    regexFunc[REGEX[13]] = &Connection::getMapSize;
    regexFunc[REGEX[14]] = &Connection::getMapSize;
    regexFunc[REGEX[15]] = &Connection::getMapSize;
    regexFunc[REGEX[16]] = &Connection::getMapSize;
    regexFunc[REGEX[17]] = &Connection::getMapSize;
    regexFunc[REGEX[18]] = &Connection::getMapSize;
    regexFunc[REGEX[19]] = &Connection::getTimeUnit;
    regexFunc[REGEX[20]] = &Connection::getMapSize;
    regexFunc[REGEX[21]] = &Connection::getMapSize;
    regexFunc[REGEX[22]] = &Connection::getMapSize;
    regexFunc[REGEX[23]] = &Connection::getMapSize;
  }

  Connection::Connection(int argc, char *argv[], Monitor& m) : _monitor(m)
  {
    if (argc < 3)
      throw (std::runtime_error(std::string("Usage : ") +
				std::string(argv[0]) +
				std::string(" <ip> <port>")));
    std::stringstream ss;
    ss << argv[2];
    ss >> _port;
    _ip = argv[1];
    _createRegexFuncMap();
  }

  void			*readOnSocket(void *data)
  {
    Connection*		connection = reinterpret_cast<Connection*>(data);
    char		buffer[2];
    std::size_t		size = 1;
    std::string		str;

    str.clear();
    while (size && connection->getServer().IsValid())
      {
	bzero(buffer, 2);
	connection->getServer().Receive(&buffer[0], 1, size);
	str.append(buffer);
	if (buffer[0] == '\n')
	  {
	    for (int i = 0; i < 24; i++)
	      {
		if (boost::regex_search(str, Connection::REGEX[i]))
		  {
		    (connection->*connection->regexFunc[Connection::REGEX[i]])(str);
		    break;
		  }
	      }
	    str.clear();
	  }
      }
    return (connection);
  }

  sf::SocketTCP&	Connection::getServer()
  {
    return (_server);
  }

  void			Connection::start()
  {
    char		buffer[4096];
    std::size_t		readSize;

    bzero(buffer, 4096);
    if (_server.Connect(_port, _ip) != sf::Socket::Done)
      {
	throw (std::runtime_error("Could not connect to server"));
      }
    _server.Receive(buffer, 4096, readSize);
    _server.Send("GRAPHIC\n", 8);
    pthread_create(&_thread, NULL, readOnSocket, this);
  }

  Connection::~Connection()
  {
  }
}
