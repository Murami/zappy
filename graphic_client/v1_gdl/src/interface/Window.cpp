#include		<unistd.h>
#include		"objects/AObject.hh"
#include		"interface/Window.hh"
#include		"interface/Camera.hh"

namespace		Zappy
{
  const float		Window::WIDTH = 1920.0f;
  const float		Window::HEIGHT = 1080.0f;
  const std::string	Window::TITLE = "Zappy Bibicy";

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

  void			Window::update()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _context.updateInputs(_input);
    if (_input.getKey(SDLK_ESCAPE))
      _running = false;
    _context.updateClock(_clock);
    _handleMouseEvents();
    // if (_clock.getElapsed() < 1.0f / 10.0f)
    //   {
    // 	//std::cout << (1.0f / 10.0f) - _clock.getElapsed() << std::endl;
    // 	usleep((1.0f / 10.0f) - _clock.getElapsed());
    //   }
  }

  void			Window::flush()
  {
    _context.flush();
  }

  void			Window::draw(AObject* object)
  {
    object->draw(_shader, _clock);
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
    if (!_shader.load("./gdl/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
	!_shader.load("./gdl/shaders/basic.vp", GL_VERTEX_SHADER) ||
	!_shader.build())
      throw (std::runtime_error("Failed shader initialization"));
    _running = true;
    _camera = new Camera(_shader);
    _camera->initialize();
  }

  Window::~Window()
  {
  }
}
