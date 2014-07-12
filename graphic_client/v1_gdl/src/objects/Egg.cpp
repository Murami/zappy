#include		<Model.hh>
#include		"objects/Egg.hh"
#include		"objects/ModelManager.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  Egg::Egg(int id, int x, int y) : AObject()
  {
    _id = id;
    rotate(glm::vec3(1, 0, 0), 90);
    scale(glm::vec3(0.75, 0.75, 0.75));
    translate(glm::vec3(x * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1,
			y * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1, 0));
  }

  void		Egg::initialize()
  {
    _model = ModelManager::getInstance()->getEgg();
  }

  int		Egg::getId() const
  {
    return (_id);
  }

  void		Egg::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Egg::draw(gdl::AShader& shader, const gdl::Clock&)
  {
    rotate(glm::vec3(0, 1, 0), 5);
    _model->draw(shader, getTransformation(), 0);
  }

  Egg::~Egg()
  {
  }
}
