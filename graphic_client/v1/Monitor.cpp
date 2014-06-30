#include		"Connection.hh"
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

  void			Monitor::connect(int argc, char **argv)
  {
    _connection = new Connection(argc, argv, *this);
    _connection->start();
  }

  void			Monitor::render()
  {
    bool		cont = true;

    try
      {
	_window.create(_mapConfig);
      }
    catch (std::runtime_error e)
      {
	std::cerr << e.what() << std::endl;
      }
    while (cont)
      {
	if (_window.update() == Window::QUIT)
	  cont = false;
	_window.draw(_mapConfig);
      }
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
