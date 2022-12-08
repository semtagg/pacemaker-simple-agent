#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define	OCF_SUCCESS		0
#define	OCF_ERR_GENERIC		1
#define	OCF_ERR_ARGS		2
#define	OCF_ERR_UNIMPLEMENTED	3
#define	OCF_ERR_PERM		4
#define	OCF_ERR_INSTALLED	5
#define	OCF_ERR_CONFIGURED	6
#define	OCF_NOT_RUNNING		7

static const char     START_CMD[]       = "start";
static const char     STOP_CMD[]        = "stop";
static const char     STATUS_CMD[]      = "status";
static const char     MONITOR_CMD[]     = "monitor";
static const char     META_DATA_CMD[]   = "meta-data";

static const char     DISABLE[]            = "one";
static const char     ENABLE[]             = "two";
static const char     LOG_SUFFIX[]         = ".log";
static const char     PATH_PREFIX[]        = "/var/log/test/";
static const char     STATE_PATH_PREFIX[]  = "/var/log/test/state_";

const char my_interp[] __attribute__((section(".interp"))) = "/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2";

void
create_path(char path[], char *prefix, char *instance) {
    path[0] = '\0';
    strcat(path, prefix);
    strcat(path, instance);
    strcat(path, LOG_SUFFIX);
    return path;
}

void
create_message(char mes[], char *action, char *instance) {
    mes[0] = '\0';
    strcat(mes, "Action: ");
    strcat(mes, action);
    strcat(mes, ", instance: ");
    strcat(mes, instance);
    strcat(mes, "\n");
    return;
}

int
start(void) {
    char mes[100];
    char path_log[100];
    char path_state[100];
    char *instance = getenv("OCF_RESOURCE_INSTANCE");
    int n;
    create_message(mes, "Start", instance);
    create_path(path_log, PATH_PREFIX, instance);
    create_path(path_state, STATE_PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);
    int fd_state = open(path_state, O_WRONLY | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    lseek(fd_state, 0, SEEK_SET);
    write(fd_state, ENABLE, sizeof(ENABLE));

    close(fd_log);
    close(fd_state);
    return OCF_SUCCESS;
}

int
stop(void) {
    char mes[100];
    char path_log[100];
    char path_state[100];
    char *instance = getenv("OCF_RESOURCE_INSTANCE");
    int n;
    create_message(mes, "Stop", instance);
    create_path(path_log, PATH_PREFIX, instance);
    create_path(path_state, STATE_PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);
    int fd_state = open(path_state, O_WRONLY | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    lseek(fd_state, 0, SEEK_SET);
    write(fd_state, DISABLE, sizeof(DISABLE));

    close(fd_log);
    close(fd_state);
    return OCF_SUCCESS;
}

int
status(void) {
    char mes[100];
    char path_log[100];
    char *instance = getenv("OCF_RESOURCE_INSTANCE");
    int n;
    create_message(mes, "Status", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    return OCF_SUCCESS;
}

int
monitor(void) {
    char mes[100];
    char path_log[100];
    char path_state[100];
    char *instance = getenv("OCF_RESOURCE_INSTANCE");
    create_message(mes, "Monitor", instance);
    create_path(path_log, PATH_PREFIX, instance);
    create_path(path_state, STATE_PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);
    int fd_state = open(path_state, O_RDONLY | O_CREAT, 0666);
    char state[4];

    write(fd_log, mes, strlen(mes));
    if (read(fd_state, state, 3) >= 0) {
        state[3] = '\0';
    }

    close(fd_log);
    close(fd_state);

    if (strcmp(state, ENABLE) == 0) {
        return OCF_SUCCESS;
    } else /*if (strcmp(buf_check, DISABLE) == 0)*/ {
        return OCF_NOT_RUNNING;
    }

    return -1;
}

int
metadata(int stdout, int stderr) {
    char mes[100];
    char path_log[100];
    char *instance = getenv("OCF_RESOURCE_INSTANCE");
    int n;
    create_message(mes, "Metadata", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    static const char meta_data[]=
    "<?xml version=\"1.0\"?>\n"
    "<!DOCTYPE resource-agent SYSTEM \"ra-api-1.dtd\">\n"
    "<resource-agent name=\"pool.so\" version=\"0.0.0\">\n"
    "  <version>0.0.0</version>\n"
    "  <longdesc lang=\"en\">\n"
    "   demo-resource\n"
    "  </longdesc>\n"
    "  <shortdesc lang=\"en\">demo-resource</shortdesc>\n"
    "  <parameters>\n"
	"    <parameter name=\"demo_parameter_1\" unique=\"0\" required=\"0\">\n"
	"      <longdesc lang=\"en\">\n"
	"	demo_parameter_1\n"
	"      </longdesc>\n"
	"      <shortdesc lang=\"en\">demo_parameter_1</shortdesc>\n"
	"      <content type=\"integer\" default=\"10\" />\n"
	"    </parameter>\n"
	"    <parameter name=\"demo_parameter_2\" unique=\"0\" required=\"0\">\n"
	"      <longdesc lang=\"en\">\n"
	"	demo_parameter_2\n"
	"      </longdesc>\n"
	"      <shortdesc lang=\"en\">demo_parameter_2</shortdesc>\n"
	"      <content type=\"boolean\" default=\"false\" />\n"
	"    </parameter>\n"
	"  </parameters>\n"
    "  <actions>\n"
    "    <action name=\"start\"   timeout=\"20s\" />\n"
    "    <action name=\"stop\"    timeout=\"20s\" />\n"
    "    <action name=\"monitor\" timeout=\"20s\" interval=\"20s\" />\n"
    "    <action name=\"meta-data\"  timeout=\"5s\" />\n"
    "  </actions>\n"
    "</resource-agent>\n";

    write(stdout, meta_data, sizeof(meta_data));
    return OCF_SUCCESS;
}

int
handler(int out_fd, int err_fd, char *action) {
    int ret = 0;
    if (strcmp(action, START_CMD) == 0){
        ret = start();
    } else if (strcmp(action, STOP_CMD) == 0) {
        ret = stop();
    } else if (strcmp(action, STATUS_CMD) == 0) {
        ret = status();
    } else if (strcmp(action, MONITOR_CMD) == 0) {
        ret = monitor();
    } else if (strcmp(action, META_DATA_CMD) == 0) {
        ret = metadata(out_fd, err_fd);
    }

    return ret;
}

int
mmain() {
    // return code
    int ret = 0;
    // is used to get parameters
    char *stack_address = __builtin_frame_address(0);
    // skip 24 bytes: ret address, argc, exec name
    char **argv = stack_address + 0x18;
    // parse action
    if (strcmp(*argv, START_CMD) == 0){
        ret = start();
    } else if (strcmp(*argv, STOP_CMD) == 0) {
        ret = stop();
    } else if (strcmp(*argv, STATUS_CMD) == 0) {
        ret = status();
    } else if (strcmp(*argv, MONITOR_CMD) == 0) {
        ret = monitor();
    } else if (strcmp(*argv, META_DATA_CMD) == 0) {
        ret = metadata(1, 2);
    }

    _exit(ret);
}
