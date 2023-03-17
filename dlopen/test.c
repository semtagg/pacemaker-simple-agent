#include <stdio.h>
#include <fcntl.h>
#include <glib.h>

#define DLOPEN_SUCCESS             0

void test_write_message(const char* instance, const char* message) {
    FILE* fptr;
    char path[100];
    sprintf(path, "/var/log/test/%s.log", instance);

    fptr = fopen(path, "a");
    fprintf(fptr, message, instance);
    fclose(fptr);
}

int start(GHashTable* params, char** error) {
    test_write_message((char *)g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE"),
                       "Action: start, instance: %s.\n");
    return DLOPEN_SUCCESS;
}

int stop(GHashTable* params, char** error) {
    test_write_message((char *)g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE"),
                       "Action: stop, instance: %s.\n");
    return DLOPEN_SUCCESS;
}

int status(GHashTable* params, char** error) {
    test_write_message((char *)g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE"),
                       "Action: status, instance: %s.\n");
    return DLOPEN_SUCCESS;
}

int monitor(GHashTable* params, char** error) {
    test_write_message((char *)g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE"),
                       "Action: monitor, instance: %s.\n");
    return DLOPEN_SUCCESS;
}

int metadata(GHashTable* params, char** stdout_data, char** error) {
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
    test_write_message((char *)g_hash_table_lookup(params, "OCF_RESOURCE_INSTANCE"),
                       "Action: meta-data, instance: %s.\n");
    *stdout_data = strdup(meta_data);
    return DLOPEN_SUCCESS;
}
