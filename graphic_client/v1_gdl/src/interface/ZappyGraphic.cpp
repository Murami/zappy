#include		<GL/glew.h>
#include		<GL/glut.h>
#include		"objects/Map.hh"
#include		"objects/Player.hh"
#include		"interface/ZappyGraphic.hh"
#include		"interface/Camera.hh"
#include		"network/Client.hh"
#include		"objects/PlayerFactory.hpp"
#include		"objects/World.hh"

namespace	Zappy
{
  ZappyGraphic::ZappyGraphic(Client& client) : _client(client)
  {
  }

  void		ZappyGraphic::updateClient()
  {
    // while (_client.getQueue().size())
    //   {
    // 	std::string cmd(_client.getQueue().front());
    // 	// PARSER CMD
    // 	_client.getQueue().pop();
    //   }
  }

  void		ZappyGraphic::run()
  {
    _window.create(Window::WIDTH, Window::HEIGHT, Window::TITLE);

    _map = new Map(20, 20);
    _map->initialize();

    _window.getCamera()->setPosition(glm::vec2(10, 10));

    for (int x = 0; x < 20; x++)
      {
    	for (int y = 0; y < 20; y++)
    	  {
    	    for (int i = 0; i < random() % 7; i++)
    	      {
    		Stone* stone = new Stone((i == 0 ? LINEMATE :
    					  i == 1 ? DERAUMERE :
    					  i == 2 ? SIBUR :
    					  i == 3 ? MENDIANE :
    					  i == 4 ? PHIRAS : THYSTAME),
    					 glm::vec2(x, y));
    		stone->initialize();
    		_stones.push_back(stone);
    	      }
    	  }
      }

    _world = new World();
    _world->initialize();

    for (int x = 0; x < 20; x++)
      {
    	for (int y = 0; y < 20; y++)
    	  {
    	    Food* food = new Food(x, y);
    	    food->initialize();
    	    _foods.push_back(food);
    	  }
      }

    for (int i = 0; i < 1; i++)
      {
    	Player* player = PlayerFactory::createNewPlayer(10,  10, "Gitan");
    	player->initialize();
    	_players.push_back(player);
      }

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

	_window.bindShader();
	_window.draw(_world);

	for (std::list<Player*>::iterator it = _players.begin();
	     it != _players.end(); it++)
	  _window.draw(*it);

	// for (std::list<Food*>::iterator it = _foods.begin();
	//      it != _foods.end(); it++)
	//   _window.draw(*it);

	// _window.bindShader();

	for (std::list<Stone*>::iterator it = _stones.begin();
	     it != _stones.end(); it++)
	  _window.draw(*it);

	_window.draw(_map);

	_window.flush();
      }
  }

  void		ZappyGraphic::_handleRightClickEvent()
  {
    gdl::Input	input = _window.getInputs();
    unsigned char pixel[4];
    pixel[0] = pixel[1] = pixel[2] = pixel[3] = 0;
    if (input.getInput(SDL_BUTTON_RIGHT))
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

  ZappyGraphic::~ZappyGraphic()
  {
  }
}
