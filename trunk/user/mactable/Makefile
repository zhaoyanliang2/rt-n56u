PROGS	= mactable
OBJS	= main.o

all: $(PROGS)

$(PROGS): $(OBJS)
	$(CC) -o $(PROGS) $(OBJS) $(CFLAGS) $(LDFLAGS)

romfs:
	$(ROMFSINST) /usr/sbin/$(PROGS)

clean:
	rm -f $(PROGS) *.o *~
