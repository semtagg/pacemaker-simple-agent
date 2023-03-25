CC = gcc
CFLAGS = -Wall -Werror -fpic `pkg-config --cflags --libs glib-2.0` # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f   # rm command
MV = mv
DIST_DIR = /usr/lib/dlopen/
LOG_DIR = /var/log/dlopen/
TARGET_LIB = test.so  # target lib
MK_DIR = mkdir -p

SRCS = test.c  # source files
OBJS = $(SRCS:.c=.o)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

.PHONY: install
install: $(TARGET_LIB)
	${MK_DIR} ${LOG_DIR}
	${MK_DIR} ${DIST_DIR}
	${MV} ${TARGET_LIB} ${DIST_DIR}

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} -- ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
	-${RM} -- ${DIST_DIR}${TARGET_LIB}
