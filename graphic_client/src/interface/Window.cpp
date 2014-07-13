#include		<SDL_ttf.h>
#include		<unistd.h>
#include		"objects/AObject.hh"
#include		"objects/Player.hh"
#include		"interface/Window.hh"
#include		"interface/Camera.hh"
#include		"graphic/ShaderManager.hpp"

namespace		Zappy
{
  const float		Window::WIDTH = 1920.0f / 1.5f;
  const float		Window::HEIGHT = 1080.0f / 1.5f;
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

  void			Window::updateCamera()
  {
    _camera->update();
  }

  void			Window::update()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _context.updateInputs(_input);
    if (_input.getKey(SDLK_ESCAPE))
      _running = false;
    _context.updateClock(_clock);
    _handleMouseEvents();
    _camera->update();
  }

  void			Window::flush()
  {
    _context.flush();
  }

  void			Window::draw(AObject* object)
  {
    _shader.bind();
    if (object)
      object->draw(_shader, _clock);
  }

  void			Window::drawPlayer(Player* player)
  {
    if (player->getLevel() < 7)
      {
	gdl::BasicShader* shader = ShaderManager::getInstance()->getPlayerShader(player->getLevel());
	shader->bind();
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ShaderManager::getInstance()->getPlayerTexture(player->getLevel())->getId());
	shader->setUniform("texture", 1);
	glActiveTexture(GL_TEXTURE0);
	player->draw(*shader, _clock);
	glActiveTexture(GL_TEXTURE0);
      }
    else
      {
	gdl::BasicShader* shader = ShaderManager::getInstance()->getBasicShader();
	shader->bind();
	player->draw(*shader, _clock);
      }
  }

  void			Window::drawMap(AObject* object)
  {
    if (object)
      object->draw(_shader, _clock);
  }

  void			Window::drawPlayerColorMap(Player *object)
  {
    _colorPickShader.bind();
    _colorPickShader.setUniform("colorPick", object->getPickColor());
    object->draw(_colorPickShader, _clock);
  }

  void			Window::updatePlayers(std::list<Player*>& list)
  {
    for (std::list<Player*>::iterator it = list.begin();
	 it != list.end(); it++)
      {
	updateObject(*it);
	drawPlayer(*it);
	if ((*it)->isAlive() == false)
	  {
	    list.erase(it);
	    break;
	  }
      }
  }

  void			Window::setCameraPosition(int x, int y)
  {
    _camera->setPosition(glm::vec2(x, y));
  }

  void			Window::updateObject(AObject* object)
  {
    if (object)
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
