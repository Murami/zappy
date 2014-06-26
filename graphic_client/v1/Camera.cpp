#include		<math.h>
#include		"Monitor.hh"
#include		"Camera.hh"

namespace		graphic
{
  const double Camera::PI = 3.141592653589793;

  Camera::Camera()
  {
  }

  bool			Camera::_isInMoveKeys(int key)
  {
    for (std::list<int>::iterator it = _moveKeys.begin();
  	 it != _moveKeys.end(); it++)
      {
  	if (key == (*it))
  	  return (true);
      }
    return (false);
  }

  void			Camera::_handleMouseEvent(const SDL_Event&)
  {
    //
    // GESTION EVENTS DE SOURIS
    //
  }

  void			Camera::update(const SDL_Event& event)
  {
    if (event.key.keysym.sym == SDLK_TAB)
      changeState();
    else if (_isInMoveKeys(event.key.keysym.sym))
      (this->*this->_cameraMoves[event.key.keysym.sym])();
    _handleMouseEvent(event);
  }

  void			Camera::initialize(const MapConfig& config)
  {
    _xCenterState = (config.sizeX + config.sizeY) / 2;
    _distance = _xCenterState;
    _yCenterState = _xCenterState;
    _zCenterState = 0;
    _xFreeState = 0;
    _zFreeState = 0;
    _alphaCenterState = 0;
    _alphaFreeState = 0;
    _xDirection = 10 * sin(_alphaFreeState);
    _zDirection = 10 * cos(_alphaFreeState);
    _state = CENTER;
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<double>(Window::WINDOW_X) /
		   static_cast<double>(Window::WINDOW_Y), 1, 1000);
    _moveKeys.push_back(SDLK_DOWN);
    _moveKeys.push_back(SDLK_UP);
    _moveKeys.push_back(SDLK_LEFT);
    _moveKeys.push_back(SDLK_RIGHT);
    _moveKeys.push_back(SDLK_KP_PLUS);
    _moveKeys.push_back(SDLK_KP_MINUS);
    _moveKeys.push_back(SDLK_PLUS);
    _moveKeys.push_back(SDLK_MINUS);
    _cameraMoves[SDLK_DOWN] = &Camera::goUp;
    _cameraMoves[SDLK_UP] = &Camera::goDown;
    _cameraMoves[SDLK_LEFT] = &Camera::turnLeft;
    _cameraMoves[SDLK_RIGHT] = &Camera::turnRight;
    _cameraMoves[SDLK_KP_PLUS] = &Camera::zoomPlus;
    _cameraMoves[SDLK_KP_MINUS] = &Camera::zoomMinus;
    _cameraMoves[SDLK_PLUS] = &Camera::zoomPlus;
    _cameraMoves[SDLK_MINUS] = &Camera::zoomMinus;
  }

  void			Camera::changeState()
  {
    SDL_EnableKeyRepeat(0, 0);
    if (_state == FREE)
      _state = CENTER;
    else
      _state = FREE;
  }

  void			Camera::zoomPlus()
  {
    if (_state == CENTER)
      {
	if (_distance > 1)
	  _distance--;
      }
  }

  void			Camera::zoomMinus()
  {
    if (_state == CENTER)
      {
	if (_distance < 100)
	  _distance++;
      }
  }

  void			Camera::turnLeft()
  {
    if (_state == CENTER)
      _alphaCenterState -= 2 * PI / 360;
    else
      {
	_alphaFreeState += 2 * PI / 360;
      }
  }

  void			Camera::turnRight()
  {
    if (_state == CENTER)
      _alphaCenterState += 2 * PI / 360;
    else
      {
	_alphaFreeState -= 2 * PI / 360;
      }
  }

  void			Camera::goUp()
  {
    if (_state == CENTER)
      {
	if (_yCenterState < 100)
	  _yCenterState += 1;
      }
    else
      {
	_xFreeState -= _xDirection / 100;
	_zFreeState -= _zDirection / 100;
      }
  }

  void			Camera::goDown()
  {
    if (_state == CENTER)
      {
	if (_yCenterState > 5)
	  _yCenterState -= 1;
      }
    else
      {
	_xFreeState += _xDirection / 100;
	_zFreeState += _zDirection / 100;
      }
  }

  void			Camera::updateForDraw()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (_state == CENTER)
      {
	_xCenterState = _distance * sin(_alphaCenterState);
	_zCenterState = _distance * cos(_alphaCenterState);
	gluLookAt(_xCenterState, _yCenterState, _zCenterState,
		  0, 0, 0, 0, 1, 0);
      }
    else
      {
	_xDirection = 10 * sin(_alphaFreeState);
	_zDirection = 10 * cos(_alphaFreeState);
	gluLookAt(_xFreeState, 2, _zFreeState,
		  _xFreeState + _xDirection, 2, _zFreeState + _zDirection,
		  0, 1, 0);
      }
  }

  Camera::~Camera()
  {
  }
}
