//
// Food.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:50 2014 Manu
// Last update Sun Jul 13 23:04:51 2014 Manu
//

#ifndef		__FOOD_HH__
# define	__FOOD_HH__

# include	<Model.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  class		Food : public AObject
  {
  private :
    int		_x;
    int		_y;
    gdl::Model*	_model;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    int		getX() const;
    int		getY() const;

  public :
    Food(int x, int y);
    ~Food();
  };
}

#endif
