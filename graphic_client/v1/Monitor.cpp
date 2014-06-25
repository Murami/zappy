//
// Monitor.cpp for zappy in /home/manu/tek2/systeme_unix/zappy/graphic_client/v1
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun 25 10:06:15 2014 Manu
// Last update Wed Jun 25 10:27:37 2014 Manu
//

#include		"Monitor.hh"

namespace		graphic
{
  Monitor::Monitor()
  {
    memset(&_mapConfig, 0, sizeof(_mapConfig));
  }

  struct MapConfig&	Monitor::operator=(struct MapConfig& config)
  {
    _mapConfig.sizeX = config.sizeX;
    _mapConfig.sizeY = config.sizeY;
    return (_mapConfig);
  }

  void			Monitor::render()
  {
  }

  void			Monitor::setMapConfig(const struct MapConfig& mapConfig)
  {
    _mapConfig = mapConfig;
  }

  void			Monitor::setMapSizeX(int x)
  {
    _mapConfig.sizeX = x;
  }

  void			Monitor::setMapSizeY(int y)
  {
    _mapConfig.sizeY = y;
  }

  int			Monitor::getMapSizeX() const
  {
    return (_mapConfig.sizeX);
  }

  int			Monitor::getMapSizeY() const
  {
    return (_mapConfig.sizeY);
  }

  Monitor::~Monitor()
  {
  }
}
