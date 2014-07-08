#ifndef		__WORLD_HH__
# define	__WORLD_HH__

# include	<Model.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  class		World : public AObject
  {
  private :
    gdl::Model*	_model;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    World();
    ~World();
  };
}

#endif
