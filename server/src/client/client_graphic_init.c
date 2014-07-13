/*
** client_graphic_init.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:03:17 2014 otoshigami
** Last update Sun Jul 13 17:03:18 2014 otoshigami
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "client_graphic.h"
#include "socketstream.h"
#include "server.h"
#include "monitor_command.h"

void			client_graphic_initialize(t_client_graphic* this,
						  t_socketstream* sockstream)
{
  client_initialize(&this->parent_client, sockstream);
  this->parent_client.vtable = &client_graphic_vtable;
}

void			client_graphic_release(t_client_graphic* this)
{
  client_release(&this->parent_client);
}

t_client_graphic*	client_graphic_new(t_socketstream* sockstream)
{
  t_client_graphic*	client_graphic;

  client_graphic = malloc(sizeof(t_client_graphic));
  if (client_graphic == NULL)
    return (NULL);
  client_graphic_initialize(client_graphic, sockstream);
  return (client_graphic);
}

void			client_graphic_delete(t_client_graphic* client_graphic)
{
  client_graphic_release(client_graphic);
  free(client_graphic);
}
