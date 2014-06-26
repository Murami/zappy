#include		"Monitor.hh"
#include		"Window.hh"
#include		"Camera.hh"

namespace		graphic
{
  const int		Window::WINDOW_X = 1920;
  const int		Window::WINDOW_Y = 1080;
  const int		Window::QUIT = -1;
  const std::string	Window::TITLE = "Zappy";
  const int		Window::BLOCK_SIZE = 5;

  Window::Window()
  {
  }

  void			Window::create(const struct MapConfig& config)
  {
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
      throw (std::runtime_error("Error initializing SDL"));
    _screen = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_HWSURFACE |
			       SDL_OPENGL | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_WM_SetCaption(TITLE.c_str(), NULL);
    _mapSizeX = config.sizeX;
    _mapSizeY = config.sizeY;
    _camera = new Camera();
    _camera->initialize(config);
    SDL_EnableKeyRepeat(10, 10);
  }

  int			Window::update()
  {
    SDL_Event		event;

    memset(&event, 0, sizeof(event));
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      return (QUIT);
    else if (event.type == SDL_KEYDOWN)
      {
	if (event.key.keysym.sym == SDLK_ESCAPE)
	  return (QUIT);
	_camera->update(event);
      }
    else if (event.type == SDL_KEYUP)
      SDL_EnableKeyRepeat(10, 10);
    return (0);
  }

  void			Window::_drawGrid(const struct MapConfig& config)
  {
    for (int x = -config.sizeX * BLOCK_SIZE;
	 x <= config.sizeX * BLOCK_SIZE; x += BLOCK_SIZE)
      {
	glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
	glVertex3d(x, 0.1, -config.sizeY / 2 * BLOCK_SIZE);
	glVertex3d(x, 0.1, config.sizeY / 2 * BLOCK_SIZE);
	glEnd();
      }
    for (int y = -config.sizeY * BLOCK_SIZE;
	 y <= config.sizeY * BLOCK_SIZE; y += BLOCK_SIZE)
      {
	glBegin(GL_LINES);
	glColor3ub(0, 0, 0);
	glVertex3d(config.sizeX * BLOCK_SIZE, 0.1, y);
	glVertex3d(-config.sizeX * BLOCK_SIZE, 0.1, y);
	glEnd();
      }
  }

  void			Window::_drawMap(const struct MapConfig& config)
  {
    glBegin(GL_QUADS);
    glColor3ub(255, 153, 51);
    glVertex3d(-config.sizeX / 2 * BLOCK_SIZE, 0,
	       -config.sizeY / 2 * BLOCK_SIZE);
    glColor3ub(255, 178, 102);
    glVertex3d(config.sizeX / 2 * BLOCK_SIZE, 0,
	       -config.sizeY / 2 * BLOCK_SIZE);
    glColor3ub(255, 128, 0);
    glVertex3d(config.sizeX / 2 * BLOCK_SIZE, 0, config.sizeY / 2 * BLOCK_SIZE);
    glColor3ub(204, 102, 0);
    glVertex3d(-config.sizeX / 2 * BLOCK_SIZE, 0,
	       config.sizeY / 2 * BLOCK_SIZE);
    glEnd();
    _drawGrid(config);
  }

  void			Window::draw(const struct MapConfig& config)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _camera->updateForDraw();
    _drawMap(config);
    glFlush();
    SDL_GL_SwapBuffers();
  }

  Window::~Window()
  {
  }
}
