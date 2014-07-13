//
// Letter.cpp for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/src/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:02:00 2014 Manu
// Last update Sun Jul 13 23:02:00 2014 Manu
//

#include		"interface/Window.hh"
#include		"objects/Letter.hh"
#include		"graphic/ShaderManager.hpp"

namespace	Zappy
{
  LetterManager* LetterManager::_instance = NULL;

  Letter::Letter(char character) : AObject()
  {
    _character = character;
    _shader = *ShaderManager::getInstance()->getHUDShader();
    _geometry = LetterManager::getInstance()->getGeometry();
    _texture = LetterManager::getInstance()->getTexture(_character);
    scale(glm::vec3(20, 20, 1));
  }

  void		Letter::initialize()
  {
  }

  void		Letter::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Letter::draw(gdl::AShader& shader, const gdl::Clock&)
  {
    _texture->bind();
    _geometry->draw(shader, getReverseTransformation(), GL_QUADS);
  }

  Letter::~Letter()
  {
  }
}
