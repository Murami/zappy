#include		<Clock.hh>
#include		<sstream>
#include		<cstring>
#include		"network/Client.hh"
#include		"interface/Window.hh"
#include		"objects/Player.hh"
#include		"graphic/HUD.hh"
#include		"graphic/ShaderManager.hpp"
#include		"objects/Sentence.hh"

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
  }

  void		HUD::print(Player* player, Client& client, Window& window)
  {
    _currentPlayer = player;
    _active = true;
    _client = &client;
    _window = &window;
  }

  void		HUD::_printLife()
  {
    std::stringstream	ss;
    ss << _resources[0];
    Sentence s(ss.str(), Window::WIDTH / 6,
	       3 * Window::HEIGHT * (62.5 / 900) - 16);
    s.draw(_shader);
  }

  void		HUD::_printLevel()
  {
    std::stringstream ss;
    ss << _currentPlayer->getLevel();
    Sentence s(ss.str(), Window::WIDTH / 6 + 5,
	       2 * Window::HEIGHT * (62.5 / 900) - 5);
    s.draw(_shader);
  }

  void		HUD::_printTeam()
  {
  }

  void		HUD::_printResources()
  {
    // linemate : blue
    std::stringstream ss;
    ss << _resources[1];
    Sentence s(ss.str(), Window::WIDTH * (72.5 / 1600),
	       Window::HEIGHT * (62.5 / 900));
    s.draw(_shader);
    // deraumere : red
    std::stringstream ss2;
    ss2 << _resources[2];
    s = Sentence(ss2.str(), Window::WIDTH * (72.5 / 1600),
		 2 * Window::HEIGHT * (62.5 / 900) - 9);
    s.draw(_shader);
    // mendiane : yellow
    std::stringstream ss3;
    ss3 << _resources[4];
    s = Sentence(ss3.str(), Window::WIDTH * (72.5 / 1600),
		 3 * Window::HEIGHT * (62.5 / 900) - 16);
    s.draw(_shader);
    // sibur : green
    std::stringstream ss4;
    ss4 << _resources[3];
    s = Sentence(ss4.str(),
		 Window::WIDTH / 3 - 15 - Window::WIDTH * (72.5 / 1600),
		 Window::HEIGHT * (62.5 / 900));
    s.draw(_shader);
    // phiras : purple
    std::stringstream ss5;
    ss5 << _resources[5];
    s = Sentence(ss5.str(),
		 Window::WIDTH / 3 - 15 - Window::WIDTH * (72.5 / 1600),
		 2 * Window::HEIGHT * (62.5 / 900) - 9);
    s.draw(_shader);
    // thystame : grey
    std::stringstream ss6;
    ss6 << _resources[6];
    s = Sentence(ss6.str(),
		 Window::WIDTH / 3 - 15 - Window::WIDTH * (72.5 / 1600),
		 3 * Window::HEIGHT * (62.5 / 900) - 16);
    s.draw(_shader);
  }

  void		HUD::draw()
  {
    if (_currentPlayer)
      {
	char buff[4096];
	std::memset(buff, 0, 4096);
	std::stringstream ss;
	ss << _currentPlayer->getId();
	std::string request(std::string("pin ") + ss.str() + '\n');
	_client->sendRequest(request);

	std::memset(&buff[0], 0, 4096);
	request = std::string(std::string("plv ") + ss.str() + '\n');
	_client->sendRequest(request);

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

	// TODO
	_printLife();
	_printLevel();
	_printTeam();

	_printResources();

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
