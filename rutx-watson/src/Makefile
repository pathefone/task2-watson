BIN:=rutx-watson
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
LDFLAGS:=-liotp-as-device -lpaho-mqtt3as -lblobmsg_json -lubox -lubus -largp

.PHONY: all clean

all: $(BIN)

$(BIN):	$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(BIN)

