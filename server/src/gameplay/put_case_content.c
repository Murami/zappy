/*
** put_case_content.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:09:27 2014 otoshigami
** Last update Sun Jul 13 21:47:01 2014 Desabre Quentin
*/

#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			put_case_content_x(char* buffer_msg, int val, char* str)
{
  while (val > 0)
    {
      strncat(buffer_msg, " ", 4095);
      strncat(buffer_msg, str, 4095);
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
