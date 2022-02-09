#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include <syslog.h>
#include <stddef.h>

int rc = 0;

enum {
	TOTAL_MEMORY,
	FREE_MEMORY,
	SHARED_MEMORY,
	BUFFERED_MEMORY,
	__MEMORY_MAX,
};

enum {
	MEMORY_DATA,
	__INFO_MAX,
};

typedef struct  {
	long long TOTAL_MEMORY, FREE_MEMORY, SHARED_MEMORY, BUFFERED_MEMORY;
} ram_memory; 

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
	[TOTAL_MEMORY] = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
	[FREE_MEMORY] = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
	[SHARED_MEMORY] = { .name = "shared", .type = BLOBMSG_TYPE_INT64 },
	[BUFFERED_MEMORY] = { .name = "buffered", .type = BLOBMSG_TYPE_INT64 },
};

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
	[MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};

static void board_cb(struct ubus_request *req, int type, struct blob_attr *msg) {
	
	struct blob_attr *tb[__INFO_MAX];
	struct blob_attr *memory[__MEMORY_MAX];

	blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));

	if (!tb[MEMORY_DATA]) {
		syslog(LOG_ERR, "No memory data received.");
		rc=-1;
		return;
	}

	blobmsg_parse(memory_policy, __MEMORY_MAX, memory,
			blobmsg_data(tb[MEMORY_DATA]), blobmsg_data_len(tb[MEMORY_DATA]));

    ram_memory *ram_mem = (ram_memory *)req->priv;
	size_t BUFF_LENGTH = sizeof(long long);

	ram_mem->TOTAL_MEMORY = blobmsg_get_u64(memory[TOTAL_MEMORY]);
	ram_mem->FREE_MEMORY = blobmsg_get_u64(memory[FREE_MEMORY]);
	ram_mem->SHARED_MEMORY = blobmsg_get_u64(memory[SHARED_MEMORY]);
	ram_mem->BUFFERED_MEMORY = blobmsg_get_u64(memory[BUFFERED_MEMORY]);
	
}

void format_json(ram_memory *ram_mem,char *data) {

	   	snprintf(data,sizeof (char)*300,"{\"d\" : {\"Total memory\": \"%lld\",\"Free memory\": \"%lld\",\"Shared memory\": \"%lld\",\"Buffered memory\": \"%lld\"}}",ram_mem->TOTAL_MEMORY,
   	   		ram_mem->FREE_MEMORY,
   	   		ram_mem->SHARED_MEMORY,
   	   		ram_mem->BUFFERED_MEMORY);
}

int get_ram_usage(char *data) {

	struct ubus_context *ctx;
	uint32_t id;
	ram_memory ram_mem;

	ctx = ubus_connect(NULL);
	if (!ctx) {
		syslog(LOG_ERR, "Failed to connect to ubus\n");
		return -1;
	}

	if (ubus_lookup_id(ctx, "system", &id) ||
	    ubus_invoke(ctx, id, "info", NULL, board_cb, &ram_mem, 3000)) {
		syslog(LOG_ERR, "cannot request memory info from procd\n");
		rc=-1;
	}

	format_json(&ram_mem, data);
	ubus_free(ctx);

	return rc;

}






