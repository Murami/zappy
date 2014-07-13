#include		<Model.hh>
#include		"objects/Egg.hh"
#include		"objects/ModelManager.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  Egg::Egg(int playerId, int id, int x, int y) : AObject()
  {
    _id = id;
    _playerId = playerId;
    _x = x;
    _y = y;
    rotate(glm::vec3(1, 0, 0), 90);
    scale(glm::vec3(0.75, 0.75, 0.75));
    translate(glm::vec3(x * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1,
			y * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1, 0));
    _print = true;
  }

  int		Egg::getY() const
  {
    return (_y);
  }

  int		Egg::getX() const
  {
    return (_x);
  }

  void		Egg::initialize()
  {
    _model = ModelManager::getInstance()->getEgg();
  }

  int		Egg::getId() const
  {
    return (_id);
  }

  int		Egg::getPlayerId() const
  {
    return (_playerId);
  }

  void		Egg::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Egg::draw(gdl::AShader& shader, const gdl::Clock&)
  {
    if (_print)
      {
	rotate(glm::vec3(0, 1, 0), 5);
	_model->draw(shader, getTransformation(), 0);
      }
  }

  void		Egg::unprint()
  {
    _print = false;
  }

  Egg::~Egg()
  {
  }
}
