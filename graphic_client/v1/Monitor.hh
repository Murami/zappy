#ifndef		__MONITOR_HH__
# define	__MONITOR_HH__

# include	<stdexcept>
# include	<iostream>
# include	<cstring>
# include	"Window.hh"

namespace			graphic
{
  class				Connection;

  struct			MapConfig
  {
    int				sizeX;
    int				sizeY;
    // std::list<AObject*>		items;
  };

  class				Monitor
  {
  private :
    MapConfig			_mapConfig;
    Window			_window;
    Connection*			_connection;

  public :
    void			render();
    void			connect(int, char **);

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
