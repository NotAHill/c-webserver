#include <client.h>

#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/socket.h>

void client_init(struct tcp_client *tcp_client) {
    //tcp_client->message_buf = {0};
    memset(tcp_client->message_buf, 0, sizeof(tcp_client->message_buf));
    tcp_client->message_type = UNINITIALISED;
}

char *get_file_name(struct tcp_client *tcp_client, char *buf, int nbytes) {
    assert(tcp_client->message_type == GET);

    strncpy(buf, tcp_client->message_buf + 5, nbytes);

    char *c;
    if ((c = strchr(buf, ' ')) == NULL) {
        return NULL;
    }

    *c = 0;
    return buf;
}

void download_file(struct tcp_client *tcp_client, char *filename) {
    int open_fd;
    ERROR(open_fd = open(filename, O_RDONLY), -1, "open");
    sendfile(tcp_client->client_fd, open_fd, 0, 256);
    close(open_fd);
}

void set_message_type(struct tcp_client *tcp_client) {
    char *buf = tcp_client->message_buf;

    printf("%s\n", buf);

    if (strncmp(buf, "GET", 3) == 0) {
        tcp_client->message_type = GET;
    } else if (strncmp(buf, "POST", 4) == 0) {
        tcp_client->message_type = POST;
    } else if (strncmp(buf, "DELETE", 6) == 0) {
        tcp_client->message_type = DELETE;
    } else if (strncmp(buf, "PUT", 3) == 0) {
        tcp_client->message_type = PUT;
    } else {
        tcp_client->message_type = ERROR;
    }
}

void client_destroy(struct tcp_client *tcp_client) {
    tcp_client->message_type = UNINITIALISED;
    //tcp_client->message_buf = {0};
    close(tcp_client->client_fd);
}

void client_receive(struct tcp_client *tcp_client) {
    recv(tcp_client->client_fd, tcp_client->message_buf, BUFSIZE, 0);
    printf("%s\n", tcp_client->message_buf);
    set_message_type(tcp_client);
    printf("%d\n", tcp_client->message_type);
}