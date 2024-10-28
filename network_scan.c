#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 80           // The port to check (HTTP)
#define TIMEOUT 1         // Timeout in seconds

// Check if a specific IP address has an open port
int is_host_live(const char *ip) {
    struct sockaddr_in addr;
    int sock;
    struct timeval timeout;
    fd_set fdset;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 0;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Set timeout for the socket
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    FD_ZERO(&fdset);
    FD_SET(sock, &fdset);

    fcntl(sock, F_SETFL, O_NONBLOCK);  // Set to non-blocking mode

    // Try to connect
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    if (select(sock + 1, NULL, &fdset, NULL, &timeout) == 1) {
        int so_error;
        socklen_t len = sizeof so_error;
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
        if (so_error == 0) {
            close(sock);
            return 1;  // Host is live on this port
        }
    }

    close(sock);
    return 0;
}

int main() {
    char ip[16];
    printf("Starting scan on local network...\n");

    for (int i = 1; i < 255; i++) {
        snprintf(ip, sizeof(ip), "192.168.1.%d", i);  // Adjust to your subnet
        if (is_host_live(ip)) {
            printf("Host %s is live on port %d\n", ip, PORT);
        }
    }

    printf("Scan completed.\n");
    return 0;
}
