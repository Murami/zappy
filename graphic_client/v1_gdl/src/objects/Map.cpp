#include		"graphic/ShaderManager.hpp"
#include		"objects/Map.hh"

namespace	Zappy
{
  const int	Map::BLOCK_SIZE = 9;

  Map::Map(int width, int height) : AObject()
  {
    _width = width;
    _height = height;
  }

  int		Map::getWidth() const
  {
    return (_width);
  }

  int		Map::getHeight() const
  {
    return (_height);
  }

  void		Map::setSize(int w, int h)
  {
    _width = w;
    _height = h;
  }

  void		Map::initialize()
  {
    if (!_texture.load("./assets/pave2.tga"))
      throw (std::runtime_error("Unable to load floor.tga"));
    _geom.setColor(glm::vec4(1, 1, 1, 1));
    _geom.pushVertex(glm::vec3(0, 0, 0));
    _geom.pushVertex(glm::vec3(_width * BLOCK_SIZE, 0, 0));
    _geom.pushVertex(glm::vec3(_width * BLOCK_SIZE,
			       _height * BLOCK_SIZE,
			       0));
    _geom.pushVertex(glm::vec3(0, _height * BLOCK_SIZE,
			       0));
    _geom.pushUv(glm::vec2(0, 0));
    _geom.pushUv(glm::vec2(_width, 0));
    _geom.pushUv(glm::vec2(_width, _height));
    _geom.pushUv(glm::vec2(0, _height));
    for (int x = 0;
	 x < static_cast<float>(_width * BLOCK_SIZE); x += BLOCK_SIZE)
      {
	_lines.pushVertex(glm::vec3(x, 0, 0.1));
	_lines.pushVertex(glm::vec3(x, _height * BLOCK_SIZE,
				    0.1));
      }
    for (int y = 0;
	 y < static_cast<float>(_height * BLOCK_SIZE); y += BLOCK_SIZE)
      {
	_lines.pushVertex(glm::vec3(0, y, 0.1));
	_lines.pushVertex(glm::vec3(_width * BLOCK_SIZE,
				    y, 0.1));
      }
    _lines.build();
    _geom.build();
  }

  void		Map::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Map::draw(gdl::AShader& shader, const gdl::Clock&)
  {
    glEnable(GL_TEXTURE_2D);
    shader.bind();
    shader.setUniform("color", glm::vec4(1, 1, 1, 1));
    _texture.bind();
    // static gdl::BasicShader bs = *ShaderManager::getInstance()->getMapShader();
    _geom.draw(shader,
	       getTransformation(), GL_QUADS);
    glDisable(GL_TEXTURE_2D);
    // _lines.draw(*bs, getTransformation(), GL_LINES);
  }

  Map::~Map()
  {
  }
}
