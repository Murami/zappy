//
// PlayerFactory.hpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:21 2014 Manu
// Last update Sun Jul 13 23:04:21 2014 Manu
//

#ifndef		__PLAYERFACTORY_HPP__
# define	__PLAYERFACTORY_HPP__

# include	<iostream>
# include	<glm/gtc/matrix_transform.hpp>

namespace	Zappy
{
  class		PlayerFactory
  {
  public :
    static Player*	createNewPlayer(int playerId, int x, int y,
					int orientation, int level,
					int limitX, int limitY,
					const std::string& tName)
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
      return (new Player(playerId, x, y, orientation, level,
			 limitX, limitY, tName, glm::vec4(static_cast<float>(next[0]) / 255.0f,
							  static_cast<float>(next[1]) / 255.0f,
							  static_cast<float>(next[2]) / 255.0f,
							  1.0f)));
    }
  };
}

#endif
