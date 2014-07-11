#include		<sstream>
#include		<cstring>
#include		"network/Client.hh"
#include		"interface/Window.hh"
#include		"objects/Player.hh"
#include		"graphic/HUD.hh"
#include		"graphic/ShaderManager.hpp"

namespace	Zappy
{
  HUD::HUD()
  {
    _currentPlayer = NULL;
    _active = false;
    if (!_texture.load("./assets/hud/frame.tga"))
      throw (std::runtime_error("Error while loading hud texture"));
    _frame.setColor(glm::vec4(1, 1, 1, 1));
    _frame.pushVertex(glm::vec3(15, 0, 0));
    _frame.pushVertex(glm::vec3(Window::WIDTH / 3, 0, 0));
    _frame.pushVertex(glm::vec3(Window::WIDTH / 3, Window::HEIGHT / 4, 0));
    _frame.pushVertex(glm::vec3(15, Window::HEIGHT / 4, 0));
    _frame.pushUv(glm::vec2(0, 1));
    _frame.pushUv(glm::vec2(1, 1));
    _frame.pushUv(glm::vec2(1, 0));
    _frame.pushUv(glm::vec2(0, 0));
    _frame.build();
    _shader = *ShaderManager::getInstance()->getBasicShader();
    std::memset(&_resources[0], 0, 7 * sizeof(int));
    _font = NULL;
  }

  void		HUD::print(Player* player, Client& client)
  {

    if (TTF_Init() != 0)
      throw (std::runtime_error("Error while initializing TTF_Font"));
    if (!_font)
      if ((_font = TTF_OpenFont("Triforce.ttf", 16)) == NULL)
	throw (std::runtime_error(TTF_GetError()));

    _currentPlayer = player;
    _active = true;
    _client = &client;
    char buff[4096];
    std::memset(buff, 0, 4096);
    std::stringstream ss;
    ss << _currentPlayer->getId();
    std::string request(std::string("pin ") + ss.str() + std::string("\n"));
    _client->sendRequest(request);
  }

  void		HUD::draw()
  {
    if (_currentPlayer)
      {

	// Faire une demande pour l'inventaire du joueur en cours

	SDL_Color fg, bg;
	fg.r = 1;
	fg.g = 1;
	fg.b = 1;
	fg.a = 1;
	bg.r = 0;
	bg.g = 0;
	bg.b = 0;
	bg.a = 0;
	TTF_RenderText_Shaded(_font, "Coucou", fg, bg);

	std::cout << "================[HUD]================" << std::endl
	    	  << "[PLAYER " << _currentPlayer->getId() << "]" << std::endl
		  << "[LEVEL]: " << _currentPlayer->getLevel() << std::endl
	    	  << "[FOOD]: " << _resources[0] << std::endl
	    	  << "[LINEMATE]: " << _resources[1] << std::endl
	    	  << "[DERAUMERE]: " << _resources[2] << std::endl
	    	  << "[SIBUR]: " << _resources[3] << std::endl
	    	  << "[MENDIANE]: " << _resources[4] << std::endl
	    	  << "[PHIRAS]: " << _resources[5] << std::endl
	    	  << "[THYSTAME]: " << _resources[6] << std::endl << std::endl;

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glm::mat4 projection = glm::ortho(0.0f, Window::WIDTH, Window::HEIGHT, 0.0f);
	glm::mat4 cam(1);
	_shader.bind();
	_shader.setUniform("projection", projection);
	_shader.setUniform("view", cam);
	glAlphaFunc(GL_GREATER, 0.1f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_texture.bind();
	_frame.draw(_shader, glm::mat4(1), GL_QUADS);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
      }
  }

  void		HUD::updateStock(int, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
  {
    _resources[0] = food;
    _resources[1] = linemate;
    _resources[2] = deraumere;
    _resources[3] = sibur;
    _resources[4] = mendiane;
    _resources[5] = phiras;
    _resources[6] = thystame;
  }

  bool		HUD::isActive() const
  {
    return (_active);
  }

  void		HUD::hide()
  {
    _currentPlayer = NULL;
    _active = false;
  }

  HUD::~HUD()
  {
  }
}
