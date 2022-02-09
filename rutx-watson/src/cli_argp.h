#ifndef CLI_ARGP_H
#define CLI_ARGP_H

#include <argp.h>


struct Config_file
{
	char *orgId, *typeId, *deviceId, *token;

};
typedef struct Config_file config_file;

static struct argp_option options[];
static error_t parse_opt (int key, char *arg, struct argp_state *state);
static struct argp argp;
void get_args(int argc, char *argv[], config_file *conf_file);

#endif
