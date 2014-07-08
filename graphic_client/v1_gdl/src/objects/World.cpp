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
    scale(glm::vec3(20, 20, 20));
    translate(glm::vec3(0, 0, -100));
    rotate(glm::vec3(1, 0, 0), 90);
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
