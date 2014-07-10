#include		<GL/glew.h>
#include		<GL/glut.h>
#include		"objects/Map.hh"
#include		"objects/Player.hh"
#include		"interface/ZappyGraphic.hh"
#include		"interface/Camera.hh"
#include		"network/Client.hh"
#include		"objects/PlayerFactory.hpp"
#include		"objects/World.hh"
#include		"objects/Egg.hh"
#include		"parser/Parser.hh"

namespace	Zappy
{
  ZappyGraphic::ZappyGraphic(Client& client) : _client(client)
  {
    _parser = new Parser(this);
    _map = NULL;
  }

  void		ZappyGraphic::updateClient()
  {
    while (_client.getQueue().size())
      {
    	std::string cmd(_client.getQueue().front());
	_parser->execCommand(cmd);
    	_client.getQueue().pop();
      }
  }

  void		ZappyGraphic::run()
  {
    _window.create(Window::WIDTH, Window::HEIGHT, Window::TITLE);
    updateClient();

    _world = new World();
    _world->initialize();

    while (_window.isRunning())
      {
	_window.bindShader();
	_window.update();
	updateClient();

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  _window.drawPlayerColorMap(static_cast<Player*>(*it));
	_handleRightClickEvent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_window.bindShader();
	_window.draw(_world);

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  _window.draw(*it);

	//drawOnlyOne*()
	_drawOnlyOneStone();
	_drawOnlyOneFood();

	// for (std::list<Stone*>::iterator it = _stones.begin();
	//      it != _stones.end(); it++)
	//   _window.draw(*it);

	// for (std::list<Egg*>::iterator it = _eggs.begin();
	//      it != _eggs.end(); it++)
	//   _window.draw(*it);

	_window.draw(_map);
	_window.flush();
      }
  }

  void		ZappyGraphic::_drawOnlyOneStone()
  {

    std::list<Stone*> tmp;
    bool yetInList = false;
    for (std::list<Stone*>::iterator it = _stones.begin();
    	 it != _stones.end(); it++)
      {
    	yetInList = false;
    	std::list<Stone*>::iterator it2;
    	for (it2 = tmp.begin();
    	     it2 != tmp.end(); it2++)
    	  {
    	    if ((*it2)->getPosition().x == (*it)->getPosition().x &&
    		(*it2)->getPosition().y == (*it)->getPosition().y &&
		(*it2)->getType() == (*it)->getType())
    	      {
    		yetInList = true;
    		break;
    	      }
    	  }
    	if (!yetInList && _stones.size())
    	  tmp.push_back(*it);
      }
    for (std::list<Stone*>::iterator it = tmp.begin();
    	 it != tmp.end(); it++)
      _window.draw(*it);
  }

  void		ZappyGraphic::_drawOnlyOneFood()
  {
    std::list<Food*> tmp;
    bool yetInList = false;
    for (std::list<Food*>::iterator it = _foods.begin();
    	 it != _foods.end(); it++)
      {
    	yetInList = false;
    	std::list<Food*>::iterator it2;
    	for (it2 = tmp.begin();
    	     it2 != tmp.end(); it2++)
    	  {
    	    if ((*it2)->getX() == (*it)->getX() &&
    		(*it2)->getY() == (*it)->getY())
    	      {
    		yetInList = true;
    		break;
    	      }
    	  }
    	if (!yetInList)
    	  tmp.push_back(*it);
      }
    for (std::list<Food*>::iterator it = tmp.begin();
    	 it != tmp.end(); it++)
      _window.draw(*it);
  }

  void		ZappyGraphic::_handleRightClickEvent()
  {
    gdl::Input	input = _window.getInputs();
    unsigned char pixel[4];
    pixel[0] = pixel[1] = pixel[2] = pixel[3] = 0;
    if (input.getKey(SDL_BUTTON_RIGHT))
      {
	glReadPixels(input.getMousePosition().x,
		     Window::HEIGHT - input.getMousePosition().y,
		     1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel[0]);

	glm::vec4 clickedColor(pixel[0] / 255,
			       pixel[1] / 255,
			       pixel[2] / 255, 0);

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  {
	    if ((*it)->getPickColor().r == clickedColor.r &&
		(*it)->getPickColor().g == clickedColor.g &&
		(*it)->getPickColor().b == clickedColor.b)
	      // CALLBACK POUR AFFICHAGE HUD D'UN JOUEUR
	      std::cout << "[CLICK] : player on " << (*it)->getRealPosition().x << " " << (*it)->getRealPosition().y << std::endl;
	  }
      }
  }

  void		ZappyGraphic::setMapSize(int width, int height)
  {
    if (!_map)
      _map = new Map(width, height);
    _map->setSize(width, height);
    _map->initialize();
    _window.getCamera()->setPosition(glm::vec2(width / 2, height / 2));
  }

  int		ZappyGraphic::_getFoodAtCase(int x, int y)
  {
    int		res = 0;
    for (std::list<Food*>::iterator it = _foods.begin();
	 it != _foods.end(); it++)
      {
	if ((*it)->getX() == x && (*it)->getY() == y)
	  res++;
      }
    return (res);
  }

  void		ZappyGraphic::_removeFoodAtCase(int x, int y)
  {
    for (std::list<Food*>::iterator it = _foods.begin();
	 it != _foods.end(); it++)
      {
	if ((*it)->getPosition().x == x && (*it)->getPosition().y == y)
	  {
	    _foods.remove(*it);
	    break;
	  }
      }
  }

  int		ZappyGraphic::_getStoneByTypeAtCase(int x, int y, Type type)
  {
    int		res = 0;
    for (std::list<Stone*>::iterator it = _stones.begin();
	 it != _stones.end(); it++)
      {
	if ((*it)->getPosition().x == x &&
	    (*it)->getPosition().y == y &&
	    (*it)->getType() == type)
	  res++;
      }
    return (res);
  }

  void		ZappyGraphic::_removeStoneByTypeAtCase(int x, int y, Type type)
  {
    for (std::list<Stone*>::iterator it = _stones.begin();
	 it != _stones.end(); it++)
      {
	if ((*it)->getPosition().x == x &&
	    (*it)->getPosition().y == y &&
	    (*it)->getType() == type)
	  {
	    _stones.remove(*it);
	    break;
	  }
      }
  }

  void		ZappyGraphic::setCaseContent(int x, int y, int* resources)
  {
    for (int i = 0; i < resources[0]; i++)
      {
	int foodAtCase = _getFoodAtCase(x, y);
	if (resources[0] > foodAtCase)
	  while (resources[0] > _getFoodAtCase(x, y))
	    {
	      Food* food = new Food(x, y);
	      food->initialize();
	      _foods.push_back(food);
	    }
	// Ne sais pas si marche a test avec IA
	// else if (resources[0] < foodAtCase)
	//   while (resources[0] < _getFoodAtCase(x, y))
	//     _removeFoodAtCase(x, y);
      }

    // int t = 0;
    // for (int res = 1; res < 7; res++)
    //   {
    // 	for (int nb = 0; nb < resources[res]; nb++)
    // 	  {
    // 	    int stone = _getStoneByTypeAtCase(x, y, static_cast<Type>(t));
    // 	    if (resources[res] > stone)
    // 	      while (resources[res] > _getStoneByTypeAtCase(x, y, static_cast<Type>(t)))
    // 		{
    // 		  Stone* stone = new Stone(static_cast<Type>(t), glm::vec2(x, y));
    // 		  stone->initialize();
    // 		  _stones.push_back(stone);
    // 		}
    // 	    else if (resources[res] > stone)
    // 	      while(resources[res] > _getStoneByTypeAtCase(x, y, static_cast<Type>(t)))
    // 		_removeStoneByTypeAtCase(x, y, static_cast<Type>(t));
    // 	  }
    // 	t++;
    //   }

  }

  void		ZappyGraphic::addTeamName(const std::string&)
  {
  }

  void		ZappyGraphic::addNewPlayer(int playerId, int x , int y,
					   int orientation, int level,
					   const std::string& teamName)
  {
    Player *player = PlayerFactory::createNewPlayer(playerId, x, y,
						    orientation, level,
						    teamName);
    player->initialize();
    _players.push_back(player);
  }

  void		ZappyGraphic::setPlayerPosition(int playerId, int newX,
						int newY, int orientation)
  {
    for (std::list<Player*>::iterator it = _players.begin();
	 it != _players.end(); it++)
      {
	if ((*it)->getId() == playerId)
	  {
	    (*it)->setPosition(newX, newY);
	    (*it)->setOrientation(static_cast<Direction>(orientation));
	    break;
	  }
      }
  }

  void		ZappyGraphic::changePlayerLevel(int, int)
  {
  }

  void		ZappyGraphic::playerStock(int, int, int, int*)
  {
  }

  void		ZappyGraphic::playerExpulse(int)
  {
  }

  void		ZappyGraphic::playerBroadcast(int)
  {
  }

  void		ZappyGraphic::playerStartCast(int, int, int, int, std::list<int>)
  {
  }

  void		ZappyGraphic::castEnd(int, int, int)
  {
  }

  void		ZappyGraphic::playerLaysEgg(int)
  {
  }

  void		ZappyGraphic::playerDropsResource(int, int)
  {
  }

  void		ZappyGraphic::playerLootsResource(int, int)
  {
  }

  void		ZappyGraphic::playerDies(int)
  {
  }

  void		ZappyGraphic::eggLaidOnCaseByPlayer(int, int, int, int)
  {
  }

  void		ZappyGraphic::eggOpens(int)
  {
  }

  void		ZappyGraphic::playerConnectsForEgg(int)
  {
  }

  void		ZappyGraphic::eggDies(int)
  {
  }

  void		ZappyGraphic::setTimeUnit(int timeUnit)
  {
    _timeUnit = timeUnit;
  }

  void		ZappyGraphic::endGame(const std::string&)
  {
  }

  void		ZappyGraphic::serverMessage(const std::string&)
  {
  }

  void		ZappyGraphic::unknownCommand(const std::string&)
  {
  }

  void		ZappyGraphic::badParameters(const std::string&)
  {
  }

  ZappyGraphic::~ZappyGraphic()
  {
  }
}
