typedef struct  {
	long long TOTAL_MEMORY, FREE_MEMORY, SHARED_MEMORY, BUFFERED_MEMORY;
} ram_memory;

static void board_cb(struct ubus_request *req, int type, struct blob_attr *msg);
void save_ram_usage(char *data);
int get_ram_usage(char *data);
void format_json(ram_memory *ram_mem,char *data);
