#ifndef		__ZAPPYGRAPHIC_HH__
# define	__ZAPPYGRAPHIC_HH__

# include	"parser/ICallback.hh"
# include	"objects/Stone.hh"
# include	"interface/Window.hh"
# include	"objects/Food.hh"

class		Client;

namespace	Zappy
{
  class		Map;
  class		World;
  class		Egg;
  class		Parser;

  class		ZappyGraphic : public ICallback
  {
  private :
    Window	_window;
    Map*	_map;
    Client&	_client;
    World*	_world;
    Parser*	_parser;
    int		_timeUnit;

    // pour test
    std::list<Stone*>	_stones;
    std::list<Player*>	_players;
    std::list<Food*>	_foods;
    std::list<Egg*>	_eggs;

  private :
    void	_handleRightClickEvent();

  public :
    void	run();

  private :
    void	updateClient();

  public :
    virtual void	setMapSize(int width, int height);
    virtual void	setCaseContent(int x, int y, int *res);
    virtual void	addTeamName(const std::string&);
    virtual void	addNewPlayer(int playerId, int x, int y,
				     int orientation, int level,
				     const std::string& teamName);
    virtual void	setPlayerPosition(int playerId, int x, int y,
					  int orientation);
    virtual void	changePlayerLevel(int playerId, int level);
    virtual void	playerStock(int playerId, int x, int y, int *res);
    virtual void	playerExpulse(int playerId);
    virtual void	playerBroadcast(int playerId);
    virtual void	playerStartCast(int playerId, int x, int y, int level,
					std::list<int> otherPlayersIds);
    virtual void	castEnd(int x, int y, int res);
    virtual void	playerLaysEgg(int playerId);
    virtual void	playerDropsResource(int playerId, int resourceId);
    virtual void	playerLootsResource(int playerId, int resourceId);
    virtual void	playerDies(int playerId);
    virtual void	eggLaidOnCaseByPlayer(int eggId, int playerId, int x,
					      int y);
    virtual void	eggOpens(int eggId);
    virtual void	playerConnectsForEgg(int eggId);
    virtual void	eggDies(int eggId);
    virtual void	setTimeUnit(int timeUnit);
    virtual void	endGame(const std::string& winnerTeam);
    virtual void	serverMessage(const std::string& message);
    virtual void	unknownCommand(const std::string& cmd);
    virtual void	badParameters(const std::string& params);

  public :
    ZappyGraphic(Client&);
    ~ZappyGraphic();
  };
}

#endif
