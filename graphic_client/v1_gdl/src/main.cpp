#include	"network/Client.hh"
#include	"interface/ZappyGraphic.hh"

int		main(int argc, char **argv)
{
  Client	client(argc, argv);

  // try
  //   {
  //     Zappy::ZappyGraphic	zappy(argc, argv);
  //     zappy.run();
  //   }
  // catch (std::runtime_error e)
  //   {
  //     std::cerr << "\033[31m" << e.what() << "\033[0m" << std::endl;
  //     return (-1);
  //   }
  return (0);
}
