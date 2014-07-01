#include		"AStone.hh"

namespace		graphic
{
  AStone::AStone()
  {
  }

  void			AStone::draw()
  {
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_TEXTURE_2D);
  }

  void			AStone::setCaseX(int caseX)
  {
    _caseX = caseX;
  }

  void			AStone::setCaseY(int caseY)
  {
    _caseY = caseY;
  }

  void			AStone::setX(int x)
  {
    _x = x;
  }

  void			AStone::setY(int y)
  {
    _y = y;
  }

  int			AStone::getCaseX() const
  {
    return (_caseX);
  }

  int			AStone::getCaseY() const
  {
    return (_caseY);
  }

  int			AStone::getX() const
  {
    return (_x);
  }

  int			AStone::getY() const
  {
    return (_y);
  }

  AStone::~AStone()
  {
  }
}
