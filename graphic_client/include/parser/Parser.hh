//
// Parser.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/parser
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:05:10 2014 Manu
// Last update Sun Jul 13 23:05:11 2014 Manu
//

#ifndef		__PARSER_HH__
# define	__PARSER_HH__

# include	<map>

namespace	Zappy
{
  class		ICallback;

  class		Parser
  {
  private :
    ICallback*							_callback;
    std::map<std::string, void (Parser::*)(const std::string&)>	_funcMap;

  private :
    void	_initMap();

  public :
    void	setMapSize(const std::string& args);
    void	setCaseContent(const std::string& args);
    void	addTeamName(const std::string& args);
    void	addNewPlayer(const std::string& args);
    void	setPlayerPosition(const std::string& args);
    void	changePlayerLevel(const std::string& args);
    void	playerStock(const std::string& args);
    void	playerExpulse(const std::string&);
    void	playerBroadcast(const std::string&);
    void	playerStartCast(const std::string&);
    void	castEnd(const std::string& args);
    void	playerLaysEgg(const std::string& args);
    void	playerDropsResource(const std::string& args);
    void	playerLootsResource(const std::string& args);
    void	playerDies(const std::string& args);
    void	eggLaidOnCaseByPlayer(const std::string& args);
    void	eggOpens(const std::string& args);
    void	playerConnectsForEgg(const std::string& args);
    void	eggDies(const std::string& args);
    void	setTimeUnit(const std::string& args);
    void	endGame(const std::string& args);
    void	serverMessage(const std::string& args);
    void	unknownCommand(const std::string& args);
    void	badParameters(const std::string& args);

  public :
    void	execCommand(const std::string&);

  public :
    Parser(ICallback*);
    ~Parser();
  };
}

#endif
