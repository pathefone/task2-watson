#include <iotp_device.h>
#include <syslog.h>
#include <argp.h>

#include "daemon.h"
#include "cli_argp.h"
#include "file_lock.h"


int main(int argc, char *argv[])
{
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    openlog("rutx-watson", LOG_PID, LOG_USER);
    int rc = 0;

    rc = only_one_instance();

    config_file conf_file;

	get_args(argc, argv, &conf_file);

    config_file *ptr = &conf_file;

    syslog(LOG_ALERT, "Starting rutx-watson program...");
    rc = start_daemon(argc, argv, ptr);
    syslog(LOG_ALERT, "Exiting rutx-watson program...");
    closelog();

    return rc; 
}