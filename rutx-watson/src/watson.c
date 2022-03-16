#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <iotp_device.h>

#include "ubus_ram.h"
#include "daemon.h"
#include "cli_argp.h"


IoTPDevice *connect_watson(int argc, char *argv[], IoTPConfig *config)
{

    int rc = 0;
    int cycle = 0;

    //IoTPConfig *config = NULL;
    IoTPDevice *device = NULL;

    /* Create IoTPDevice object */
    rc = IoTPDevice_create(&device, config);
    if (rc != 0)
    {
        syslog(LOG_ERR, "Failed to configure IoTP device. rc: %d", rc);
        exit(1);
    }

    /* Invoke connection API IoTPDevice_connect() to connect to WIoTP. */
    syslog(1,"Establishing connection with IBM Watson");
    rc = IoTPDevice_connect(device);
    if (rc != 0)
    {
        syslog(LOG_ERR, "Failed to connect to Watson IoT Platform.");
        exit(1);
    }

    syslog(LOG_ALERT, "Successfully connected to watson ibm.");

    return device;
}

void send_data(IoTPDevice *device, char *data)
{
    int rc = 0;
    // Sending ram metrics
    rc = IoTPDevice_sendEvent(device, "status", data, "json", QoS0, NULL);

    if(rc!= IOTPRC_SUCCESS) {
        syslog(LOG_ERR, "Data metrics sending failed.");
    }
    else {
        syslog(LOG_ALERT, "Data succesfully sent to Watson IoT platform.");
    }
}

void disconnect_device(IoTPDevice *device, IoTPConfig *config)
{
    int rc = 0;
    /* Disconnect device */
    rc = IoTPDevice_disconnect(device);

    if (rc != IOTPRC_SUCCESS) {
        syslog(LOG_ALERT, "Failed to disconnect device from Watson IoT platform.");
        exit(1);    
    }
    else {
        syslog(LOG_ALERT, "Successfully disconnected device from Watson IoT platform");
    }

    /* Destroy client */
    IoTPDevice_destroy(device);

    /* Clear configuration */
    IoTPConfig_clear(config);

}
