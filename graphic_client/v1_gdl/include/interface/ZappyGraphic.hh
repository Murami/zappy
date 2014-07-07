#ifndef		__ZAPPYGRAPHIC_HH__
# define	__ZAPPYGRAPHIC_HH__

# include	"interface/Window.hh"

namespace	Zappy
{
  class		Map;

  class		ZappyGraphic
  {
  private :
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
