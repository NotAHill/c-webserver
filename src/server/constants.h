#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ERROR(result, error_val, msg) \
    if ((result) == (error_val)) { \
        perror("Error on " msg); \
        exit(1); \
    } else { \
        printf(msg " worked successfully\n"); \
    }

#define PORT_NUM 0x8080
#define BACKLOG_SIZE 10
#define BUFSIZE 256

#endif