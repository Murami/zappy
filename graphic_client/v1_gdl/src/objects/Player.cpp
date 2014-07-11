#include		"objects/ModelManager.hh"
#include		"objects/Player.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  const float	Player::SPEED = 1.0f;

  Player::Player(int playerId, int x, int y, int orientation,
		 int level, int limitX, int limitY, const std::string& name,
		 const glm::vec4& pickColor) : _teamName(name)
  {
    _limitX = limitX;
    _limitY = limitY;
    _id = playerId;
    _pickColor = pickColor;
    _level = level;
    translate(glm::vec3(x * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2,
			y * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2, 0));
    _stateStack.push(STANDING);
    _orientation = static_cast<Orientation>(orientation);
    rotate(glm::vec3(1, 0, 0), 90);
    _timeUnit = 100;
    _elapsed = 0;
    _x = x;
    _y = y;
    _alive = true;
    _dying = false;
  }

  bool		Player::isAlive() const
  {
    return (_alive);
  }

  int		Player::getY() const
  {
    return (_y);
  }

  void		Player::die()
  {
    _dying = true;
    rotate(glm::vec3(1, 0, 0), -90);
  }

  void		Player::setOrientation(Orientation dir)
  {
    int exDir = static_cast<int>(_orientation);
    int newDir = static_cast<int>(dir);
    _orientation = dir;
    if (exDir == 1 && newDir == 4)
      {
	turnLeft();
      }
    else if (exDir == 4 && newDir == 1)
      {
	turnRight();
      }
    else if ((exDir < newDir && (exDir != 1 || newDir != 4)))
      {
	turnRight();
      }
    else if (((exDir > newDir) && (exDir != 4 || newDir != 1)))
      {
	turnLeft();
      }
  }

  Orientation	Player::getOrientation() const
  {
    return (_orientation);
  }

  void		Player::setPosition(int x, int y)
  {
    _x = x;
    _y = y;
    _position.x = x * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2;
    _position.y = y * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2;
  }

  void		Player::setLevel(int lvl)
  {
    _level = lvl;
  }

  int		Player::getX() const
  {
    return (_x);
  }

  int		Player::getLevel() const
  {
    return (_level);
  }

  const std::string&	Player::getTeamName() const
  {
    return (_teamName);
  }

  int		Player::getId() const
  {
    return (_id);
  }

  const glm::vec4& Player::getPickColor() const
  {
    return (_pickColor);
  }

  void		Player::initialize()
  {
    _model = AnimationPool::getInstance()->getStandingFrame(_level);
    rotate(glm::vec3(0, 1, 0), (_orientation - 1) * 90);
  }

  State		Player::getState() const
  {
    return (_stateStack.top());
  }

  void		Player::turnLeft()
  {
    rotate(glm::vec3(0, 1, 0), -90);
  }

  void		Player::turnRight()
  {
    rotate(glm::vec3(0, 1, 0), 90);
  }

  void		Player::goForward()
  {
    if (_stateStack.top() == STANDING)
      {
	_stateStack.pop();
	_stateStack.push(RUNNING);
      }
    else
      _stateStack.push(RUNNING);
  }

  void		Player::loot()
  {
    if (_stateStack.top() == STANDING)
      {
	_stateStack.pop();
	_stateStack.push(LOOTING);
      }
    else
      _stateStack.push(LOOTING);
  }

  void		Player::startCast()
  {
    if (_stateStack.top() == STANDING)
      {
	_stateStack.pop();
	_stateStack.push(CASTING);
      }
    else
      _stateStack.push(CASTING);
  }

  void		Player::update(const gdl::Clock&, gdl::Input&)
  {
    if (!_dying)
      {
	switch (_stateStack.top())
	  {
	  case RUNNING :
	    switch (_orientation)
	      {
	      case NORTH :
		translate(glm::vec3(0, -Player::SPEED, 0));
		if (_position.y < 0)
		  _position.y = (_limitY - 1) * Map::BLOCK_SIZE + Map::BLOCK_SIZE;
		break;
	      case EAST :
		translate(glm::vec3(Player::SPEED, 0, 0));
		if (_position.x > Map::BLOCK_SIZE * _limitX)
		  _position.x = 0;
		break;
	      case SOUTH :
		translate(glm::vec3(0, Player::SPEED, 0));
		if (_position.y > Map::BLOCK_SIZE * _limitY)
		  _position.y = 0;
		break;
	      case WEST :
		translate(glm::vec3(-Player::SPEED, 0, 0));
		if (_position.x < 0)
		  _position.x = (_limitX - 1) * Map::BLOCK_SIZE + Map::BLOCK_SIZE;
		break;
	      }
	    _model = AnimationPool::getInstance()->getNextRunningFrame(_level);
	    if (_model == NULL)
	      std::cerr << "WARNING : MODEL TO DRAW IS NULL" << std::endl;
	    _elapsed++;
	    if (_elapsed == Map::BLOCK_SIZE)
	      {
		stopRunning();
		_elapsed = 0;
	      }
	    break;
	  case LOOTING :
	    break;
	  case CASTING :
	    break;
	  case STANDING :
	    break;
	  case GHOST :
	    break;
	  }
      }
    else
      {
	_elapsed++;
	if (_elapsed == 25)
	  {
	    _alive = false;
	    _elapsed = 0;
	  }
      }
  }

  void		Player::stopRunning()
  {
    _x = (int) _position.x / Map::BLOCK_SIZE;
    _y = (int) _position.y / Map::BLOCK_SIZE;
    _stateStack.pop();
    _stateStack.push(STANDING);
    _model = AnimationPool::getInstance()->getStandingFrame(_level);
  }

  void		Player::setTimeUnit(float time)
  {
    _timeUnit = time;
  }

  float		Player::getTimeUnit() const
  {
    return (_timeUnit);
  }

  void		Player::draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    _model->draw(shader, getTransformation(), clock.getElapsed());
  }

  Player::~Player()
  {
  }
}
