#ifndef		__SHADERMANAGER_HPP__
# define	__SHADERMANAGER_HPP__

namespace	Zappy
{
  class		ShaderManager
  {
  private :
    static	ShaderManager*	_instance;

  private :
    gdl::BasicShader	*_basicShader;
    gdl::BasicShader	*_colorPickShader;

  public :
    static ShaderManager*	getInstance()
    {
      if (_instance == NULL)
	_instance = new ShaderManager();
      return (_instance);
    }

    gdl::BasicShader*	getBasicShader()
    {
      return (_basicShader);
    }

    gdl::BasicShader*	getColorPickShader()
    {
      return (_colorPickShader);
    }

  private :
    ShaderManager()
    {
      _basicShader = new gdl::BasicShader();
      // if (!_basicShader->load("./reflection.fp", GL_FRAGMENT_SHADER) ||
      // 	  !_basicShader->load("./reflection.vp", GL_VERTEX_SHADER) ||
      // 	  !_basicShader->build())
      // 	throw (std::runtime_error("Failed reflection shader init"));
      if (!_basicShader->load("./gdl/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      	  !_basicShader->load("./gdl/shaders/basic.vp", GL_VERTEX_SHADER) ||
      	  !_basicShader->build())
      	throw (std::runtime_error("Failed basic shader init"));
      _colorPickShader = new gdl::BasicShader();
      if (!_colorPickShader->load("./gdl/shaders/colorPick.fp",
      				  GL_FRAGMENT_SHADER) ||
      	  !_colorPickShader->load("./gdl/shaders/colorPick.vp",
      				  GL_VERTEX_SHADER) ||
      	  !_colorPickShader->build())
      	throw (std::runtime_error("Failed colorPick shader init"));
    }

    ~ShaderManager()
    {
    }
  };
}

#endif
