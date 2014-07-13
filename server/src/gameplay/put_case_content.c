/*
** put_case_content.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:09:27 2014 otoshigami
** Last update Sun Jul 13 23:21:29 2014 Desabre Quentin
*/

#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

char			*my_strcat(char *str, char *str2)
{
  int			len;
  char			*buff;
  int			i;

  i = 0;
  len = strlen(str) + strlen(str2) + 4;
  buff = malloc(len);
  memset(buff, 0, len);
  while (str[i])
    {
      buff[i] = str[i];
      i++;
    }
  len = 0;
  while (str2[len])
    {
      buff[i++] = str2[len];
      len++;
    }
  return (buff);
}

void			put_case_content_x(char* buffer_msg, int val, char* str)
{
  while (val > 0)
    {
      my_strcat(buffer_msg, " ");
      my_strcat(buffer_msg, str);
      val--;
    }
}

void			put_case_content(t_gameplay* this,
					 char* buffer_msg, int x, int y)
{
  t_case*		contents;
  t_player*		player;
  t_list_iterator	it;

  contents = &this->map.map[x + y * this->map.width];
  put_case_content_x(buffer_msg, contents->linemate, "linemate");
  put_case_content_x(buffer_msg, contents->deraumere, "deraumere");
  put_case_content_x(buffer_msg, contents->sibur, "sibur");
  put_case_content_x(buffer_msg, contents->phiras, "phiras");
  put_case_content_x(buffer_msg, contents->thystame, "thystame");
  put_case_content_x(buffer_msg, contents->mendiane, "mendiane");
  put_case_content_x(buffer_msg, contents->food, "nourriture");
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == x && player->y == y)
	strncat(buffer_msg, " joueur", 4095);
      it = list_iterator_next(it);
    }
  strncat(buffer_msg, ",", 4095);
}
