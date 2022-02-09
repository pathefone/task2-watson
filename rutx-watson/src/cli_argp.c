#include <stdio.h>
#include <stdlib.h>       
#include <string.h>       
#include <argp.h>
#include "cli_argp.h"         


static struct argp_option options[] = {
  {"orgId", 'o', "orgId", 0, "An orgId", 0 },
  {"typeId", 't', "typeId", 0, "A typeId", 0 },
  {"deviceId", 'd', "deviceId", 0, "An ID for device", 0 },
  {"token", 'n', "token", 0, "A token", 0 },
  { 0 } 
};

static struct argp argp = { options, parse_opt };


static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  config_file *config_file = state->input;

  switch (key)
    {
    case 'o':
      config_file->orgId = arg;
      break;
    case 't':
      config_file->typeId = arg;
      break;
    case 'd':
      config_file->deviceId = arg;
      break;
    case 'n':
      config_file->token = arg;
      
      
    }
  return 0;
}

void get_args(int argc, char *argv[], config_file *conf_file)
{
  argp_parse (&argp, argc, argv, 0, 0, conf_file);

}
