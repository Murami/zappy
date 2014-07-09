#ifndef		__ANIMATIONPOOL_HPP__
# define	__ANIMATIONPOOL_HPP__

# include	<unistd.h>
# include	<map>
# include	<Model.hh>

namespace	Zappy
{
  class		AnimationPool
  {
  private :
    std::map<int, gdl::Model*>	_runningFrames;
    int				_currentRunningFrame;
    static	AnimationPool*	_instance;
    gdl::Model*			_standingFrame;

  public :
    static AnimationPool*	getInstance()
    {
      if (!_instance)
	_instance = new AnimationPool();
      return (_instance);
    }

    gdl::Model*		getStandingFrame()
    {
      return (_standingFrame);
    }

    gdl::Model*		getRunningFrame(int index)
    {
      return (_runningFrames[index]);
    }

    gdl::Model*		getNextRunningFrame()
    {
      if (_currentRunningFrame < 18)
	_currentRunningFrame++;
      else
	_currentRunningFrame = 0;
      return (_runningFrames[_currentRunningFrame]);
    }

  private :
    AnimationPool()
    {
      _currentRunningFrame = 0;
      gdl::Model* model;
      for (int i = 0; i < 19; i++)
	{
	  model = new gdl::Model();
	  if (!model->load("./assets/models/young_link.fbx"))
	    {
	      std::cerr << "Error while loading young_link.fbx" << std::endl;
	      return ;
	    }
	  model->setCurrentAnim(0);
	  model->createSubAnim(0, "running", i + 10, i + 11);
	  model->setCurrentSubAnim("running");
	  _runningFrames[i] = model;
	  usleep(5000);
	}
      _standingFrame = new gdl::Model();
      _standingFrame->load("./assets/models/young_link.fbx");
    }

    ~AnimationPool()
    {
    }
  };
}

#endif
