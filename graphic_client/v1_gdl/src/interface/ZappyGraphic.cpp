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

    // for (int x = 0; x < 20; x++)
    //   {
    // 	for (int y = 0; y < 20; y++)
    // 	  {
    // 	    for (int i = 0; i < random() % 7; i++)
    // 	      {
    // 		Stone* stone = new Stone((i == 0 ? LINEMATE :
    // 					  i == 1 ? DERAUMERE :
    // 					  i == 2 ? SIBUR :
    // 					  i == 3 ? MENDIANE :
    // 					  i == 4 ? PHIRAS : THYSTAME),
    // 					 glm::vec2(x, y));
    // 		stone->initialize();
    // 		_stones.push_back(stone);
    // 	      }
    // 	  }
    //   }

    // for (int i = 0; i < 10; i++)
    //   {
    // 	Egg *egg = new Egg(random() % 20, random() % 20);
    // 	egg->initialize();
    // 	_eggs.push_back(egg);
    //   }

    // _world = new World();
    // _world->initialize();

    // for (int x = 0; x < 20; x++)
    //   {
    // 	Food* food = new Food(random() % 20, random() % 20);
    // 	food->initialize();
    // 	_foods.push_back(food);
    //   }

    // for (int i = 0; i < 1; i++)
    //   {
    // 	Player* player = PlayerFactory::createNewPlayer(10,  10, "Gitan");
    // 	player->initialize();
    // 	_players.push_back(player);
    //   }

    while (_window.isRunning())
      {
	_window.bindShader();
	_window.update();

	updateClient();

	// for (std::list<Player*>::iterator it = _players.begin();
	//      it != _players.end(); it++)
	//   {
	//     if ((*it)->getState() == STANDING)
	//       {
	// 	if (random() % 2 == 0)
	// 	  (*it)->turnLeft();
	// 	else
	// 	  (*it)->turnRight();
	// 	(*it)->goForward();
	//       }
	//     _window.updateObject(*it);
	//   }

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  _window.drawPlayerColorMap(static_cast<Player*>(*it));

	_handleRightClickEvent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// _window.bindShader();
	// _window.draw(_world);

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  _window.draw(*it);

	for (std::list<Food*>::iterator it = _foods.begin();
	     it != _foods.end(); it++)
	  _window.draw(*it);

	// for (std::list<Egg*>::iterator it = _eggs.begin();
	//      it != _eggs.end(); it++)
	//   _window.draw(*it);

	// for (std::list<Stone*>::iterator it = _stones.begin();
	//      it != _stones.end(); it++)
	//   _window.draw(*it);

	_window.draw(_map);
	_window.flush();
      }
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

  void		ZappyGraphic::setCaseContent(int x, int y, int* resources)
  {
    for (int i = 0; i < resources[0]; i++)
      {
	Food* food = new Food(x, y);
	food->initialize();
	_foods.push_back(food);
      }
    for (int res = 1; res < 7; res++)
      {
	for (int nb = 0; nb < resources[res]; nb++)
	  {

	  }
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
						    teamName);
    player->initialize();
    _players.push_back(player);
  }

  void		ZappyGraphic::setPlayerPosition(int, int, int, int)
  {
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
