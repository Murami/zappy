//
// ICallback.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/parser
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:05:13 2014 Manu
// Last update Sun Jul 13 23:05:13 2014 Manu
//

#ifndef		__ICALLBACK_HH__
# define	__ICALLBACK_HH__

# include	<list>
# include	<string>

namespace	Zappy
{
  class		ICallback
  {
  public :
    virtual void	setMapSize(int width, int height) = 0;
    virtual void	setCaseContent(int x, int y, int *res) = 0;
    virtual void	addTeamName(const std::string&) = 0;
    virtual void	addNewPlayer(int playerId, int x, int y,
				     int orientation, int level,
				     const std::string& teamName) = 0;
    virtual void	setPlayerPosition(int playerId, int x, int y,
					  int orientation) = 0;
    virtual void	changePlayerLevel(int playerId, int level) = 0;
    virtual void	playerStock(int playerId, int x, int y, int *res) = 0;
    virtual void	playerExpulse(int playerId) = 0;
    virtual void	playerBroadcast(int playerId) = 0;
    virtual void	playerStartCast(int playerId, int x, int y, int level,
					std::list<int> otherPlayersIds) = 0;
    virtual void	castEnd(int x, int y, int res) = 0;
    virtual void	playerLaysEgg(int playerId) = 0;
    virtual void	playerDropsResource(int playerId, int resourceId) = 0;
    virtual void	playerLootsResource(int playerId, int resourceId) = 0;
    virtual void	playerDies(int playerId) = 0;
    virtual void	eggLaidOnCaseByPlayer(int eggId, int playerId, int x,
					      int y) = 0;
    virtual void	eggOpens(int eggId) = 0;
    virtual void	playerConnectsForEgg(int eggId) = 0;
    virtual void	eggDies(int eggId) = 0;
    virtual void	setTimeUnit(int timeUnit) = 0;
    virtual void	endGame(const std::string& winnerTeam) = 0;
    virtual void	serverMessage(const std::string& message) = 0;
    virtual void	unknownCommand(const std::string& cmd) = 0;
    virtual void	badParameters(const std::string& params) = 0;
  };
}

#endif
