#ifndef		__LINEMATE_HH__
# define	__LINEMATE_HH__

# include	"AStone.hh"

namespace	graphic
{
  class		Linemate : public AStone
  {
  public :
    virtual void	initialize(int x, int y);

  public :
    Linemate();
    ~Linemate();
  };
}

#endif
