#ifndef		__LETTERMANAGER_HPP__
# define	__LETTERMANAGER_HPP__

# include	<map>
# include	<iostream>
# include	<stdexcept>
# include	<Geometry.hh>
# include	<Texture.hh>

namespace	Zappy
{
  class		Letter;

  class		LetterManager
  {
  private :
    static LetterManager*		_instance;

  private :
    gdl::Geometry*			_geometry;
    std::map<char, gdl::Texture*>	_textureLetters;

  public :
    static LetterManager*	getInstance()
    {
      if (_instance == NULL)
	_instance = new LetterManager();
      return (_instance);
    }

  public :
    gdl::Geometry*	getGeometry()
    {
      return (_geometry);
    }

    gdl::Texture*	getTexture(char c)
    {
      if (c >= 65 && c <= 90)
	c += 32;
      return (_textureLetters[c]);
    }

  private :
    void		_createGeomAndLoadTexture(char begin, char end)
    {
      for (char c = begin; c <= end; c++)
	{
	  gdl::Texture* texture = new gdl::Texture();
	  std::string texPath("./assets/fonts/letter");
	  texPath += c;
	  texPath += std::string(".tga");
	  if (!texture->load(texPath))
	    throw (std::runtime_error(std::string("Error while loading ") + texPath));
	  _textureLetters[c] = texture;
	}
    }

  private :
    LetterManager()
    {
      _createGeomAndLoadTexture('0', '9');
      _createGeomAndLoadTexture('a', 'z');
      gdl::Texture* texture = new gdl::Texture();
      std::string texPath("./assets/fonts/letterspace.tga");
      if (!texture->load(texPath))
	throw (std::runtime_error(std::string("Error while loading ") + texPath));
      _textureLetters[' '] = texture;
      _geometry = new gdl::Geometry();
      _geometry->setColor(glm::vec4(1, 1, 1, 1));
      _geometry->pushVertex(glm::vec3(0, 0, 0));
      _geometry->pushVertex(glm::vec3(1, 0, 0));
      _geometry->pushVertex(glm::vec3(1, 1, 0));
      _geometry->pushVertex(glm::vec3(0, 1, 0));

      // changer cet ordre les lettres sont a l'envers
      // et checker les translates
      _geometry->pushUv(glm::vec2(-1, 1));
      _geometry->pushUv(glm::vec2(0, 1));
      _geometry->pushUv(glm::vec2(0, 0));
      _geometry->pushUv(glm::vec2(-1, 0));
      _geometry->build();
    }

    ~LetterManager()
    {
    }
  };
}

#endif
