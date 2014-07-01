#ifndef		__ASTONE_HH__
# define	__ASTONE_HH__

# include	<SDL/SDL.h>
# include	<GL/gl.h>
# include	<GL/glu.h>
# include	"SdlGlUtils.hh"

namespace	graphic
{
  class		AStone
  {
  protected :
    int			_caseX;
    int			_caseY;
    int			_x;
    int			_y;

  public :
    virtual void	initialize(int x, int y) = 0;

  public :
    void	draw();

  public :
    void	setCaseX(int);
    void	setCaseY(int);
    void	setX(int);
    void	setY(int);

  public :
    int		getCaseX() const;
    int		getCaseY() const;
    int		getX() const;
    int		getY() const;

  public :
    AStone();
    ~AStone();
  };
}

#endif
