#include		"objects/ModelManager.hh"
#include		"objects/Player.hh"
#include		"objects/Map.hh"
#include		"graphic/ShaderManager.hpp"

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
    _state = STANDING;
    _stateStack.push(STANDING);
    _orientation = static_cast<Orientation>(orientation);
    rotate(glm::vec3(1, 0, 0), 90);
    _timeUnit = 100;
    _elapsed = 0;
    _x = x;
    _y = y;
    _alive = true;
    _dying = false;
    _shader = *ShaderManager::getInstance()->getPlayerShader(_level);
    _eggId = -1;
    _moveFunc[STANDING] = &Player::stand;
    _moveFunc[FORKING] = &Player::fork;
    _moveFunc[RUNNING] = &Player::move;
    _moveFunc[LOOTING] = &Player::loot;
    _moveFunc[DROPING] = &Player::drop;
    _moveFunc[CASTING] = &Player::cast;
    _dirMoveFunc[NORTH] = &Player::north;
    _dirMoveFunc[SOUTH] = &Player::south;
    _dirMoveFunc[EAST] = &Player::east;
    _dirMoveFunc[WEST] = &Player::west;
  }

  void		Player::setEggId(int id)
  {
    _eggId = id;
  }

  int		Player::getEggId() const
  {
    return (_eggId);
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
    if ((exDir - newDir) % 2 == 0)
      rotate(glm::vec3(0, 1, 0), 180);
    else if (exDir == 1 && newDir == 4)
      turnLeft();
    else if (exDir == 4 && newDir == 1)
      turnRight();
    else if ((exDir < newDir && (exDir != 1 || newDir != 4)))
      turnRight();
    else if (((exDir > newDir) && (exDir != 4 || newDir != 1)))
      turnLeft();
  }

  Orientation	Player::getOrientation() const
  {
    return (_orientation);
  }

  void		Player::setPosition(int x, int y)
  {
    _x = x;
    _y = y;
    translate(glm::vec3(x * Map::BLOCK_SIZE + Map::BLOCK_SIZE,
			y * Map::BLOCK_SIZE + Map::BLOCK_SIZE, 0));
  }

  void		Player::setLevel(int lvl)
  {
    _level = lvl;
    _shader = *ShaderManager::getInstance()->getPlayerShader(lvl);
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

  void		Player::setId(int id)
  {
    _id = id;
  }

  void		Player::setTeamName(const std::string& team)
  {
    _teamName = team;
  }

  void		Player::goForward()
  {
    _stateStack.push(RUNNING);
    _state = RUNNING;
    _elapsed = 0;
  }

  void		Player::loot()
  {
    _stateStack.push(LOOTING);
    _state = LOOTING;
    _elapsed = 0;
  }

  void		Player::stopCast()
  {
    _stateStack.pop();
    if (_stateStack.size() == 0)
      _stateStack.push(STANDING);
    _model = AnimationPool::getInstance()->getStandingFrame(_level);
    _state = STANDING;
    AnimationPool::getInstance()->resetCast();
  }

  void		Player::startCast()
  {
    _stateStack.push(CASTING);
    _state = CASTING;
    _model = AnimationPool::getInstance()->getNextCastingFrame();
    _elapsed = 0;
  }

  void		Player::update(const gdl::Clock&, gdl::Input&)
  {
    if (!_dying)
      (this->*this->_moveFunc[_stateStack.top()])();
    else
      {
	_elapsed++;
	if (_elapsed == 50)
	  {
	    _alive = false;
	    _elapsed = 0;
	  }
      }
  }

  void		Player::north()
  {
    if (_timeUnit <= 10)
      {
	translate(glm::vec3(0, -Player::SPEED, 0));
	if (_position.y <= 0)
	  _position.y = _limitY * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
      }
    else
      {
	translate(glm::vec3(0, -Player::SPEED * Map::BLOCK_SIZE, 0));
	if (_position.y <= 0)
	  _position.y = _limitY * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
	stopRunning();
      }
  }

  void		Player::south()
  {
    if (_timeUnit <= 10)
      {
	translate(glm::vec3(0, Player::SPEED, 0));
	if (_position.y > Map::BLOCK_SIZE * _limitY)
	  _position.y = Map::BLOCK_SIZE / 2;
      }
    else
      {
	translate(glm::vec3(0, Player::SPEED * Map::BLOCK_SIZE, 0));
	if (_position.y > Map::BLOCK_SIZE * _limitY)
	  _position.y = Map::BLOCK_SIZE / 2;
	stopRunning();
      }
  }

  void		Player::east()
  {
    if (_timeUnit <= 10)
      {
	translate(glm::vec3(Player::SPEED, 0, 0));
	if (_position.x > Map::BLOCK_SIZE * _limitX)
	  _position.x = Map::BLOCK_SIZE / 2;
      }
    else
      {
	translate(glm::vec3(Player::SPEED * Map::BLOCK_SIZE, 0, 0));
	if (_position.x > Map::BLOCK_SIZE * _limitX)
	  _position.x = Map::BLOCK_SIZE / 2;
	stopRunning();
      }
  }

  void		Player::west()
  {
    if (_timeUnit <= 10)
      {
	translate(glm::vec3(-Player::SPEED, 0, 0));
	if (_position.x <= 0)
	  _position.x = _limitX * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
      }
    else
      {
	translate(glm::vec3(-Player::SPEED * Map::BLOCK_SIZE, 0, 0));
	if (_position.x <= 0)
	  _position.x = _limitX * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
	stopRunning();
      }
  }

  void		Player::move()
  {
    (this->*this->_dirMoveFunc[_orientation])();
    _model = AnimationPool::getInstance()->getNextRunningFrame();
    _elapsed++;
    if (_elapsed >= Map::BLOCK_SIZE)
      {
	stopRunning();
	_elapsed = 0;
      }
  }

  void		Player::cast()
  {
    if (_timeUnit <= 10)
      _model = AnimationPool::getInstance()->getNextCastingFrame();
    else
      _model = AnimationPool::getInstance()->getCastingFrame(8);
  }

  void		Player::fork()
  {
    _model = AnimationPool::getInstance()->getNextForkingFrame();
    _elapsed++;
    if (_elapsed == 10)
      _elapsed = 0;
  }

  void		Player::looting()
  {
  }

  void		Player::drop()
  {
  }

  void		Player::stand()
  {
    _model = AnimationPool::getInstance()->getStandingFrame(_level);
  }

  void		Player::startForking()
  {
    _stateStack.push(FORKING);
  }

  void		Player::stopForking()
  {
    _model = AnimationPool::getInstance()->getStandingFrame(_level);
    _stateStack.pop();
    _stateStack.push(STANDING);
  }

  void		Player::stopRunning()
  {
    _x = static_cast<int>(_position.x) / Map::BLOCK_SIZE;
    _y = static_cast<int>(_position.y) / Map::BLOCK_SIZE;
    _position.x = _x * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2;
    _position.y = _y * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2;
    std::cout << _x << "  " << _y << std::endl << std::endl;
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

  void		Player::drawColorLevel()
  {
    _shader = *ShaderManager::getInstance()->getPlayerShader(_level);
    _model->draw(_shader, getTransformation(), 0);
  }

  Player::~Player()
  {
  }
}
