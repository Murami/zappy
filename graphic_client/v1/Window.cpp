#include		"Monitor.hh"
#include		"Window.hh"

namespace		graphic
{
  const int		Window::WINDOW_X = 1280;
  const int		Window::WINDOW_Y = 960;
  const int		Window::QUIT = -1;
  const std::string	Window::TITLE = "Zappy";

  Window::Window()
  {
  }

  void			Window::create(const struct MapConfig& config)
  {
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
      throw (std::runtime_error("Error initializing SDL"));
    _screen = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_HWSURFACE |
			       SDL_OPENGL);
    SDL_WM_SetCaption(TITLE.c_str(), NULL);
    _mapSizeX = config.sizeX;
    _mapSizeY = config.sizeY;
  }

  int			Window::update()
  {
    SDL_Event		event;

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      return (QUIT);
    else if (event.type == SDL_KEYDOWN)
      {
	if (event.key.keysym.sym == SDLK_ESCAPE)
	  return (QUIT);
      }
    return (0);
  }

  void			Window::draw(const struct MapConfig&)
  {
  }

  Window::~Window()
  {
  }
}
