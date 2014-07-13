#ifndef		__ANIMATIONPOOL_HPP__
# define	__ANIMATIONPOOL_HPP__

# include	<stdexcept>
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
    gdl::Model*			_castingFrame;

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

    gdl::Model*		getCastingFrame()
    {
      return (_castingFrame);
    }

    gdl::Model*		getNextRunningFrame()
    {
      if (_currentRunningFrame < 18)
	_currentRunningFrame++;
      else
	_currentRunningFrame = 0;
      return (_runningFrames[_currentRunningFrame]);
    }

    void		loadModels()
    {
      _currentRunningFrame = 0;
      gdl::Model* model;
      for (int i = 0; i < 19; i++)
	{
	  model = new gdl::Model();
	  if (!model->load("./assets/models/young_link_1.fbx"))
	    {
	      std::cerr << "Error while loading young_link_1.fbx" << std::endl;
	      return ;
	    }
	  model->setCurrentAnim(0);
	  model->createSubAnim(0, "running", i + 10, i + 11);
	  model->setCurrentSubAnim("running");
	  _runningFrames[i] = model;
	  usleep(5000);
	}
      _standingFrame = new gdl::Model();
      if (!_standingFrame->load("./assets/models/young_link_1.fbx"))
	throw (std::runtime_error("Error while laoding standing frame"));
      _castingFrame = new gdl::Model();
      if (!_castingFrame->load("./assets/models/young_link_1.fbx"))
	throw (std::runtime_error("Error while laoding casting frame"));
      _castingFrame->setCurrentAnim(0);
      _castingFrame->createSubAnim(0, "cast", 50, 50);
      _castingFrame->setCurrentSubAnim("cast");
    }

  private :
    AnimationPool()
    {
    }

    ~AnimationPool()
    {
    }
  };
}

#endif
