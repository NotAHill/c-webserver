#ifndef CLIENT_H
#define CLIENT_H

#include <constants.h>

enum message_type {
    UNINITIALISED,
    GET,
    POST,
    PUT,
    DELETE,
    ERROR
};

struct tcp_client {
    int client_fd;
    char message_buf[BUFSIZE];
    enum message_type message_type;
};


void client_init        (struct tcp_client *);
void client_destroy     (struct tcp_client *);

void set_message_type   (struct tcp_client *);
void download_file      (struct tcp_client *, char *);
char *get_file_name(struct tcp_client *, char *, int);
void client_receive     (struct tcp_client *);

#endif
