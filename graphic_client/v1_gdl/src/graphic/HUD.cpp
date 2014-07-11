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
    if (!_texture.load("./assets/floor.tga"))
      throw (std::runtime_error("Error while loading hud texture"));
    _frame.setColor(glm::vec4(1, 0, 1, 1));
    _frame.pushVertex(glm::vec3(Window::WIDTH - (Window::WIDTH / 3),
				Window::HEIGHT - (Window::HEIGHT / 6), 0));
    _frame.pushVertex(glm::vec3(Window::WIDTH,
				Window::HEIGHT - (Window::HEIGHT / 6), 0));
    _frame.pushVertex(glm::vec3(Window::WIDTH, Window::HEIGHT, 0));
    _frame.pushVertex(glm::vec3(Window::WIDTH - (Window::WIDTH / 3),
				Window::HEIGHT, 0));
    _frame.pushUv(glm::vec2(0, 0));
    _frame.pushUv(glm::vec2(1, 0));
    _frame.pushUv(glm::vec2(1, 1));
    _frame.pushUv(glm::vec2(0, 1));
    _frame.build();
    _shader = ShaderManager::getInstance()->getHUDShader();
  }

  void		HUD::print(Player* player, Client& client)
  {
    _currentPlayer = player;
    _active = true;
    _client = &client;
    draw();

    char buff[4096];
    std::memset(buff, 0, 4096);
    std::stringstream ss;
    ss << _currentPlayer->getId();
    std::string request(std::string("pin ") + ss.str());
    _client->sendRequest(request);
  }

  void		HUD::draw()
  {
    if (_currentPlayer)
      {

	// Faire une demande pour l'inventaire du joueur en cours

	glDisable(GL_DEPTH_TEST);
	glm::mat4 projection = glm::ortho(0.0f, Window::WIDTH, Window::HEIGHT, 0.0f);
	glm::mat4 cam(1);
	_shader->bind();
	_shader->setUniform("projection", projection);
	_shader->setUniform("view", cam);
	_texture.bind();
	_frame.draw(*_shader, glm::mat4(1), GL_QUADS);
	glEnable(GL_DEPTH_TEST);
      }
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
