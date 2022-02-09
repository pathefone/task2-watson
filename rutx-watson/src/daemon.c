#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <iotp_device.h>

#include "watson.h"
#include "ubus_ram.h"
#include "cli_argp.h"
#include "file_lock.h"

volatile sig_atomic_t sigint_received = 0;

/* Signal handler */
void sigHandler(int signo)
{
    sigint_received = 1;
}

int start_daemon(int argc, char *argv[], config_file *conf_file)
{

    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    int rc = 0;

    //creating IoTPConfig file for connection to watson ibm
    IoTPConfig *config = NULL;
    IoTPConfig_create(&config, NULL);
    IoTPConfig_setProperty(config, "identity.orgId", conf_file->orgId);
    IoTPConfig_setProperty(config, "identity.typeId", conf_file->typeId);
    IoTPConfig_setProperty(config, "identity.deviceId", conf_file->deviceId);
    IoTPConfig_setProperty(config, "auth.token", conf_file->token);
    
    syslog(LOG_ALERT, "orgId: %s", conf_file->orgId);
    syslog(LOG_ALERT, "typeId: %s", conf_file->typeId);
    syslog(LOG_ALERT, "deviceId: %s", conf_file->deviceId);
    syslog(LOG_ALERT, "token: %s", conf_file->token);

    
    IoTPDevice *device = NULL;

    device = connect_watson(argc, argv, config);
    sleep(5); //sleep after establishing connection

    char data[300]; 
    int result = 0;
    int fail_counter = 0;

    /* Daemon Loop */
    while (!sigint_received)
    {
        result = get_ram_usage(data);
        if(result!= IOTPRC_SUCCESS) { 
            fail_counter++;
            syslog(LOG_ERR, "Getting ram usage failed (%d).", fail_counter);
            if(fail_counter >= 5) {sigint_received = 1; rc = -1;}
        }
        else {
            send_data(device, data);
        }
        sleep(10);
    }
    
    disconnect_device(device, config);
    syslog(LOG_INFO, "Terminating program.");
    
    exit(EXIT_SUCCESS);

    return rc;
}