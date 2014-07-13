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
    //_stateStack.push(STANDING);
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
    _model = AnimationPool::getInstance()->getStandingFrame();
    rotate(glm::vec3(0, 1, 0), (_orientation - 1) * 90);
  }

  State		Player::getState() const
  {
    return (_state);
    //return (_stateStack.top());
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
    // if (_stateStack.top() == STANDING)
    //   {
    // 	_stateStack.pop();
    // 	_stateStack.push(RUNNING);
    //   }
    // else
    //   _stateStack.push(RUNNING);
    _state = RUNNING;
  }

  void		Player::loot()
  {
    // if (_stateStack.top() == STANDING)
    //   {
    // 	_stateStack.pop();
    // 	_stateStack.push(LOOTING);
    //   }
    // else
    //   _stateStack.push(LOOTING);
    _state = LOOTING;
  }

  void		Player::stopCast()
  {
    // if (_stateStack.top() == CASTING)
    //   {
    // 	_stateStack.pop();
    // 	_stateStack.push(STANDING);
	_model = AnimationPool::getInstance()->getStandingFrame();
      // }
	_state = STANDING;
  }

  void		Player::startCast()
  {
    // if (_stateStack.top() == STANDING)
    //   {
    // 	_stateStack.pop();
    // 	_stateStack.push(CASTING);
    //   }
    // else
    //   _stateStack.push(CASTING);
    _state = CASTING;
    _model = AnimationPool::getInstance()->getCastingFrame();
  }

  void		Player::update(const gdl::Clock&, gdl::Input&)
  {
    if (!_dying)
      {
	switch (_state)
	  //switch (_stateStack.top())
	  {
	  case RUNNING :

	    switch (_orientation)
	      {
	      case NORTH :
	      	translate(glm::vec3(0, -Player::SPEED * Map::BLOCK_SIZE, 0));
	      	if (_position.y <= 0)
	      	  _position.y = _limitY * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
		stopRunning();
	      	break;
	      case EAST :
	      	translate(glm::vec3(Player::SPEED * Map::BLOCK_SIZE, 0, 0));
	      	if (_position.x > Map::BLOCK_SIZE * _limitX)
	      	  _position.x = Map::BLOCK_SIZE / 2;
		stopRunning();
	      	break;
	      case SOUTH :
	      	translate(glm::vec3(0, Player::SPEED * Map::BLOCK_SIZE, 0));
	      	if (_position.y > Map::BLOCK_SIZE * _limitY)
	      	  _position.y = Map::BLOCK_SIZE / 2;
		stopRunning();
	      	break;
	      case WEST :
	      	translate(glm::vec3(-Player::SPEED * Map::BLOCK_SIZE, 0, 0));
	      	if (_position.x <= 0)
	      	  _position.x = _limitX * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2;
		stopRunning();
	      	break;
	      }

	    //_model = AnimationPool::getInstance()->getNextRunningFrame();

	    // if (_model == NULL)
	    //   std::cerr << "WARNING : MODEL TO DRAW IS NULL" << std::endl;
	    _elapsed++;
	    // if (_elapsed == Map::BLOCK_SIZE)
	    //   {
	    // 	stopRunning();
	    // 	_elapsed = 0;
	    //   }

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
    _x = static_cast<int>(_position.x) / Map::BLOCK_SIZE;
    _y = static_cast<int>(_position.y) / Map::BLOCK_SIZE;
    // _stateStack.pop();
    // _stateStack.push(STANDING);
    _state = STANDING;
    _model = AnimationPool::getInstance()->getStandingFrame();
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
