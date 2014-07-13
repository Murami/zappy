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
  enum		Orientation
    {
      NORTH = 1,
      EAST = 2,
      SOUTH = 3,
      WEST = 4
    };

  enum		State
    {
      STANDING,
      RUNNING,
      LOOTING,
      CASTING,
      GHOST,
    };

  class		Player : public AObject
  {
  public :
    const static float	SPEED;

  private :
    gdl::Model*		_model;
    int			_level;
    std::string		_teamName;
    Orientation		_orientation;
    float		_timeUnit;
    int			_elapsed;
    State		_state;
    //std::stack<State>	_stateStack;
    glm::vec4		_pickColor;
    gdl::BasicShader	_colorPickShader;
    int			_id;
    int			_x;
    int			_y;
    int			_limitX;
    int			_limitY;
    bool		_alive;
    bool		_dying;
    gdl::BasicShader	_shader;
    int			_eggId;

  public :
    void		setId(int);
    void		setTeamName(const std::string&);

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);
    void		drawColorLevel();

  public :
    void		turnLeft();
    void		turnRight();
    void		goForward();
    void		loot();
    void		startCast();
    void		stopCast();
    void		stopRunning();
    const glm::vec4&	getPickColor() const;
    void		goingTo(int, int);
    void		die();
    void		setEggId(int);
    int			getEggId() const;

  public :
    int			getId() const;
    int			getLevel() const;
    const std::string&	getTeamName() const;
    int			getX() const;
    int			getY() const;
    Orientation		getOrientation() const;
    bool		isAlive() const;

  public :
    void		setLevel(int);
    void		setPosition(int, int);
    void		setOrientation(Orientation);

  public :
    State		getState() const;
    float		getTimeUnit() const;
    void		setTimeUnit(float);

  public :
    Player(int playerId, int x, int y, int orientation,
	   int level, int limitX, int limitY, const std::string& teamName,
	   const glm::vec4& pickColor);
    ~Player();
  };
}

#endif
