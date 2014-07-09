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
