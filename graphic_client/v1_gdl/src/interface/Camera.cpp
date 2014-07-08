#include		"interface/Window.hh"
#include		"interface/Camera.hh"
#include		"objects/Map.hh"

namespace	Zappy
{

  Camera::Camera(gdl::AShader& shader,
		 gdl::AShader& colorShader) : _shader(shader),
					       _colorPickShader(colorShader)
  {
    _distance = 10;
    _x = 5;
    _y = 0;
    _z = 2;
    _xFocus = 0;
    _yFocus = 0;
    _zFocus = 0;
    _xTop = 0;
    _yTop = 0;
    _zTop = 1;
    _phi = asin(_x / _distance);
    _zTop = sin(_phi);
    _thetha = 0;
    _projection = glm::perspective(60.0f, static_cast<float>(Window::WIDTH) /
				   static_cast<float>(Window::HEIGHT),
				   0.1f, 1000.0f);
    _shader.bind();
    _shader.setUniform("projection", _projection);
    _colorPickShader.setUniform("projection", _projection);
  }

  void		Camera::initialize()
  {
    _x = _distance * cos(_phi) * cos(_thetha);
    _y = _distance * cos(_phi) * sin(_thetha);
    _z = _distance * sin(_phi);
    _transformation = glm::lookAt(glm::vec3(_x, _y, _z),
				  glm::vec3(_xFocus, _yFocus, _zFocus),
				  glm::vec3(_xTop, _yTop, _zTop));
    _shader.bind();
    _shader.setUniform("view", _transformation);
    _shader.setUniform("projection", _projection);
    _colorPickShader.bind();
    _colorPickShader.setUniform("view", _transformation);
    _colorPickShader.setUniform("projection", _projection);
  }

  void		Camera::update()
  {
    _x = _xFocus + _distance * cos(_phi) * cos(_thetha);
    _y = _yFocus + _distance * cos(_phi) * sin(_thetha);
    _z = _zFocus + _distance * sin(_phi);
    _transformation = glm::lookAt(glm::vec3(_x, _y, _z),
				  glm::vec3(_xFocus, _yFocus, _zFocus),
				  glm::vec3(_xTop, _yTop, _zTop));
    _shader.bind();
    _shader.setUniform("view", _transformation);
    _shader.setUniform("projection", _projection);
    _colorPickShader.bind();
    _colorPickShader.setUniform("view", _transformation);
    _colorPickShader.setUniform("projection", _projection);
  }

  void		Camera::zoomPlus()
  {
    if (_distance - _distance / 10 > 1)
      _distance -= _distance / 10;
    update();
  }

  void		Camera::zoomLess()
  {
    if (_distance + _distance / 10 < 1000)
      _distance += _distance / 10;
    update();
  }

  void		Camera::rotateVertical(float value)
  {
    if (_phi + value / 100 > 0 && _phi + value / 100 < 3.1415 / 2)
      _phi += value / 100;
    update();
  }

  void		Camera::rotateHorizontal(float value)
  {
    _thetha -= value / 100;
    update();
  }

  void		Camera::setPosition(const glm::vec2& v)
  {
    _x = (v.x) * Map::BLOCK_SIZE;
    _y = (v.y) * Map::BLOCK_SIZE;
    _xFocus = v.x * Map::BLOCK_SIZE;
    _yFocus = v.y * Map::BLOCK_SIZE;
    update();
  }

  void		Camera::translateDrag(float xScreen, float yScreen)
  {
    double deltaX = xScreen * sin(_thetha) - yScreen * cos(_thetha);
    double deltaY = xScreen * cos(_thetha) + yScreen * sin(_thetha);

    _x += deltaX * (_distance / 200);
    _y -= deltaY * (_distance / 200);
    _xFocus += deltaX * (_distance / 200);
    _yFocus -= deltaY * (_distance / 200);
    update();
  }

  void		Camera::perspectiveMode(const std::string& mode)
  {
    if (mode == "2d")
      {
	_projection = glm::ortho(0.0f, static_cast<float>(Window::WIDTH) /
				 static_cast<float>(Window::HEIGHT),
				 0.1f, 100.0f);
	_shader.bind();
	_shader.setUniform("projection", _projection);
	_colorPickShader.bind();
	_colorPickShader.setUniform("projection", _projection);
      }
    else if (mode == "3d")
      {
	_projection = glm::perspective(60.0f,
				       static_cast<float>(Window::WIDTH) /
				       static_cast<float>(Window::HEIGHT),
				       0.1f, 1000.0f);
	_colorPickShader.bind();
	_colorPickShader.setUniform("projection", _projection);
      }
    else
      {
	std::cerr << "Could not apply '" << mode << "' to camera" << std::endl;
      }
  }

  Camera::~Camera()
  {
  }
}
