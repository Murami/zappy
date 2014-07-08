#ifndef		__ZAPPYGRAPHIC_HH__
# define	__ZAPPYGRAPHIC_HH__

# include	"objects/Stone.hh"
# include	"interface/Window.hh"
# include	"objects/Food.hh"

class		Client;

namespace	Zappy
{
  class		Map;
  class		World;

  class		ZappyGraphic
  {
  private :
    Window	_window;
    Map*	_map;
    Client&	_client;
    World*	_world;

    // pour test
    std::list<Stone*>	_stones;
    std::list<Player*>	_players;
    std::list<Food*>	_foods;

  private :
    void	_handleRightClickEvent();

  public :
    void	run();

  private :
    void	updateClient();

  public :
    ZappyGraphic(Client&);
    ~ZappyGraphic();
  };
}

#endif
