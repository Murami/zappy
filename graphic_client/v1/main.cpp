#include	"Monitor.hh"

int			main(int argc, char **argv)
{
  graphic::Monitor	_monitor;
  //graphic::MapConfig	_mapConfig;

  try
    {
      _monitor.connect(argc, argv);
      _monitor.render();
    }
  catch (std::runtime_error e)
    {
      std::cerr << e.what() << std::endl;
      return (-1);
    }
  // _mapConfig.sizeX = 20;
  // _mapConfig.sizeY = 20;
  // _monitor.setMapConfig(_mapConfig);
  // _monitor.render();
  return (0);
}
