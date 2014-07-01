#ifndef		__SKYBOX_HH__
# define	__SKYBOX_HH__

# include	<iostream>
# include	<SDL/SDL.h>
# include	<GL/gl.h>
# include	<GL/glu.h>
# include	"SdlGlUtils.hh"

namespace	graphic
{
  class		Skybox
  {
  private :
    GLuint	_texture;
    GLUquadric*	_quadric;

  public :
    void	draw();
    void	update(const SDL_Event&);

  public :
    Skybox();
    ~Skybox();
  };
}

#endif
