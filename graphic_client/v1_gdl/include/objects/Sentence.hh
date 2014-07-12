#ifndef		__SENTENCE_HH__
# define	__SENTENCE_HH__

# include	<list>
# include	<string>
# include	"BasicShader.hh"

namespace	Zappy
{
  class		Letter;

  class		Sentence
  {
  private :
    int			_x;
    int			_y;
    std::string		_label;
    std::list<Letter*>	_letters;

  private :
    void		_createString();

  public :
    void	draw(gdl::AShader&);
    void	updateLabel(const std::string&);

  public :
    Sentence(const std::string& label, int x, int y);
    ~Sentence();
  };
}

#endif
