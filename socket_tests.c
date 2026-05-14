#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

void check_option(int fd, int level, int optname, const char* name) {
    int optval;
    socklen_t optlen = sizeof(optval);
    if (getsockopt(fd, level, optname, &optval, &optlen) == 0) {
        printf("Option %s: Value = %d (Success)\n", name, optval);
    } else {
        perror("getsockopt");
    }
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    printf("--- Socket Options Testing ---\n");

    // Проверка различных опций
    check_option(sockfd, SOL_SOCKET, SO_REUSEADDR, "SO_REUSEADDR");
    check_option(sockfd, IPPROTO_TCP, TCP_NODELAY, "TCP_NODELAY (Nagle Algorithm)");
    check_option(sockfd, SOL_SOCKET, SO_KEEPALIVE, "SO_KEEPALIVE");
    check_option(sockfd, SOL_SOCKET, SO_SNDBUF, "SO_SNDBUF (Send Buffer)");
    check_option(sockfd, SOL_SOCKET, SO_RCVBUF, "SO_RCVBUF (Receive Buffer)");

    close(sockfd);
    return 0;
}
