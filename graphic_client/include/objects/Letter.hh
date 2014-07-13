//
// Letter.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:46 2014 Manu
// Last update Sun Jul 13 23:04:47 2014 Manu
//

#ifndef		__LETTER_HH__
# define	__LETTER_HH__

# include	"BasicShader.hh"
# include	"objects/LetterManager.hpp"
# include	"objects/AObject.hh"

namespace	Zappy
{
  class		Letter : public AObject
  {
  private :
    gdl::Geometry*	_geometry;
    gdl::Texture*	_texture;
    char		_character;
    gdl::BasicShader	_shader;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    Letter(char);
    ~Letter();
  };
}

#endif
