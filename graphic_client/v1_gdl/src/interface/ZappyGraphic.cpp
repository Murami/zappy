#include		"objects/Map.hh"
#include		"objects/Player.hh"
#include		"interface/ZappyGraphic.hh"
#include		"interface/Camera.hh"

namespace	Zappy
{
  ZappyGraphic::ZappyGraphic(int argc, char **argv)
  {
    _connection.initialize(argc, argv);
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
	    for (int i = 0; i < 12; i++)
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

    std::list<Player*> list;

    for (int i = 0; i < 20; i++)
      {
	Player* player = new Player(10,  10, "Gitan");
	player->initialize();
	list.push_back(player);
      }

    while (_window.isRunning())
      {
	_window.update();
	_window.bindShader();

	for (std::list<Player*>::iterator it = list.begin();
	     it != list.end(); it++)
	  {
	    if ((*it)->getState() == STANDING)
	      {
		if (random() % 2 == 0)
		  (*it)->turnLeft();
		else
		  (*it)->turnRight();
		(*it)->goForward();
	      }
	    _window.updateObject(*it);
	  }

	for (std::list<Player*>::iterator it = list.begin();
	     it != list.end(); it++)
	  _window.draw(*it);

	for (std::list<Stone*>::iterator it = _stones.begin();
	     it != _stones.end(); it++)
	  _window.draw(*it);

	_window.draw(_map);
	_window.flush();
      }
  }

  ZappyGraphic::~ZappyGraphic()
  {
  }
}
