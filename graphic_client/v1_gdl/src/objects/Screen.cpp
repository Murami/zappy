#include		<glm/glm.hpp>
#include		"graphic/ShaderManager.hpp"
#include		"objects//Screen.hh"

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
  }

  void		Screen::draw()
  {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    _projection = glm::ortho(0.0f, Window::WIDTH, Window::HEIGHT, 0.0f);
    glm::mat4 cam(1);
    _shader.bind();
    _shader.setUniform("projection", _projection);
    _shader.setUniform("view", cam);
    _shader.setUniform("color", glm::vec4(1, 1, 1, 1));
    _texture.bind();
    _geom.draw(_shader, glm::mat4(1), GL_QUADS);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
  }

  Screen::~Screen()
  {
  }
}
