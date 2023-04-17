GO = go
GOFLAGS = build -o test.so -buildmode=c-shared
RM = rm -f
MV = mv
DIST_DIR = /usr/lib/dlopen/
LOG_DIR = /var/log/dlopen/
TARGET_LIB = test.so
MK_DIR = mkdir -p

SRCS = main.go

.PHONY: default
default:
	${GO} ${GOFLAGS} ${SRCS}

.PHONY: install
install: ${default}
	${MK_DIR} ${LOG_DIR}
	${MK_DIR} ${DIST_DIR}
	${MV} ${TARGET_LIB} ${DIST_DIR}

.PHONY: clean
clean:
	-${RM} -- ${TARGET_LIB} test.h
	-${RM} -- ${DIST_DIR}${TARGET_LIB}
