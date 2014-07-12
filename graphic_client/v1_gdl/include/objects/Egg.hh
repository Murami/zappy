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
    int		_id;
    gdl::Model*	_model;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    int		getId() const;

  public :
    Egg(int id, int x, int y);
    ~Egg();
  };
}

#endif
