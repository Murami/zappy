#ifndef		__ZAPPYGRAPHIC_HH__
# define	__ZAPPYGRAPHIC_HH__

# include	"network/Connection.hh"
# include	"interface/Window.hh"

namespace	Zappy
{
  class		Map;

  class		ZappyGraphic
  {
  private :
    Connection	_connection;
    Window	_window;
    Map*	_map;

  public :
    void	run();

  public :
    ZappyGraphic(int argc, char **argv);
    ~ZappyGraphic();
  };
}

#endif
