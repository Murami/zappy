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
