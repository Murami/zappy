//
// HUD.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/graphic
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:03:14 2014 Manu
// Last update Sun Jul 13 23:03:15 2014 Manu
//

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
  class		Window;
  class		Sentence;

  class		HUD
  {
  private :
    bool		_active;
    Player*		_currentPlayer;
    gdl::Geometry	_frame;
    gdl::Texture	_texture;
    gdl::BasicShader	_shader;
    Client*		_client;
    Window*		_window;
    int			_resources[7];

  private :
    void	_printResources();
    void	_printLife();
    void	_printLevel();
    void	_printTeam();

  public :
    void	print(Player*, Client&, Window&);
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
