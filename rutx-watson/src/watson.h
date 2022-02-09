void usage(void);
void getopts(int argc, char **argv);
void deviceCommandCallback(char *type, char *id, char *commandName, char *format, void *payload, size_t payloadSize);
void logCallback(int level, char *message);
void MQTTTraceCallback(int level, char *message);
IoTPDevice *connect_watson(int argc, char *argv[], IoTPConfig *config);
int disconnect_device(IoTPDevice *device, IoTPConfig *config);
void send_data(IoTPDevice *device, char *data);