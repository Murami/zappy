#ifndef		__EGG_HH__
# define	__EGG_HH__

# include	"objects/AObject.hh"

namespace	gdl
{
  class		Model;
}

namespace	Zappy
{
  class		Egg : public AObject
  {
  private :
    int		_playerId;
    int		_id;
    gdl::Model*	_model;
    int		_x;
    int		_y;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    int		getId() const;
    int		getPlayerId() const;
    int		getX() const;
    int		getY() const;

  public :
    Egg(int playerId, int eggId, int x, int y);
    ~Egg();
  };
}

#endif
