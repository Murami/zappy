#include	"interface/ZappyGraphic.hh"
#include	"objects/AnimationPool.hpp"

Zappy::AnimationPool*	Zappy::AnimationPool::_instance = NULL;

int		main(int argc, char **argv)
{
  try
    {
      Zappy::ZappyGraphic	zappy(argc, argv);
      zappy.run();
    }
  catch (std::runtime_error e)
    {
      std::cerr << "\033[31m" << e.what() << "\033[0m" << std::endl;
      return (-1);
    }
  return (0);
}
