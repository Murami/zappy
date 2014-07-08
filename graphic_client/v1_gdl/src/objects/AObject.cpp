//
// AObject.cpp for bomberman in /home/manu/tek2/CPP/bomberman/menu_gdl
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sat May 10 15:42:32 2014 Manu
// Last update Tue Jul  8 02:28:27 2014 Manu
//

#include	"objects/Map.hh"
#include	"objects/AObject.hh"

namespace	Zappy
{
  AObject::AObject() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
  {
  }

  const glm::vec3&	AObject::getPosition() const
  {
    return (_position);
  }

  const glm::vec3	AObject::getRealPosition() const
  {
    return (glm::vec3((int) _position.x / Map::BLOCK_SIZE,
		      (int) _position.y / Map::BLOCK_SIZE,
		      (int) _position.z / Map::BLOCK_SIZE));
  }

  const glm::vec3&	AObject::getRotation() const
  {
    return (_rotation);
  }

  const glm::vec3&	AObject::getScale() const
  {
    return (_scale);
  }

  void		AObject::setPosition(const glm::vec3& pos)
  {
    this->_position = pos;
  }

  void		AObject::translate(const glm::vec3& v)
  {
    this->_position += v;
  }

  void		AObject::rotate(const glm::vec3& axis, float angle)
  {
    this->_rotation += axis * angle;
  }

  void		AObject::scale(const glm::vec3& v)
  {
    this->_scale *= v;
  }

  void		AObject::reset()
  {
    _position = glm::vec3(0, 0, 0);
    _rotation = glm::vec3(0, 0, 0);
    _scale = glm::vec3(1, 1, 1);
  }

  glm::mat4	AObject::getTransformation()
  {
    glm::mat4	matrix(1);

    matrix = glm::translate(matrix, this->_position);
    matrix = glm::rotate(matrix, this->_rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, this->_rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, this->_rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, this->_scale);
    return (matrix);
  }

  AObject::~AObject()
  {
  }
}
