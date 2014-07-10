#include		"objects/Food.hh"
#include		"objects/ModelManager.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  Food::Food(int x, int y) : AObject()
  {
    _x = x;
    _y = y;
    scale(glm::vec3(0.25, 0.25, 0.25));
    rotate(glm::vec3(1, 0, 0), 90);
    translate(glm::vec3(x * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1,
			y * Map::BLOCK_SIZE + random() %
			(Map::BLOCK_SIZE - 1) + 1, 0));
  }

  int		Food::getX() const
  {
    return (_x);
  }

  int		Food::getY() const
  {
    return (_y);
  }

  void		Food::initialize()
  {
    _model = ModelManager::getInstance()->getFood();
  }

  void		Food::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Food::draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    rotate(glm::vec3(0, 1, 0), 2);
    _model->draw(shader, getTransformation(), clock.getElapsed());
  }

  Food::~Food()
  {
  }
}
