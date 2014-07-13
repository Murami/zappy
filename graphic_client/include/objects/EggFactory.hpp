//
// EggFactory.hpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:56 2014 Manu
// Last update Sun Jul 13 23:04:57 2014 Manu
//

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
