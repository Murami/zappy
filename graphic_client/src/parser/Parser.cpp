//
// Parser.cpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/src/parser
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:02:27 2014 Manu
// Last update Sun Jul 13 23:02:28 2014 Manu
//

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
    _callback->addTeamName(args);
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
    	if (i == 6)
    	  break;
      }
    _callback->addNewPlayer(tab[0], tab[1], tab[2], tab[3], tab[4], tmp);
  }

  void		Parser::setPlayerPosition(const std::string& args)
  {
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
    std::stringstream ss;
    std::stringstream sstmp;
    std::string tmp;
    int	id = 0, level = 0;

    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> level;
      }
    _callback->changePlayerLevel(id, level);
  }

  void		Parser::playerStock(const std::string& args)
  {
    std::stringstream	ss;
    std::stringstream	sstmp;
    std::string		tmp;
    int			resources[7];
    int			x = 0, y = 0, id = 0;
    int			i = 0, j = 0;

    ss << args;
    while (std::getline(ss, tmp, ' '))
      {
    	sstmp << tmp;
    	if (i == 0)
    	  sstmp >> id;
    	else if (i == 1)
    	  sstmp >> x;
	else if (i == 2)
	  sstmp >> y;
    	else
    	  sstmp >> resources[j++];
    	sstmp.clear();
    	i++;
      }
    _callback->playerStock(id, x, y, &resources[0]);
  }

  void		Parser::playerExpulse(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	_callback->playerExpulse(id);
      }
  }

  void		Parser::playerBroadcast(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	_callback->playerBroadcast(id);
      }
  }

  void		Parser::playerStartCast(const std::string& args)
  {
    std::stringstream ss;
    std::stringstream sstmp;
    std::string tmp;
    ss << args;
    int x = 0, y = 0, level = 0, id = 0, i = 0;
    std::list<int> list;
    while (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	if (i == 0)
	  sstmp >> x;
	else if (i == 1)
	  sstmp >> y;
	else if (i == 2)
	  sstmp >> level;
	else if (i == 3)
	  sstmp >> id;
	else
	  {
	    int j;
	    sstmp >> j;
	    list.push_back(j);
	  }
	sstmp.clear();
	i++;
      }
    _callback->playerStartCast(id, x, y, level, list);
  }

  void		Parser::castEnd(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int x = 0, y = 0, r = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> x;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> y;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> r;
	sstmp.clear();
      }
    _callback->castEnd(x, y, r);
  }

  void		Parser::playerLaysEgg(const std::string& args)
  {
    std::stringstream ss;
    std::stringstream sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	_callback->playerLaysEgg(id);
      }
  }

  void		Parser::playerDropsResource(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int playerId, resId;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> playerId;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> resId;
	_callback->playerDropsResource(playerId, resId);
      }
  }

  void		Parser::playerLootsResource(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int playerId, resId;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> playerId;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> resId;
	_callback->playerLootsResource(playerId, resId);
      }
  }

  void		Parser::playerDies(const std::string& args)
  {
    std::stringstream	ss;
    int		nb;

    ss << args;
    ss >> nb;
    _callback->playerDies(nb);
  }

  void		Parser::eggLaidOnCaseByPlayer(const std::string& args)
  {
    int eggId = 0, playerId = 0, x = 0, y = 0;
    std::stringstream ss, sstmp;
    std::string tmp;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> eggId;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> playerId;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> x;
	sstmp.clear();
      }
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> y;
	sstmp.clear();
      }
    _callback->eggLaidOnCaseByPlayer(eggId, playerId, x, y);
  }

  void		Parser::eggOpens(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	_callback->eggOpens(id);
      }
  }

  void		Parser::playerConnectsForEgg(const std::string& args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	_callback->playerConnectsForEgg(id);
      }
  }

  void		Parser::eggDies(const std::string & args)
  {
    std::stringstream ss, sstmp;
    std::string tmp;
    int id = 0;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	sstmp << tmp;
	sstmp >> id;
	_callback->eggDies(id);
      }
  }

  void		Parser::setTimeUnit(const std::string& args)
  {
    std::stringstream	ss;
    int		time;

    ss << args;
    ss >> time;
    _callback->setTimeUnit(time);
  }

  void		Parser::endGame(const std::string & args)
  {
    std::stringstream ss;
    std::string tmp;
    ss << args;
    if (std::getline(ss, tmp, ' '))
      {
	_callback->endGame(tmp);
      }
  }

  void		Parser::serverMessage(const std::string& args)
  {
    _callback->serverMessage(args);
  }

  void		Parser::unknownCommand(const std::string& args)
  {
    _callback->unknownCommand(args);
  }

  void		Parser::badParameters(const std::string& args)
  {
    _callback->badParameters(args);
  }

  Parser::~Parser()
  {
  }
}
