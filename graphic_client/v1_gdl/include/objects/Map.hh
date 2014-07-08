#ifndef		__MAP_HH__
# define	__MAP_HH__

# include	<stdexcept>
# include	<iostream>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  class		Map : public AObject
  {
  public :
    const static int	BLOCK_SIZE;

  private :
    gdl::Geometry	_geom;
    gdl::Geometry	_lines;
    gdl::Texture	_texture;
    int			_width;
    int			_height;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    Map(int width, int height);
    ~Map();
  };
}

#endif
