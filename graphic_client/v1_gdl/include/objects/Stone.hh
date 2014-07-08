#ifndef		__STONE_HH__
# define	__STONE_HH__

# include	<Model.hh>
# include	"objects/AObject.hh"

namespace	Zappy
{
  enum		Type
    {
      LINEMATE,
      DERAUMERE,
      SIBUR,
      MENDIANE,
      PHIRAS,
      THYSTAME
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

  public :
    Stone(Type, const glm::vec2& caseNum = glm::vec2(0, 0));
    ~Stone();
  };
}

#endif
