#ifndef		__WINDOW_HH__
# define	__WINDOW_HH__

namespace	graphic
{
  class		Window
  {
  public :
    const static int	WINDOW_X;
    const static int	WINDOW_Y;

  public :
    void	create();

  public :
    Window();
    ~Window();
  };
}

#endif
