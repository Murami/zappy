#include		<glm/glm.hpp>
#include		"graphic/ShaderManager.hpp"
#include		"objects/Screen.hh"
#include		"objects/Sentence.hh"
#include		"interface/Window.hh"

namespace	Zappy
{
  Screen::Screen(const std::string& file)
  {
    if (!_texture.load(file))
      throw (std::runtime_error(std::string("Error while loading ") + file));
    _geom.setColor(glm::vec4(1, 1, 1, 1));
    _geom.pushVertex(glm::vec3(0, 0, 0));
    _geom.pushVertex(glm::vec3(Window::WIDTH, 0, 0));
    _geom.pushVertex(glm::vec3(Window::WIDTH, Window::HEIGHT, 0));
    _geom.pushVertex(glm::vec3(0, Window::HEIGHT, 0));
    _geom.pushUv(glm::vec2(0, 1));
    _geom.pushUv(glm::vec2(1, 1));
    _geom.pushUv(glm::vec2(1, 0));
    _geom.pushUv(glm::vec2(0, 0));
    _geom.build();
    _shader = *ShaderManager::getInstance()->getBasicShader();
    _endScreen = false;
  }

  void		Screen::draw()
  {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    _projection = glm::ortho(0.0f, Window::WIDTH, Window::HEIGHT, 0.0f);
    glm::mat4 cam(1);
    _shader.bind();
    _shader.setUniform("projection", _projection);
    _shader.setUniform("view", cam);
    _shader.setUniform("color", glm::vec4(1, 1, 1, 1));
    glAlphaFunc(GL_GREATER, 0.1f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _texture.bind();
    _geom.draw(_shader, glm::mat4(1), GL_QUADS);
    if (_endScreen)
      {
	_s->draw(_shader);
      }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
  }

  void		Screen::setWinnerTeam(const std::string& win)
  {
    _s = new Sentence(win, (Window::WIDTH * 500) / (1920 / 2), (Window::HEIGHT * 250) / (1080 / 2));
    _winnerTeam = win;
    _endScreen = true;
  }

  Screen::~Screen()
  {
  }
}
