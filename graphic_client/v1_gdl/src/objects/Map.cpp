#include		"objects/Map.hh"

namespace	Zappy
{
  const int	Map::BLOCK_SIZE = 9;

  Map::Map(int width, int height) : AObject()
  {
    _width = width;
    _height = height;
  }

  void		Map::initialize()
  {
    if (!_texture.load("./assets/floor.tga"))
      throw (std::runtime_error("Unable to load floor.tga"));
    _geom.setColor(glm::vec4(1, 1, 1, 1));
    _geom.pushVertex(glm::vec3(0, 0, 0));
    _geom.pushUv(glm::vec2(0, 0));
    _geom.pushVertex(glm::vec3(_width * BLOCK_SIZE, 0, 0));
    _geom.pushUv(glm::vec2(1, 0));
    _geom.pushVertex(glm::vec3(_width * BLOCK_SIZE,
			       _height * BLOCK_SIZE,
			       0));
    _geom.pushUv(glm::vec2(1, 1));
    _geom.pushVertex(glm::vec3(0, _height * BLOCK_SIZE,
			       0));
    _geom.pushUv(glm::vec2(0, 1));
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

    _x.setColor(glm::vec4(1, 0, 0, 1));
    _x.pushVertex(glm::vec3(0, 0, 0));
    _x.pushVertex(glm::vec3(100, 0, 0));
    _x.pushUv(glm::vec2(0, 0));
    _x.pushUv(glm::vec2(1, 1));

    _y.setColor(glm::vec4(0, 1, 0, 1));
    _y.pushVertex(glm::vec3(0, 0, 0));
    _y.pushVertex(glm::vec3(0, 100, 0));
    _y.pushUv(glm::vec2(0, 0));
    _y.pushUv(glm::vec2(1, 1));

    _z.setColor(glm::vec4(0, 0, 1, 1));
    _z.pushVertex(glm::vec3(0, 0, 0));
    _z.pushVertex(glm::vec3(0, 0, 100));
    _z.pushUv(glm::vec2(0, 0));
    _z.pushUv(glm::vec2(1, 1));

    _x.build();
    _y.build();
    _z.build();

  }

  void		Map::update(const gdl::Clock&, gdl::Input&)
  {
  }

  void		Map::draw(gdl::AShader& shader, const gdl::Clock&)
  {
    glEnable(GL_TEXTURE_2D);
    shader.setUniform("color", glm::vec4(1, 1, 1, 1));
    _texture.bind();
    _geom.draw(shader, getTransformation(), GL_QUADS);
    // _x.draw(shader, getTransformation(), GL_LINES);
    // _y.draw(shader, getTransformation(), GL_LINES);
    // _z.draw(shader, getTransformation(), GL_LINES);
    glDisable(GL_TEXTURE_2D);
    _lines.draw(shader, getTransformation(), GL_LINES);

  }

  Map::~Map()
  {
  }
}