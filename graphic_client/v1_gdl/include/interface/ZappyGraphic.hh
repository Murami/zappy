#ifndef		__ZAPPYGRAPHIC_HH__
# define	__ZAPPYGRAPHIC_HH__

# include	"objects/Stone.hh"
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

    // pour test
    std::list<Stone*>	_stones;

  public :
    void	run();

  public :
    ZappyGraphic(int argc, char **argv);
    ~ZappyGraphic();
  };
}

#endif
