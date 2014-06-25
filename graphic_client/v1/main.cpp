#include	"Monitor.hh"

int			main()
{
  graphic::Monitor	_monitor;
  graphic::MapConfig	_mapConfig;

  _mapConfig.sizeX = 20;
  _mapConfig.sizeY = 20;
  _monitor.setMapConfig(_mapConfig);
  _monitor.render();
  return (0);
}
