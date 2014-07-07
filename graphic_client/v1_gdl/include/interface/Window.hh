#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

# include	<stdexcept>
# include	<string>
# include	"glm/glm.hpp"
# include	"glm/gtc/matrix_transform.hpp"
# include	"Clock.hh"
# include	"Input.hh"
# include	"SdlContext.hh"
# include	"BasicShader.hh"

namespace	Zappy
{
  class		AObject;
  class		Camera;

  class		Window
  {
  public :
    const static float		WIDTH;
    const static float		HEIGHT;
    const static std::string	TITLE;

  public :
    gdl::SdlContext	_context;

  private :
    gdl::BasicShader	_shader;
    gdl::Input		_input;
    gdl::Clock		_clock;
    bool		_running;
    Camera*		_camera;

  private :
    void	_handleMouseEvents();

  public :
    gdl::Input&	getInputs();
    void	create(int w, int h, const std::string& title);
    bool	isRunning() const;
    void	update();
    void	flush();
    void	draw(AObject*);
    void	bindShader();
    Camera*	getCamera();
    void	updateObject(AObject*);

  public :
    Window();
    ~Window();
  };
}

#endif
