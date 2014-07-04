#include		"objects/Stone.hh"
#include		"objects/Map.hh"
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
    // Lancer le thread de la connection

    _window.create(Window::WIDTH, Window::HEIGHT, Window::TITLE);

    _map = new Map(20, 20);
    _map->initialize();

    _window.getCamera()->setPosition(glm::vec2(10, 10));

    Stone* linemate = new Stone(LINEMATE, glm::vec2(0, 0));
    linemate->initialize();

    Stone* deraumere = new Stone(DERAUMERE, glm::vec2(0, 0));
    deraumere->initialize();

    Stone* sibur = new Stone(SIBUR, glm::vec2(0, 0));
    sibur->initialize();

    Stone* mendiane = new Stone(MENDIANE, glm::vec2(0, 0));
    mendiane->initialize();

    Stone* phiras = new Stone(PHIRAS, glm::vec2(0, 0));
    phiras->initialize();

    Stone* thystame = new Stone(THYSTAME, glm::vec2(0, 0));
    thystame->initialize();

    while (_window.isRunning())
      {
	_window.update();
	// Dessin des elements ici
	_window.bindShader();

	_window.draw(linemate);
	_window.draw(deraumere);
	_window.draw(sibur);
	_window.draw(mendiane);
	_window.draw(phiras);
	_window.draw(thystame);

	_window.draw(_map);

	_window.flush();
      }
  }

  ZappyGraphic::~ZappyGraphic()
  {
  }
}
