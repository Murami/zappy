#ifndef		__CONNECTION_HH__
# define	__CONNECTION_HH__

# include	<iostream>
# include	<string>
# include	<sstream>
# include	<stdexcept>

namespace	Zappy
{
  class		Connection
  {
  private :
    int		_port;
    std::string	_ip;

  public :
    void	initialize(int argc, char **argv);

  public :
    Connection();
    ~Connection();
  };
}

#endif
