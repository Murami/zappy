#include		<sstream>
#include		<iostream>
#include		"parser/ICallback.hh"
#include		"parser/Parser.hh"

namespace	Zappy
{
  Parser::Parser(ICallback* callback)
  {
    _callback = callback;
    _initMap();
  }

  void		Parser::execCommand(const std::string& cmd)
  {
    std::string	func;
    std::map<std::string, void (Parser::*)(const std::string&)>::iterator it;
    std::map<std::string, void (Parser::*)(const std::string&)>::key_compare compMap = _funcMap.key_comp();
    it = _funcMap.begin();
    std::string last = _funcMap.rbegin()->first;
    do
      {
	if (cmd.find(it->first) != std::string::npos)
	  (this->*this->_funcMap[it->first])(std::string(&cmd.c_str()[(cmd.size() > 4 ? 4 : 0)]));
      } while (compMap((*it++).first, last));
  }

  void		Parser::_initMap()
  {
    _funcMap["msz"] = &Parser::setMapSize;
    _funcMap["bct"] = &Parser::setCaseContent;
    _funcMap["tna"] = &Parser::addTeamName;
    _funcMap["pnw"] = &Parser::addNewPlayer;
    _funcMap["ppo"] = &Parser::setPlayerPosition;
    _funcMap["plv"] = &Parser::changePlayerLevel;
    _funcMap["pin"] = &Parser::playerStock;
    _funcMap["pex"] = &Parser::playerExpulse;
    _funcMap["pbc"] = &Parser::playerBroadcast;
    _funcMap["pic"] = &Parser::playerStartCast;
    _funcMap["pie"] = &Parser::castEnd;
    _funcMap["pfk"] = &Parser::playerLaysEgg;
    _funcMap["pdr"] = &Parser::playerDropsResource;
    _funcMap["pgt"] = &Parser::playerLootsResource;
    _funcMap["pdi"] = &Parser::playerDies;
    _funcMap["enw"] = &Parser::eggLaidOnCaseByPlayer;
    _funcMap["eht"] = &Parser::eggOpens;
    _funcMap["ebo"] = &Parser::playerConnectsForEgg;
    _funcMap["edi"] = &Parser::eggDies;
    _funcMap["sgt"] = &Parser::setTimeUnit;
    _funcMap["seg"] = &Parser::endGame;
    _funcMap["smg"] = &Parser::serverMessage;
    _funcMap["suc"] = &Parser::unknownCommand;
    _funcMap["sbp"] = &Parser::badParameters;
  }

  void		Parser::setMapSize(const std::string& args)
  {
    std::stringstream	mainSS;
    std::stringstream	nb;
    std::string		tmp;
    int			x = 0;
    int			y = 0;

    mainSS << args;
    if (std::getline(mainSS, tmp, ' '))
      {
    	nb << tmp;
    	nb >> x;
      }
    nb.clear();
    if (std::getline(mainSS, tmp, ' '))
      {
    	nb << tmp;
    	nb >> y;
      }
    _callback->setMapSize(x, y);
  }

  void		Parser::setCaseContent(const std::string& args)
  {
    std::stringstream	ss;
    std::stringstream	sstmp;
    std::string		tmp;
    int			resources[7];
    int			x = 0, y = 0;
    int			i = 0, j = 0;

    ss << args;
    while (std::getline(ss, tmp, ' '))
      {
    	sstmp << tmp;
    	if (i == 0)
    	  sstmp >> x;
    	else if (i == 1)
    	  sstmp >> y;
    	else
    	  sstmp >> resources[j++];
    	sstmp.clear();
    	i++;
    	if (j == 7)
    	  break;
      }
    _callback->setCaseContent(x, y, &resources[0]);
  }

  void		Parser::addTeamName(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::addNewPlayer(const std::string& args)
  {
    std::stringstream	ss;
    std::stringstream	ssTmp;
    std::string		tmp;
    int			tab[5];
    int			i = 0;

    ss << args;
    while (std::getline(ss, tmp, ' '))
      {
    	ssTmp << tmp;
    	ssTmp >> tab[i];
    	ssTmp.clear();
    	i++;
    	if (i == 4)
    	  break;
      }
    _callback->addNewPlayer(tab[0], tab[1], tab[2], tab[3], tab[4], tmp);
  }

  void		Parser::setPlayerPosition(const std::string& args)
  {
    // PPO n x y o
    std::stringstream ss;
    std::stringstream sstmp;
    std::string	tmp;
    int		tab[4];
    int		i = 0;

    ss << args;
    while (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> tab[i];
	sstmp.clear();
	i++;
	if (i == 4)
	  break;
      }
    _callback->setPlayerPosition(tab[0], tab[1], tab[2], tab[3]);
  }

  void		Parser::changePlayerLevel(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerStock(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerExpulse(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerBroadcast(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerStartCast(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::castEnd(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerLaysEgg(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerDropsResource(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerLootsResource(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerDies(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::eggLaidOnCaseByPlayer(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::eggOpens(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::playerConnectsForEgg(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::eggDies(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::setTimeUnit(const std::string& args)
  {
    std::stringstream	ss;
    int		time;

    ss << args;
    ss >> time;
    _callback->setTimeUnit(time);
  }

  void		Parser::endGame(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::serverMessage(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::unknownCommand(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  void		Parser::badParameters(const std::string& args)
  {
    //std::cout << __FUNCTION__ << ": \"" << args << "\"" << std::endl;
  }

  Parser::~Parser()
  {
  }
}
