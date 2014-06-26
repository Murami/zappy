//
// sdlglutils.hh for nibbler in /home/manu/tek2/C++/nibbler/v1/opengl/plateau/v3
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Thu Apr  3 13:12:02 2014 Manu
// Last update Thu Jun 26 09:48:51 2014 Manu
//

#ifndef		__SDLGLUTILS_HH__
# define	__SDLGLUTILS_HH__

# include <GL/gl.h>
# include <SDL/SDL.h>

# ifndef GL_CLAMP_TO_EDGE
#  define GL_CLAMP_TO_EDGE 0x812F
# endif

namespace		graphic
{
  class			SdlGlUtils
  {
  public :
    static SDL_Surface * flipSurface(SDL_Surface * surface);
    static GLuint loadTexture(const char * filename, bool useMipMap = true);
    static int takeScreenshot(const char * filename);
    static void drawAxis(double scale = 1);
    static int initFullScreen(unsigned int * width = NULL,
			      unsigned int * height = NULL);
    static int XPMFromImage(const char * imagefile, const char * XPMfile);
    static SDL_Cursor * cursorFromXPM(const char * xpm[]);
  };
}

#endif //SDLGLUTILS_H
