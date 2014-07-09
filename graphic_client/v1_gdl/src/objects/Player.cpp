#include		"objects/ModelManager.hh"
#include		"objects/Player.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  const float	Player::SPEED = 1.0f;

  Player::Player(int playerId, int x, int y, int orientation, int level, const std::string& name,
		 const glm::vec4& pickColor) : _teamName(name)
  {
    _id = playerId;
    _pickColor = pickColor;
    _level = level;
    translate(glm::vec3(x * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2,
			y * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2, 0));
    _stateStack.push(STANDING);
    _direction = static_cast<Direction>(orientation);
    _timeUnit = 100;
    _elapsed = 0;
  }

  const glm::vec4& Player::getPickColor() const
  {
    return (_pickColor);
  }

  void		Player::initialize()
  {
    _model = AnimationPool::getInstance()->getStandingFrame();
    rotate(glm::vec3(1, 0, 0), 90);
  }

  State		Player::getState() const
  {
    return (_stateStack.top());
  }

  void		Player::turnLeft()
  {
    if (_stateStack.top() == STANDING)
      {
	switch (_direction)
	  {
	  case FRONT :
	    _direction = LEFT;
	    break;
	  case LEFT :
	    _direction = BACK;
	    break;
	  case BACK :
	    _direction = RIGHT;
	    break;
	  default :
	    _direction = FRONT;
	    break;
	  }
	rotate(glm::vec3(0, 1, 0), 90);
      }
  }

  void		Player::turnRight()
  {
    if (_stateStack.top() == STANDING)
      {
	switch (_direction)
	  {
	  case FRONT :
	    _direction = RIGHT;
	    break;
	  case RIGHT :
	    _direction = BACK;
	    break;
	  case BACK :
	    _direction = LEFT;
	    break;
	  default :
	    _direction = FRONT;
	    break;
	  }
	rotate(glm::vec3(0, -1, 0), 90);
      }
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
    switch (_stateStack.top())
      {
      case RUNNING :
    	switch (_direction)
    	  {
    	  case FRONT :
    	    translate(glm::vec3(0, -Player::SPEED, 0));
    	    break;
    	  case BACK :
    	    translate(glm::vec3(0, Player::SPEED, 0));
    	    break;
    	  case RIGHT :
    	    translate(glm::vec3(-Player::SPEED, 0, 0));
    	    break;
    	  case LEFT :
    	    translate(glm::vec3(Player::SPEED, 0, 0));
    	    break;
    	  }
	_model = AnimationPool::getInstance()->getNextRunningFrame();
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
      }
  }

  void		Player::stopRunning()
  {
    _stateStack.pop();
    _stateStack.push(STANDING);
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

  Player::~Player()
  {
  }
}
