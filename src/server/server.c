#include <server.h>         // header
#include <client.h>         // send_message
#include <constants.h>      // BACKLOG_SIZE, bufsize

#include <sys/socket.h>     // socket
#include <netinet/in.h>     // sockaddr_in
#include <unistd.h>         // close
#include <stdlib.h>         // exit
#include <stdio.h>          // printf, perror

void tcp_init(struct tcp_socket *tcp_socket) {
    tcp_socket->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    tcp_socket->socket_addr = (struct sockaddr_in) {
        .sin_family = AF_INET,
        .sin_port = htons(PORT_NUM),      // 0x8080 reversed = 0x901f
        .sin_addr = {0}                  // any network address can be used    
    };

    ERROR(bind(tcp_socket->socket_fd, &tcp_socket->socket_addr, sizeof(tcp_socket->socket_addr)), -1, "bind");
}

void tcp_listen(struct tcp_socket *tcp_socket) {
    ERROR(listen(tcp_socket->socket_fd, BACKLOG_SIZE), -1, "listen");
}

void tcp_accept(struct tcp_socket *tcp_socket, struct tcp_client *tcp_client) {
    tcp_client->client_fd = accept(tcp_socket->socket_fd, 0, 0);
}

void tcp_destroy(struct tcp_socket *tcp_socket) {
    close(tcp_socket->socket_fd);
}