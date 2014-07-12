#include		"objects/Map.hh"
#include		"objects/ModelManager.hh"
#include		"objects/World.hh"

namespace	Zappy
{
  World::World() : AObject()
  {
  }

  void		World::initialize()
  {
    _model = ModelManager::getInstance()->getWorld();
    rotate(glm::vec3(1, 0, 0), 90);
  }

  void		World::setMapSize(int width, int height)
  {
    scale(glm::vec3(3 * width, 3 * height, 3 * (width + height) / 2));
    rotate(glm::vec3(0, 1, 0), 14);
    translate(glm::vec3(0, 0, -5.5 * (width + height) / 2));
    translate(glm::vec3(((width + height) / 4) * Map::BLOCK_SIZE + Map::BLOCK_SIZE / 2, ((width + height) / 4) * Map::BLOCK_SIZE - Map::BLOCK_SIZE / 2, 0));
  }

  void		World::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		World::draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    _model->draw(shader, getTransformation(), clock.getElapsed());
  }

  World::~World()
  {
  }
}
