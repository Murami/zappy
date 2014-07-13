#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "client.h"
#include "team.h"

void			gameplay_send_seg(t_gameplay* this)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  sprintf(buffer, "seg %s\n", this->winner->name);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}
