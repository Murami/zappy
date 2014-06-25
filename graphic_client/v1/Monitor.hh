//
// Monitor.hh for zappy in /home/manu/tek2/systeme_unix/zappy/graphic_client/v1
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Wed Jun 25 10:06:12 2014 Manu
// Last update Wed Jun 25 10:27:28 2014 Manu
//

#ifndef		__MONITOR_HH__
# define	__MONITOR_HH__

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
