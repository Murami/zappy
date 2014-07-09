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
    gdl::Model*	_model;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    Egg(int, int);
    ~Egg();
  };
}

#endif
