#ifndef		__CONNECTION_HH__
# define	__CONNECTION_HH__

# include	<sstream>
# include	<map>
# include	<SFML/Network.hpp>
# include	<netinet/in.h>
# include	<arpa/inet.h>
# include	<fcntl.h>
# include	<netdb.h>
# include	<sstream>
# include	<pthread.h>
# include	<stdexcept>
# include	<boost/regex.hpp>

namespace	graphic
{
  class		Monitor;

  class		Connection
  {
  public :
    const static boost::regex	REGEX[24];

  private :
    Monitor&		_monitor;
    pthread_t		_thread;
    int			_port;
    std::string		_ip;
    sf::SocketTCP	_server;

  private :
    void		_createRegexFuncMap();

  public :
    std::map<boost::regex, void (Connection::*)(const std::string&)> regexFunc;

  public :
    void		getMapSize(const std::string&);
    void		getCaseContent(const std::string&);
    void		getTeamName(const std::string&);
    void		getTimeUnit(const std::string&);

  public :
    void	start();

  public :
    sf::SocketTCP&	getServer();

  public :
    Connection(int, char **, Monitor&);
    ~Connection();
  };

  void			*readOnSocket(void *);
}

#endif
