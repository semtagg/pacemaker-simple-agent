CC = gcc
CFLAGS = -Wall -Werror -fpic `pkg-config --cflags --libs glib-2.0` # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f   # rm command
MV = mv
MV_DIST_DIR = /usr/lib/dlopen/
TARGET_LIB = test.so  # target lib

SRCS = test.c  # source files
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
