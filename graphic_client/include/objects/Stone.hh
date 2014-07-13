//
// Stone.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:09 2014 Manu
// Last update Sun Jul 13 23:04:10 2014 Manu
//

#ifndef		__STONE_HH__
# define	__STONE_HH__

# include	<Model.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  enum		Type
    {
      LINEMATE = 0,
      DERAUMERE = 1,
      SIBUR = 2,
      MENDIANE = 3,
      PHIRAS = 4,
      THYSTAME = 5
    };

  class		Stone : public AObject
  {
  private :
    gdl::Model*	_model;
    Type	_type;
    bool	_up;
    int		_cpt;
    glm::vec2	_case;
    bool	_sens;
    int		_speed;

  public :
    virtual void	initialize();
    virtual void	update(const gdl::Clock&, gdl::Input&);
    virtual void	draw(gdl::AShader&, const gdl::Clock&);

  public :
    const Type&		getType() const;
    const glm::vec2&	getPosition() const;

  public :
    Stone(Type, const glm::vec2& caseNum = glm::vec2(0, 0));
    ~Stone();
  };
}

#endif
