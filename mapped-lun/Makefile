CC = gcc
CFLAGS = -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared -Wl,-e,mmain  # linking flags
RM = rm -f   # rm command
TARGET_LIB = mapped-lun.so  # target lib

SRCS = mapped-lun.c  # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} -- ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
