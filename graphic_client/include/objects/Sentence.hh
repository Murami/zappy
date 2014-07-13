//
// Sentence.hh for zappy in /home/manu/rendu/PSU_2013_zappy/graphic_client/include/objects
//
// Made by Manu
// Login   <manu@epitech.net>
//
// Started on  Sun Jul 13 23:04:12 2014 Manu
// Last update Sun Jul 13 23:04:12 2014 Manu
//

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
