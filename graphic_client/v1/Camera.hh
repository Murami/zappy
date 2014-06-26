#ifndef		__CAMERA_HH__
# define	__CAMERA_HH__

# include	<SDL/SDL.h>
# include	<list>
# include	<iostream>
# include	<map>

namespace	graphic
{
  class		Camera
  {
  public :
    enum	CameraState
      {
	FREE,
	CENTER
      };

  private :
    const static double PI;

  private :
    double	_xCenterState;
    double	_yCenterState;
    double	_zCenterState;
    double	_xFreeState;
    double	_zFreeState;
    double	_xDirection;
    double	_zDirection;
    double	_alphaCenterState;
    double	_alphaFreeState;
    double	_distance;
    CameraState	_state;
    std::map<int, void (Camera::*)()>	_cameraMoves;
    std::list<int>			_moveKeys;

  private :
    bool	_isInMoveKeys(int);
    void	_handleMouseEvent(const SDL_Event&);

  public :
    void	initialize(const MapConfig&);
    void	updateForDraw();
    void	changeState();
    void	update(const SDL_Event&);

  public :
    void	goDown();
    void	goUp();
    void	turnLeft();
    void	turnRight();
    void	zoomPlus();
    void	zoomMinus();

  public :
    Camera();
    ~Camera();
  };
}

#endif
