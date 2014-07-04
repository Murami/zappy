#include		"objects/ModelManager.hh"
#include		"objects/Stone.hh"
#include		"objects/Map.hh"

namespace	Zappy
{
  Stone::Stone(Type type, const glm::vec2& caseNum) : AObject()
  {
    _type = type;
    _model = ModelManager::getInstance()->getModel(type);
    _up = true;
    _cpt = 0;
    _case = caseNum;
    translate(glm::vec3(caseNum.x * Map::BLOCK_SIZE + random() % (Map::BLOCK_SIZE - 1) + 1,
			caseNum.y * Map::BLOCK_SIZE + random() % (Map::BLOCK_SIZE - 1) + 1, 0));
  }

  void		Stone::initialize()
  {
    translate(glm::vec3(0, 0, 0.5));
    scale(glm::vec3(0.1, 0.1, 0.1));
  }

  void		Stone::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Stone::draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    if (_up)
      {
	_cpt++;
	translate(glm::vec3(0, 0, 0.01));
      }
    else
      {
	_cpt--;
	translate(glm::vec3(0, 0, -0.01));
      }
    if (_cpt == 50)
      _up = false;
    else if (_cpt == 0)
      _up = true;
    rotate(glm::vec3(0, 0, 1), 1);
    _model->draw(shader, getTransformation(), clock.getElapsed());
  }

  const Type&	Stone::getType() const
  {
    return (_type);
  }

  Stone::~Stone()
  {
  }
}
