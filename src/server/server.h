#ifndef SOCKET_H
#define SOCKET_H

#include <client.h>

#include <sys/socket.h>
#include <netinet/in.h>


struct tcp_socket {
    int socket_fd;
    struct sockaddr_in socket_addr;   
};

void tcp_init    (struct tcp_socket *);
void tcp_listen  (struct tcp_socket *);
void tcp_accept  (struct tcp_socket *, struct tcp_client *);
void tcp_destroy (struct tcp_socket *);

#endif