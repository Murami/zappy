#ifndef		__HUD_HH__
# define	__HUD_HH__

# include	<stdexcept>
# include	<Geometry.hh>
# include	<Texture.hh>
# include	"BasicShader.hh"

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
    gdl::BasicShader*	_shader;
    Client*		_client;

  public :
    void	print(Player*, Client&);
    void	hide();
    void	draw();

  public :
    bool	isActive() const;

  public :
    HUD();
    ~HUD();
  };
}

#endif
