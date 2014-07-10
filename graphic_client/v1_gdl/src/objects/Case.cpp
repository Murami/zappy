#include		"objects/Case.hh"

namespace	Zappy
{
  Case::Case(int x, int y)
  {
    _x = x;
    _y = y;
  }

  void		Case::addFood()
  {
    Food* food = new Food(_x, _y);
    food->initialize();
    _foodList.push_back(food);
  }

  void		Case::removeFood()
  {
    if (_foodList.size())
      _foodList.pop_back();
  }

  void		Case::draw(gdl::AShader& shader, const gdl::Clock& clock)
  {
    if (_foodList.size())
      {
	std::list<Food*>::iterator it = _foodList.begin();
	(*it)->draw(shader, clock);
      }
  }

  Case::~Case()
  {
  }
}
