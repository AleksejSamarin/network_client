#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock;
    struct sockaddr_in addr{};
    const int size = 1024;
    char buffer[size];

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2345);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sock = socket(AF_INET, SOCK_STREAM, NULL)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    while (true) {
        fgets(buffer, size, stdin);
        write(sock, buffer, size);
        memset(buffer, 0, size);
        read(sock, buffer, size);
        printf("Response: %s\n", buffer);
    }
}