//
// World.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:05 2014 Manu
// Last update Sun Jul 13 23:04:06 2014 Manu
//

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
    void		setMapSize(int, int);

  public :
    World();
    ~World();
  };
}

#endif
