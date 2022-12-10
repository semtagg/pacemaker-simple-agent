CC = gcc
CFLAGS = -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared -Wl,-e,mmain  # linking flags
RM = rm -f   # rm command
MV = mv
MV_DIST_DIR = /usr/lib/ocf/resource.d/heartbeat/
TARGET_LIB = pool.so  # target lib

SRCS = pool.c  # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}; ${MV} ${TARGET_LIB} ${MV_DIST_DIR}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} -- ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d); \
	${RM} ${MV_DIST_DIR}${TARGET_LIB};
