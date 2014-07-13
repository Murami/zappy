/*
** gameplay_gauche.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:35:19 2014 otoshigami
** Last update Sun Jul 13 17:37:03 2014 otoshigami
*/

#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			gameplay_command_gauche(t_gameplay* this,
						t_player_command* command)
{
  command->player->direction -= 1;
  if (command->player->direction <= 0)
    command->player->direction = 4;
  client_send_msg(command->player->client, "ok");
  gameplay_send_pos(this, command->player);
}
