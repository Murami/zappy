#include		"objects/Map.hh"
#include		"objects/Player.hh"
#include		"interface/ZappyGraphic.hh"
#include		"interface/Camera.hh"
#include		"network/Client.hh"
#include		"objects/PlayerFactory.hpp"
#include		"objects/EggFactory.hpp"
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
    AnimationPool::getInstance()->loadModels();
    _hud = new HUD();
    updateClient();
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
	_window.updatePlayers(_players);
	for (std::list<Stone*>::iterator it = _stones.begin();
	     it != _stones.end(); it++)
	  _window.draw(*it);
	for (std::list<Food*>::iterator it = _foods.begin();
	     it != _foods.end(); it++)
	  _window.draw(*it);

	// _drawOnlyOneStone();
	// _drawOnlyOneFood();

	for (std::list<Egg*>::iterator it = _eggs.begin();
	     it != _eggs.end(); it++)
	  _window.draw(*it);

	_window.drawMap(_map);
	_hud->draw();
	_window.flush();
      }
  }

  // void		ZappyGraphic::_drawOnlyOneStone()
  // {

  //   std::list<Stone*> tmp;
  //   bool yetInList = false;
  //   for (std::list<Stone*>::iterator it = _stones.begin();
  //   	 it != _stones.end(); it++)
  //     {
  //   	yetInList = false;
  //   	std::list<Stone*>::iterator it2;
  //   	for (it2 = tmp.begin();
  //   	     it2 != tmp.end(); it2++)
  //   	  {
  //   	    if ((*it2)->getPosition().x == (*it)->getPosition().x &&
  //   		(*it2)->getPosition().y == (*it)->getPosition().y &&
  // 		(*it2)->getType() == (*it)->getType())
  //   	      {
  //   		yetInList = true;
  //   		break;
  //   	      }
  //   	  }
  //   	if (!yetInList && _stones.size())
  //   	  tmp.push_back(*it);
  //     }
  //   for (std::list<Stone*>::iterator it = tmp.begin();
  //   	 it != tmp.end(); it++)
  //     _window.draw(*it);
  // }

  // void		ZappyGraphic::_drawOnlyOneFood()
  // {
  //   std::list<Food*> tmp;
  //   bool yetInList = false;
  //   for (std::list<Food*>::iterator it = _foods.begin();
  //   	 it != _foods.end(); it++)
  //     {
  //   	yetInList = false;
  //   	std::list<Food*>::iterator it2;
  //   	for (it2 = tmp.begin();
  //   	     it2 != tmp.end(); it2++)
  //   	  {
  //   	    if ((*it2)->getX() == (*it)->getX() &&
  //   		(*it2)->getY() == (*it)->getY())
  //   	      {
  //   		yetInList = true;
  //   		break;
  //   	      }
  //   	  }
  //   	if (!yetInList)
  //   	  tmp.push_back(*it);
  //     }
  //   for (std::list<Food*>::iterator it = tmp.begin();
  //   	 it != tmp.end(); it++)
  //     _window.draw(*it);
  // }

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
	glm::vec4 clickedColor(static_cast<float>(pixel[0]) / 255.0f,
			       static_cast<float>(pixel[1]) / 255.0f,
			       static_cast<float>(pixel[2]) / 255.0f, 0);
	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  {
	    if ((*it)->getPickColor().r == clickedColor.r &&
		(*it)->getPickColor().g == clickedColor.g &&
		(*it)->getPickColor().b == clickedColor.b)
	      _hud->print(*it, _client, _window);
	    else if (clickedColor.r == 0 &&
		     clickedColor.g == 0 &&
		     clickedColor.b == 0)
	      _hud->hide();
	  }
      }
  }

  void		ZappyGraphic::setMapSize(int width, int height)
  {
    if (!_map)
      _map = new Map(width, height);
    _map->setSize(width, height);
    _map->initialize();
    _world = new World();
    _world->initialize();
    _world->setMapSize(_map->getWidth(), _map->getHeight());
    _window.getCamera()->setPosition(glm::vec2(width / 2, -height / 2));
    for (int i = 0; i < (width + height); i++)
      _window.getCamera()->zoomLess();
  }

  void		ZappyGraphic::setCaseContent(int x, int y, int* resources)
  {
    int foodAtCase = _getFoodAtCase(x, y);
    if (resources[0] > foodAtCase)
      {
	while (resources[0] > foodAtCase)
	  {
	    Food* food = new Food(x, y);
	    food->initialize();
	    _foods.push_back(food);
	    foodAtCase++;
	  }
      }
    else if (resources[0] < foodAtCase)
      {
	while (resources[0] < foodAtCase)
	  {
	    _removeFoodAtCase(x, y);
	    foodAtCase--;
	  }
      }
    int t = 0;
    for (int res = 1; res < 7; res++)
      {
	int nbstone = _getStoneByTypeAtCase(x, y, static_cast<Type>(t));
	if (resources[res] > nbstone)
	  while (resources[res] > nbstone)
	    {
	      Stone* stone = new Stone(static_cast<Type>(t), glm::vec2(x, y));
	      stone->initialize();
	      _stones.push_back(stone);
	      nbstone++;
	    }
	else if (resources[res] < nbstone)
	  while(resources[res] < nbstone)
	    {
	      _removeStoneByTypeAtCase(x, y, static_cast<Type>(t));
	      nbstone--;
	    }
	t++;
      }
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
						    _map->getWidth(),
						    _map->getHeight(),
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
	    if ((*it)->getX() == newX && (*it)->getY() == newY)
	      (*it)->setOrientation(static_cast<Orientation>(orientation));
	    else
	      (*it)->goForward();
	    break;
	  }
      }
  }

  void		ZappyGraphic::changePlayerLevel(int playerId, int level)
  {
    for (std::list<Player*>::iterator it = _players.begin();
	 it != _players.end(); it++)
      {
	if ((*it)->getId() == playerId)
	  {
	    (*it)->setLevel(level);
	    break;
	  }
      }
  }

  void		ZappyGraphic::playerStock(int id, int, int, int* resources)
  {
    _hud->updateStock(id, resources[0], resources[1], resources[2],
		      resources[3], resources[4], resources[5], resources[6]);
  }

  void		ZappyGraphic::playerExpulse(int)
  {
  }

  void		ZappyGraphic::playerBroadcast(int)
  {
  }

  void		ZappyGraphic::playerStartCast(int firstId, int x, int y,
					      int, std::list<int>)
  {
    for (std::list<Player*>::iterator it = _players.begin();
	 it != _players.end(); it++)
      {
	if ((*it)->getId() == firstId)
	  (*it)->startCast();
	else if ((*it)->getX() == x && (*it)->getY() == y)
	  (*it)->startCast();
      }
  }

  void		ZappyGraphic::castEnd(int x, int y, int)
  {
    for (std::list<Player*>::iterator it = _players.begin();
	 it != _players.end(); it++)
      {
	if ((*it)->getX() == x && (*it)->getY() == y)
	  (*it)->stopCast();
      }
  }

  void		ZappyGraphic::playerLaysEgg(int)
  {
    // for (std::list<Player*>::iterator it = _players.begin();
    // 	 it != _players.end(); it++)
    //   {
    // 	if ((*it)->getId() == id)
    // 	  {
    // 	    _eggs.push_back(EggFactory::createNewEgg(id, (*it)->getX(), (*it)->getY()));

    // 	    // Egg* egg = new Egg(id, (*it)->getX(), (*it)->getY());
    // 	    // egg->initialize();
    // 	    // _eggs.push_back(egg);

    // 	    break;
    // 	  }
    //   }
  }

  void		ZappyGraphic::playerDropsResource(int, int)
  {
  }

  void		ZappyGraphic::playerLootsResource(int, int)
  {
  }

  void		ZappyGraphic::playerDies(int playerId)
  {
    _hud->hide();
    for (std::list<Player*>::iterator it = _players.begin();
	 it != _players.end(); it++)
      {
	if ((*it)->getId() == playerId)
	  {
	    (*it)->die();
	    break;
	  }
      }
  }

  void		ZappyGraphic::eggLaidOnCaseByPlayer(int eggid, int playerid,
						    int x, int y)
  {
    Egg* egg = EggFactory::createNewEgg(playerid, eggid, x, y);
    _eggs.push_back(egg);
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
	if ((*it)->getX() == x && (*it)->getY() == y)
	  {
	    _foods.erase(it);
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
	    _stones.erase(it);
	    break;
	  }
      }
  }

  ZappyGraphic::~ZappyGraphic()
  {
  }
}
