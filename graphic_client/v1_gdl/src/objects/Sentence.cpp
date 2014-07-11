#include		<Clock.hh>
#include		"objects/Sentence.hh"
#include		"objects/Letter.hh"

namespace	Zappy
{
  Sentence::Sentence(const std::string& label, int x, int y)
  {
    _label = label;
    _x = x;
    _y = y;
    _createString();
  }

  void		Sentence::_createString()
  {
    _letters.clear();
    std::size_t nb = 0;
    for (std::string::iterator it = _label.begin(); it != _label.end(); it++)
      {
	Letter* letter = new Letter(*it);
	letter->translate(glm::vec3(_x + nb * 20, _y, 0));
	_letters.push_back(letter);
	nb++;
      }
  }

  void		Sentence::updateLabel(const std::string& newLabel)
  {
    _label = newLabel;
    _createString();
  }

  void		Sentence::draw(gdl::AShader& shader)
  {
    for (std::list<Letter*>::iterator it = _letters.begin();
	 it != _letters.end(); it++)
      (*it)->draw(shader, gdl::Clock());
  }

  Sentence::~Sentence()
  {
  }
}
