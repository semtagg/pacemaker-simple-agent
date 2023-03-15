#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>

#define OCF_SUCCESS             0
#define OCF_ERR_GENERIC         1
#define OCF_ERR_ARGS            2
#define OCF_ERR_UNIMPLEMENTED   3
#define OCF_ERR_PERM            4
#define OCF_ERR_INSTALLED       5
#define OCF_ERR_CONFIGURED      6
#define OCF_NOT_RUNNING         7

static const char     LOG_SUFFIX[]         = ".log";
static const char     PATH_PREFIX[]        = "/var/log/test/";

void
create_path(char path[], const char *prefix, char *instance) {
    path[0] = '\0';
    strcat(path, prefix);
    strcat(path, instance);
    strcat(path, LOG_SUFFIX);
    return;
}

void
create_message(char mes[], const char *action, char *instance) {
    mes[0] = '\0';
    strcat(mes, "Action: ");
    strcat(mes, action);
    strcat(mes, ", instance: ");
    strcat(mes, instance);
    strcat(mes, "\n");
    return;
}

void
create_error(char** error, char* mes) {
    char *buf = (char *)malloc(sizeof(char) * (sizeof(mes) + 1));
    strcpy(buf, mes);
    *error = buf;
    return;
}

int
start(GHashTable *params, char **error) {
    char mes[100];
    char path_log[100];
    char *instance = g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE");

    create_message(mes, "Start", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    return OCF_SUCCESS;
}

int
stop(GHashTable *params, char **error) {
    char mes[100];
    char path_log[100];
    char *instance = g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE");

    create_message(mes, "Stop", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    return OCF_SUCCESS;
}

int
status(GHashTable *params, char **error) {
    char mes[100];
    char path_log[100];
    char *instance = g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE");

    create_message(mes, "Status", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    return OCF_SUCCESS;
}

int
monitor(GHashTable *params, char **error) {
    char mes[100];
    char path_log[100];
    char *instance = g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE");
    create_message(mes, "Monitor", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);

    return OCF_SUCCESS;
}

int
metadata(GHashTable *params, char **stdout_data, char **error) {
    static const char meta_data[] = 
    "<?xml version=\"1.0\"?>\n"
    "<!DOCTYPE resource-agent SYSTEM \"ra-api-1.dtd\">\n"
    "<resource-agent name=\"libtest.so\" version=\"1.0\">\n"
    "  <version>1.0</version>\n"
    "  <longdesc lang=\"en\">\n"
    "   This script is used to write data to a file.\n"
    "  </longdesc>\n"
    "  <shortdesc lang=\"en\">Test agent</shortdesc>\n"
    "  <actions>\n"
    "    <action name=\"start\"   timeout=\"15s\" />\n"
    "    <action name=\"stop\"    timeout=\"15s\" />\n"
    "    <action name=\"status\"  timeout=\"15s\" interval=\"15s\" />\n"
    "    <action name=\"monitor\" timeout=\"15s\" interval=\"15s\" />\n"
    "    <action name=\"meta-data\"  timeout=\"5s\" />\n"
    "  </actions>\n"
    "</resource-agent>\n";

    char *buf = (char *)malloc(sizeof(char) * (sizeof(meta_data) + 1));
    char mes[100];
    char path_log[100];
    char *instance = g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE");
    create_message(mes, "Metadata", instance);
    create_path(path_log, PATH_PREFIX, instance);
    int fd_log = open(path_log, O_WRONLY | O_APPEND | O_CREAT, 0666);

    write(fd_log, mes, strlen(mes));
    close(fd_log);
    strcpy(buf, meta_data);
    *stdout_data = buf;

    create_error(error, "All right!");

    return OCF_SUCCESS;
}
