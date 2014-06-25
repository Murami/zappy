#ifndef		__MONITOR_HH__
# define	__MONITOR_HH__

# include	<stdexcept>
# include	<iostream>
# include	<cstring>
# include	"Window.hh"

namespace			graphic
{
  struct			MapConfig
  {
    int				sizeX;
    int				sizeY;
  };

  class				Monitor
  {
  private :
    MapConfig			_mapConfig;
    Window			_window;

  public :
    void			render();

  public :
    void			setMapSizeX(int);
    void			setMapSizeY(int);
    void			setMapConfig(const struct MapConfig&);

  public :
    int				getMapSizeX() const;
    int				getMapSizeY() const;
    const struct MapConfig&	getMapConfig() const;

  public :
    struct MapConfig&		operator=(struct MapConfig&);

  public :
    Monitor();
    ~Monitor();
  };
}

#endif
