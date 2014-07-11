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
    std::map<int, gdl::Model*>	_runningFrames[8];
    int				_currentRunningFrame[8];
    static	AnimationPool*	_instance;
    gdl::Model*			_standingFrame[8];

  public :
    static AnimationPool*	getInstance()
    {
      if (!_instance)
	_instance = new AnimationPool();
      return (_instance);
    }

    gdl::Model*		getStandingFrame(int level)
    {
      return (_standingFrame[level]);
    }

    gdl::Model*		getRunningFrame(int level, int index)
    {
      return (_runningFrames[level][index]);
    }

    gdl::Model*		getNextRunningFrame(int level)
    {
      if (_currentRunningFrame[level] < 18)
	_currentRunningFrame[level]++;
      else
	_currentRunningFrame[level] = 0;
      return (_runningFrames[level][_currentRunningFrame[level]]);
    }

    void		loadModels()
    {
      for (char level = '1'; level < '7'; level++)
	{
	  _currentRunningFrame[level - 49] = 0;
	  gdl::Model* model;
	  std::string modelPath("./assets/models/young_link_");
	  for (int i = 0; i < 19; i++)
	    {
	      model = new gdl::Model();
	      if (!model->load(modelPath + level + std::string(".fbx")))
		{
		  std::cerr << "Error while loading young_link_" << level << ".fbx" << std::endl;
		  return ;
		}
	      model->setCurrentAnim(0);
	      model->createSubAnim(0, "running", i + 10, i + 11);
	      model->setCurrentSubAnim("running");
	      _runningFrames[level - 49][i] = model;
	      usleep(5000);
	    }
	  _standingFrame[level - 49] = new gdl::Model();
	  if (!_standingFrame[level - 49]->load(modelPath + level + std::string(".fbx")))
	    {
	      std::cerr << "Error while loading young_link_" << level << ".fbx" << std::endl;
	      return ;
	    }
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
