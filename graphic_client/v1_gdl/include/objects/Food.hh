#ifndef		__FOOD_HH__
# define	__FOOD_HH__

# include	<Model.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  class		Food : public AObject
  {
  private :
    int		_x;
    int		_y;
    gdl::Model*	_model;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    int		getX() const;
    int		getY() const;

  public :
    Food(int x, int y);
    ~Food();
  };
}

#endif
