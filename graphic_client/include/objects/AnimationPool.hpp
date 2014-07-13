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
    gdl::Model*			_castingFrame[10];
    int				_currentCastingFrame;
    gdl::Model*			_lastModel;
    std::map<int, gdl::Model*>	_forkingFrames;
    int				_currentForkingFrame;

  public :
    static AnimationPool*	getInstance()
    {
      if (!_instance)
	_instance = new AnimationPool();
      return (_instance);
    }

    gdl::Model*		getStandingFrame(int level)
    {
      if (level < 8)
	return (_standingFrame);
      return (_lastModel);
    }

    gdl::Model*		getRunningFrame(int index)
    {
      return (_runningFrames[index]);
    }

    gdl::Model*		getCastingFrame(int ndx)
    {
      return (_castingFrame[ndx]);
    }

    void		resetCast()
    {
      _currentCastingFrame = 0;
    }

    gdl::Model*		getNextCastingFrame()
    {
      if (_currentCastingFrame < 9)
	return (_castingFrame[_currentCastingFrame++]);
      else
	return (_castingFrame[8]);
    }

    gdl::Model*		getNextRunningFrame()
    {
      int size = _runningFrames.size();
      if (_currentRunningFrame < size - 1)
	_currentRunningFrame++;
      else
	_currentRunningFrame = 0;
      return (_runningFrames[_currentRunningFrame]);
    }

    gdl::Model*		getNextForkingFrame()
    {
      int size = _forkingFrames.size();
      if (_currentForkingFrame < size - 1)
	_currentForkingFrame++;
      else
	_currentForkingFrame = 0;
      return (_forkingFrames[_currentForkingFrame]);
    }

    void		loadModels()
    {
      _currentCastingFrame = 0;
      _currentForkingFrame = 0;
      _currentRunningFrame = 0;
      gdl::Model* model;
      for (int i = 0; i < 19; i++)
	{
	  model = new gdl::Model();
	  if (!model->load("./assets/models/young_link_1.fbx"))
	    throw (std::runtime_error("Error while loading running frames"));
	  model->setCurrentAnim(0);
	  model->createSubAnim(0, "running", i + 10, i + 11);
	  model->setCurrentSubAnim("running");
	  _runningFrames[i] = model;
	  usleep(5000);
	}
      _standingFrame = new gdl::Model();
      if (!_standingFrame->load("./assets/models/young_link_1.fbx"))
	throw (std::runtime_error("Error while laoding standing frame"));
      _lastModel = new gdl::Model();
      if (!_lastModel->load("./assets/link_adult/adult.fbx"))
	throw (std::runtime_error("Error while loading model for last level"));

      for (int i = 0; i < 9; i++)
	{
	  model = new gdl::Model();
	  if (!model->load("./assets/models/young_link_1.fbx"))
	    throw (std::runtime_error("Error while loading forking frames"));
	  model->setCurrentAnim(0);
	  model->createSubAnim(0, "forking", i + 60, i + 61);
	  model->setCurrentSubAnim("forking");
	  _forkingFrames[i] = model;
	  usleep(5000);
	}
      for (int i = 1; i < 10; i++)
	{
	  model = new gdl::Model();
	  if (!model->load("./assets/models/young_link_1.fbx"))
	    throw (std::runtime_error("Error while loading forking frames"));
	  model->setCurrentAnim(0);
	  model->createSubAnim(0, "casting", i + 30, i + 31);
	  model->setCurrentSubAnim("casting");
	  _castingFrame[i-1] = model;
	  std::cout << "\033[31mCREATE CAST FRAME " << i+30 << "-" << i+31 << " i - 1 = " << i - 1 << std::endl;
	  usleep(5000);
	}

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
