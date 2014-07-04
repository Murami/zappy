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

  public :
    gdl::Model*		getModel(Type);

  private :
    ModelManager();
    ~ModelManager();
  };
}

#endif
