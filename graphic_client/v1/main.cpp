//
// main.cpp for zappy in /home/manu/tek2/systeme_unix/zappy/graphic_client/v1
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun 25 09:52:41 2014 Manu
// Last update Wed Jun 25 10:24:22 2014 Manu
//

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
