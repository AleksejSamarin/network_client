#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iconv.h>

int main() {
    int sock;
    struct sockaddr_in addr{};
    const int size = 1024;
    char buffer1[size], buffer2[size];

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2345);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sock = socket(AF_INET, SOCK_STREAM, NULL)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    while (true) {
        fgets(buffer1, size, stdin);
        size_t src_len = size;
        size_t dst_len = size;
        char *p_in = buffer1;
        char *p_out = buffer2;
        iconv_t conv = iconv_open("CP1251","UTF-8");
        iconv(conv, &p_in, &src_len, &p_out, &dst_len);
        iconv_close(conv);
        write(sock, buffer2, size);
        memset(buffer2, 0, size);
        read(sock, buffer2, size);
        printf("Response: %s\n", buffer2);
    }
}