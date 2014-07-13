//
// Screen.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:15 2014 Manu
// Last update Sun Jul 13 23:04:15 2014 Manu
//

#ifndef		__SCREEN_HH__
# define	__SCREEN_HH__

# include	<glm/gtc/matrix_transform.hpp>
# include	<stdexcept>
# include	<string>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"interface/Window.hh"

namespace	Zappy
{
  class		Sentence;

  class		Screen
  {
  private :
    gdl::Geometry	_geom;
    gdl::Texture	_texture;
    gdl::BasicShader	_shader;
    glm::mat4		_projection;
    bool		_endScreen;
    std::string		_winnerTeam;
    Sentence*		_s;

  public :
    void	draw();
    void	setWinnerTeam(const std::string&);

  public :
    Screen(const std::string&);
    ~Screen();
  };
}

#endif
