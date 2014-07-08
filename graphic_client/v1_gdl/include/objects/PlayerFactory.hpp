#ifndef		__PLAYERFACTORY_HPP__
# define	__PLAYERFACTORY_HPP__

# include	<glm/gtc/matrix_transform.hpp>

namespace	Zappy
{
  class		PlayerFactory
  {
  public :
    static Player*	createNewPlayer(int x, int y, const std::string& tName)
    {
      static int	next[4];
      static bool	init = false;

      if (!init)
	{
	  next[0] = 255;
	  next[1] = 255;
	  next[2] = 255;
	  next[3] = 255;
	  init = true;
	  return (new Player(x, y, tName, glm::vec4(1, 1, 1, 1)));
	}
      if (next[0] <= 0)
	{
	  next[0] = 255;
	  if (next[1] <= 0)
	    {
	      next[1] = 255;
	      if (next[2] <= 0)
		next[2] = 255;
	      else
		next[2] -= 5;
	    }
	  else
	    next[1] -= 5;
	}
      else
	next[0] -= 5;

      return (new Player(x, y, tName, glm::vec4(next[0] / 255,
						next[1] / 255,
						next[2] / 255,
						next[3] / 255)));
    }
  };
}

#endif
