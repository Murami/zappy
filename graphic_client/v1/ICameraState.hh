#ifndef		__ACAMERASTATE_HH__
# define	__ACAMERASTATE_HH__

# include	<list>
# include	<iostream>
# include	<map>
# include	"Monitor.hh"

namespace	graphic
{
  class		ACameraState
  {
  protected :
    double	_x;
    double	_y;
    double	_z;
    double	_alpha;
    std::map<int, void (ACameraState::*)()>	_cameraMoves;
    std::list<int>				_moveKeys;

  protected :
    bool	_isInMoveKeys(int);

  public :
    ACameraState();
    virtual ~ACameraState();

  public :
    void	initialize(const struct MapConfig&);
    void	update(int);

  public :
    virtual void	updateForDraw() = 0;
    virtual void	goDown() = 0;
    virtual void	goUp() = 0;
    virtual void	turnLeft() = 0;
    virtual void	turnRight() = 0;
    virtual void	zoomPlus() = 0;
    virtual void	zoomMinus() = 0;
  };
}

#endif
