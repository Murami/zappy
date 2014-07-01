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

  void			Camera::update(const SDL_Event& event)
  {
    if (event.type == SDL_KEYDOWN)
      {
	if (event.key.keysym.sym == SDLK_TAB)
	  changeState();
	else if (_isInMoveKeys(event.key.keysym.sym))
	  (this->*this->_cameraMoves[event.key.keysym.sym])();
      }
  }

  void			Camera::_setNewTouch(int key, void (Camera::*fct)())
  {
    _moveKeys.push_back(key);
    _cameraMoves[key] = fct;
  }

  void			Camera::initialize(const MapConfig& config)
  {
    _xCenterState = (config.sizeX + config.sizeY) / 2;
    _distance = _xCenterState;
    _yCenterState = 0;
    _zCenterState = _xCenterState;
    _xFreeState = 0;
    _yFreeState = 0;
    _zFreeState = 2;
    _alphaCenterState = 0;
    _alphaFreeState = 0;
    _xDirection = 10 * sin(_alphaFreeState);
    _yDirection = 10 * cos(_alphaFreeState);
    _state = CENTER;
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<double>(Window::WINDOW_X) /
		   static_cast<double>(Window::WINDOW_Y), 1, 10000);
    _setNewTouch(SDLK_DOWN, &Camera::goUp);
    _setNewTouch(SDLK_UP, &Camera::goDown);
    _setNewTouch(SDLK_LEFT, &Camera::turnLeft);
    _setNewTouch(SDLK_RIGHT, &Camera::turnRight);
    _setNewTouch(SDLK_KP_PLUS, &Camera::zoomPlus);
    _setNewTouch(SDLK_KP_MINUS, &Camera::zoomMinus);
    _setNewTouch(SDLK_1, &Camera::higher);
    _setNewTouch(SDLK_2, &Camera::lower);
  }

  void			Camera::changeState()
  {
    SDL_EnableKeyRepeat(0, 0);
    if (_state == FREE)
      _state = CENTER;
    else
      _state = FREE;
    SDL_EnableKeyRepeat(10, 10);
  }

  void			Camera::lower()
  {
    if (_state == FREE)
      _zFreeState += 0.5;
  }

  void			Camera::higher()
  {
    if (_state == FREE)
      _zFreeState -= 0.5;
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
	_alphaFreeState -= 3 * PI / 360;
      }
  }

  void			Camera::turnRight()
  {
    if (_state == CENTER)
      _alphaCenterState += 2 * PI / 360;
    else
      {
	_alphaFreeState += 3 * PI / 360;
      }
  }

  void			Camera::goUp()
  {
    if (_state == CENTER)
      {
	if (_zCenterState < 100)
	  _zCenterState += 1;
      }
    else
      {
	_xFreeState -= _xDirection / 25;
	_yFreeState -= _yDirection / 25;
      }
  }

  void			Camera::goDown()
  {
    if (_state == CENTER)
      {
	if (_zCenterState > 5)
	  _zCenterState -= 1;
      }
    else
      {
	_xFreeState += _xDirection / 25;
	_yFreeState += _yDirection / 25;
      }
  }

  void			Camera::updateForDraw()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (_state == CENTER)
      {
	_xCenterState = _distance * sin(_alphaCenterState);
	_yCenterState = _distance * cos(_alphaCenterState);
	gluLookAt(_xCenterState, _yCenterState, _zCenterState,
		  0, 0, 0, 0, 0, 1);
      }
    else
      {
	_xDirection = 10 * sin(_alphaFreeState);
	_yDirection = 10 * cos(_alphaFreeState);
	gluLookAt(_xFreeState, _yFreeState,
		  _zFreeState,
		  _xFreeState + _xDirection, _yFreeState + _yDirection,
		  _zFreeState - (_zFreeState / 5),
		  0, 0, 1);
      }
  }

  Camera::~Camera()
  {
  }
}
