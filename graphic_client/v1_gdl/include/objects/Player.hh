#ifndef		__PLAYER_HH__
# define	__PLAYER_HH__

# include	<stack>
# include	<string>
# include	<Model.hh>
# include	"objects/AObject.hh"
# include	"objects/AnimationPool.hpp"
# include	"BasicShader.hh"

namespace	Zappy
{
  enum		Direction
    {
      FRONT = 0,
      LEFT = 1,
      BACK = 2,
      RIGHT = 3
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
    glm::vec4		_pickColor;
    gdl::BasicShader	_colorPickShader;
    int			_id;
    int			_x;
    int			_y;

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
    const glm::vec4&	getPickColor() const;

  public :
    int			getId() const;
    int			getLevel() const;
    const std::string&	getTeamName() const;
    int			getX() const;
    int			getY() const;

  public :
    void		setLevel(int);
    void		setPosition(int, int);
    void		setOrientation(Direction);

  public :
    State		getState() const;
    float		getTimeUnit() const;
    void		setTimeUnit(float);

  public :
    Player(int playerId, int x, int y, int orientation, int level, const std::string& teamName, const glm::vec4& pickColor);
    ~Player();
  };
}

#endif
