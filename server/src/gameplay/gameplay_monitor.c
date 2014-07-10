#include <stdlib.h>
#include "gameplay.h"
#include "client.h"
#include "client_graphic.h"
#include "monitors.h"
#include "monitor_command.h"

void			gameplay_command_msz(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_size(this, &command->client->parent_client);
}

void			gameplay_command_bct(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_case(this,
		    &command->client->parent_client,
		    &this->map.map[atoi(command->data[0])
				   + atoi(command->data[1]) * this->map.width]);
}

void			gameplay_command_mct(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_map(this, &command->client->parent_client);
}

void			gameplay_command_tna(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_teams(this, &command->client->parent_client);
}

void			gameplay_command_ppo(t_gameplay* this, t_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_plv(t_gameplay* this, t_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_pin(t_gameplay* this, t_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_sgt(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_delay(this, &command->client->parent_client);
}

void			gameplay_command_sst(t_gameplay* this, t_monitor_command* command)
{
  this->delay = atoi(command->data[0]);
  monitor_send_delay(this, &command->client->parent_client);
}
