#ifndef		__CASE_HH__
# define	__CASE_HH__

# include	<list>
# include	"objects/Food.hh"

namespace	Zappy
{
  class		Case
  {
  private :
    int			_x;
    int			_y;
    std::list<Food*>	_foodList;

  public :
    void	addFood();
    void	removeFood();
    void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    Case(int x, int y);
    ~Case();
  };
}

#endif
