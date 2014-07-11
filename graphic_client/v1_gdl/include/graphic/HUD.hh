#ifndef		__HUD_HH__
# define	__HUD_HH__

# include	<stdexcept>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"BasicShader.hh"
# include	<SDL2/SDL_ttf.h>

class		Client;

namespace	Zappy
{
  class		Player;

  class		HUD
  {
  private :
    bool		_active;
    Player*		_currentPlayer;
    gdl::Geometry	_frame;
    gdl::Texture	_texture;
    gdl::BasicShader	_shader;
    Client*		_client;
    int			_resources[7];
    TTF_Font*		_font;

  public :
    void	print(Player*, Client&);
    void	hide();
    void	draw();
    void	updateStock(int id, int, int, int, int, int, int, int);

  public :
    bool	isActive() const;

  public :
    HUD();
    ~HUD();
  };
}

#endif
