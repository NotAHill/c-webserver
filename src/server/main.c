#include <server.h>
#include <client.h>

#include <stddef.h>

int main(void) {
    struct tcp_socket tcp_socket;
    tcp_init(&tcp_socket);
    tcp_listen(&tcp_socket);

    char filename[256];
    struct tcp_client tcp_client;
    client_init(&tcp_client);
    for (int i = 0; i < 3; i++) {
        tcp_accept(&tcp_socket, &tcp_client);
        client_receive(&tcp_client);

        if (get_file_name(&tcp_client, filename, 256) == NULL) {
            client_destroy(&tcp_client);
        }

        download_file(&tcp_client, filename);

        client_destroy(&tcp_client);
    }
    
    tcp_destroy(&tcp_socket);

    return 0;
}