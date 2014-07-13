//
// ModelManager.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:33 2014 Manu
// Last update Sun Jul 13 23:04:36 2014 Manu
//

#ifndef		__MODELMANAGER_HH__
# define	__MODELMANAGER_HH__

# include	<map>
# include	<stdexcept>
# include	<Model.hh>
# include	"objects/Stone.hh"

namespace	Zappy
{
  class		ModelManager
  {
  private :
    static	ModelManager*	_instance;

  public :
    static ModelManager*	getInstance();

  private :
    std::map<Type, gdl::Model*>	_models;
    gdl::Model*			_food;
    gdl::Model*			_world;
    gdl::Model*			_egg;

  public :
    gdl::Model*		getStone(Type);
    gdl::Model*		getFood();
    gdl::Model*		getWorld();
    gdl::Model*		getEgg();

  private :
    ModelManager();
    ~ModelManager();
  };
}

#endif
