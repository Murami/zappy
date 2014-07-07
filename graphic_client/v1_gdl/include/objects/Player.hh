#ifndef		__PLAYER_HH__
# define	__PLAYER_HH__

# include	<stack>
# include	<string>
# include	<Model.hh>
# include	"objects/AObject.hh"
# include	"objects/AnimationPool.hpp"

namespace	Zappy
{
  enum		Direction
    {
      FRONT,
      LEFT,
      BACK,
      RIGHT
    };

  enum		State
    {
      STANDING,
      RUNNING,
      LOOTING,
      CASTING
    };

  class		Player : public AObject
  {
  public :
    const static float	SPEED;

  private :
    gdl::Model*		_model;
    int			_level;
    const std::string&	_teamName;
    Direction		_direction;
    float		_timeUnit;
    int			_elapsed;
    std::stack<State>	_stateStack;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    void		turnLeft();
    void		turnRight();
    void		goForward();
    void		loot();
    void		startCast();
    void		stopCast();
    void		stopRunning();

  public :
    State		getState() const;
    float		getTimeUnit() const;
    void		setTimeUnit(float);

  public :
    Player(int x, int y, const std::string& teamName);
    ~Player();
  };
}

#endif