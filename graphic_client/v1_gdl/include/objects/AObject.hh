//
// AObject.hh for bomberman in /home/manu/tek2/CPP/bomberman/menu_gdl
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sat May 10 15:42:28 2014 Manu
// Last update Tue Jul  8 02:26:19 2014 Manu
//

#ifndef		__AOBJECT_HH__
# define	__AOBJECT_HH__

# include	<AShader.hh>
# include	<SdlContext.hh>
# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>
# include	<iostream>

namespace	Zappy
{
  class		AObject
  {
  protected :
    glm::vec3	_position;
    glm::vec3	_rotation;
    glm::vec3	_scale;

  public :
    virtual void	initialize() = 0;
    virtual void	update(const gdl::Clock&, gdl::Input&) = 0;
    virtual void	draw(gdl::AShader&, const gdl::Clock&) = 0;

  public :
    AObject();
    virtual ~AObject();

  public :
    const glm::vec3&	getPosition() const;
    const glm::vec3	getRealPosition() const;
    const glm::vec3&	getRotation() const;
    const glm::vec3&	getScale() const;

  public :
    void		reset();
    void		translate(const glm::vec3&);
    void		rotate(const glm::vec3&, float);
    void		scale(const glm::vec3&);
    glm::mat4		getTransformation();

  public :
    void		setPosition(const glm::vec3&);
  };
}

#endif
