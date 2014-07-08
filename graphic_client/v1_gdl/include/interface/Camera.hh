#ifndef		__CAMERA_HH__
# define	__CAMERA_HH__

# include	<iostream>
# include	<glm/gtc/matrix_transform.hpp>
# include	<AShader.hh>

namespace	Zappy
{
  class		Camera
  {
  private :
    float		_x;
    float		_y;
    float		_z;
    float		_xFocus;
    float		_yFocus;
    float		_zFocus;
    float		_xTop;
    float		_yTop;
    float		_zTop;
    float		_thetha;
    float		_phi;
    float		_distance;
    glm::mat4		_transformation;
    glm::mat4		_projection;
    gdl::AShader&	_shader;
    GLuint		_selectBuffer[512];

  public :
    void	initialize();

  public :
    void	zoomPlus();
    void	zoomLess();
    void	rotateVertical(float value);
    void	rotateHorizontal(float value);
    void	translateDrag(float xScreen, float yScreen);
    void	setPosition(const glm::vec2&);

  public :
    void	update();
    void	perspectiveMode(const std::string& mode);

  public :
    void	setMapWidth(int);
    void	setMapHeight(int);

  public :
    Camera(gdl::AShader&);
    ~Camera();
  };
}

#endif
