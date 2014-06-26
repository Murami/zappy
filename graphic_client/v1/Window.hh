#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<iostream>
# include	<stdexcept>
# include	<SDL/SDL.h>
# include	<GL/gl.h>
# include	<GL/glu.h>

namespace	graphic
{
  class		Camera;

  class		Window
  {
  public :
    const static int		WINDOW_X;
    const static int		WINDOW_Y;
    const static std::string	TITLE;
    const static int		QUIT;
    const static int		BLOCK_SIZE;

  private :
    SDL_Surface*			_screen;
    int					_mapSizeX;
    int					_mapSizeY;
    Camera*				_camera;

  private :
    void			_drawMap(const struct MapConfig&);
    void			_drawGrid(const struct MapConfig&);

  public :
    void			create(const struct MapConfig&);
    int				update();
    void			draw(const struct MapConfig&);

  public :
    Window();
    ~Window();
  };
}

#endif
