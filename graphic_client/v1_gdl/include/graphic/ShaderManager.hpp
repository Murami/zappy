#ifndef		__SHADERMANAGER_HPP__
# define	__SHADERMANAGER_HPP__

# include	<iostream>
# include	<Texture.hh>
# include	<BasicShader.hh>
# include	<stdexcept>

# define	MAX_PLAYER_LEVEL	7

namespace	Zappy
{
  class		ShaderManager
  {
  private :
    static	ShaderManager*	_instance;

  private :
    gdl::BasicShader	*_basicShader;
    gdl::BasicShader	*_colorPickShader;
    gdl::BasicShader	*_reflectionShader;
    gdl::BasicShader	*_mapShader;
    gdl::BasicShader	*_hudShader;
    gdl::BasicShader	*_playerShaders[MAX_PLAYER_LEVEL];

  public :
    static ShaderManager*	getInstance()
    {
      if (_instance == NULL)
	_instance = new ShaderManager();
      return (_instance);
    }

    gdl::BasicShader*	getHUDShader()
    {
      return (_hudShader);
    }

    gdl::BasicShader*	getMapShader()
    {
      return (_mapShader);
    }

    gdl::BasicShader*	getReflectionShader()
    {
      return (_reflectionShader);
    }

    gdl::BasicShader*	getBasicShader()
    {
      return (_basicShader);
    }

    gdl::BasicShader*	getColorPickShader()
    {
      return (_colorPickShader);
    }

    gdl::BasicShader*	getPlayerShader(int level)
    {
      return (_playerShaders[level - 1]);
    }

  private :
    ShaderManager()
    {
      _reflectionShader = new gdl::BasicShader();
      if (!_reflectionShader->load("./gdl/shaders/reflection.fp", GL_FRAGMENT_SHADER) ||
      	  !_reflectionShader->load("./gdl/shaders/reflection.vp", GL_VERTEX_SHADER) ||
      	  !_reflectionShader->build())
      	throw (std::runtime_error("Failed reflection shader init"));
      _basicShader = new gdl::BasicShader();
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
      _mapShader = new gdl::BasicShader();
      if (!_mapShader->load("./gdl/shaders/map.fp", GL_FRAGMENT_SHADER) ||
	  !_mapShader->load("./gdl/shaders/map.vp", GL_VERTEX_SHADER) ||
	  !_mapShader->build())
	throw (std::runtime_error("Failed map shader init"));
      _hudShader = new gdl::BasicShader();
      if (!_hudShader->load("./gdl/shaders/hud.fp", GL_FRAGMENT_SHADER) ||
	  !_hudShader->load("./gdl/shaders/hud.vp", GL_VERTEX_SHADER) ||
	  !_hudShader->build())
	throw (std::runtime_error("Failed map shader init"));
      for (int i = 0; i < MAX_PLAYER_LEVEL; i++)
	{
	  _playerShaders[i] = new gdl::BasicShader();
	  if (!_playerShaders[i]->load("./gdl/shaders/player.fp", GL_FRAGMENT_SHADER))
	    throw (std::runtime_error("Failed to load player.fp"));
	  if (!_playerShaders[i]->load("./gdl/shaders/player.vp", GL_VERTEX_SHADER))
	    throw (std::runtime_error("Failed to load player.vp"));
	  if (!_playerShaders[i]->build())
	    throw (std::runtime_error("Failed to build player shader"));
	  _playerShaders[i]->bind();
	}
    }

    ~ShaderManager()
    {
    }
  };
}

#endif
