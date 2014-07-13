#ifndef		__EGGFACTORY_HPP__
# define	__EGGFACTORY_HPP__

# include	"objects/Egg.hh"

namespace	Zappy
{
  class		EggFactory
  {
  public :
    static Egg*	createNewEgg(int eggId, int playerId, int x, int y)
    {
      Egg* egg = new Egg(playerId, eggId, x, y);
      egg->initialize();
      return (egg);
    }
  };
}

#endif
