#include		<unistd.h>
#include		"objects/AObject.hh"
#include		"objects/Player.hh"
#include		"interface/Window.hh"
#include		"interface/Camera.hh"
#include		"graphic/ShaderManager.hpp"

namespace		Zappy
{
  const float		Window::WIDTH = 1920.0f;
  const float		Window::HEIGHT = 1080.0f;
  const std::string	Window::TITLE = "Zappy Bibicy";
  ShaderManager*	ShaderManager::_instance = NULL;

  Window::Window()
  {
  }

  Camera*		Window::getCamera()
  {
    return (_camera);
  }

  bool			Window::isRunning() const
  {
    return (_running);
  }

  void			Window::_handleMouseEvents()
  {
    glm::ivec2  mouse = _input.getMouseWheel();

    if (mouse.y < 0)
      _camera->zoomLess();
    else if (mouse.y > 0)
      _camera->zoomPlus();
    if (_input.getKey(SDL_BUTTON_MIDDLE))
      {
	glm::ivec2 delta = _input.getMouseDelta();
	_camera->rotateVertical(delta.y);
	_camera->rotateHorizontal(delta.x);
      }
    if (_input.getKey(SDL_BUTTON_LEFT))
      {
	glm::ivec2 delta = _input.getMouseDelta();
	_camera->translateDrag(delta.x, delta.y);
      }
  }

  gdl::Input&		Window::getInputs()
  {
    return (_input);
  }

  void			Window::update()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _context.updateInputs(_input);
    if (_input.getKey(SDLK_ESCAPE))
      _running = false;
    _context.updateClock(_clock);
    _handleMouseEvents();
  }

  void			Window::flush()
  {
    _context.flush();
  }

  void			Window::draw(AObject* object)
  {
    _shader.bind();
    object->draw(_shader, _clock);
  }

  void			Window::drawPlayerColorMap(Player *object)
  {
    _colorPickShader.bind();
    _colorPickShader.setUniform("colorPick", object->getPickColor());
    object->scale(glm::vec3(0.8, 0.999, 0.8));
    object->draw(_colorPickShader, _clock);
    object->scale(glm::vec3(1/0.8, 1/0.999, 1/0.8));
  }

  void			Window::updateObject(AObject* object)
  {
    object->update(_clock, _input);
  }

  void			Window::bindShader()
  {
    _shader.bind();
  }

  void			Window::create(int w, int h, const std::string& title)
  {
    _context.start(w, h, title);
    glEnable(GL_DEPTH_TEST);
    _shader = *ShaderManager::getInstance()->getBasicShader();
    _colorPickShader = *ShaderManager::getInstance()->getColorPickShader();
    _running = true;
    _camera = new Camera(_shader, _colorPickShader);
    _camera->initialize();
  }

  Window::~Window()
  {
  }
}
