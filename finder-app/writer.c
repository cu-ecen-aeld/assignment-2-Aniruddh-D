#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc);
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *file_path = argv[1];
    const char *write_str = argv[2];

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to open file: %s", file_path);
        perror("fopen");
        closelog();
        return 1;
    }

    if (fputs(write_str, fp) == EOF) {
        syslog(LOG_ERR, "Failed to write to file: %s", file_path);
        perror("fputs");
        fclose(fp);
        closelog();
        return 1;
    }

    fclose(fp);
    syslog(LOG_DEBUG, "Writing %s to %s", write_str, file_path);

    closelog();
    return 0; //completed successfully
}