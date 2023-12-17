#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // Создание Сокета
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    // Адрес сервера
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &(server_addr.sin_addr)) <= 0) {
        perror("Failed to set up server address");
        return 1;
    }

    // Сообщения
    if (sendto(sockfd, "GET", strlen("GET"), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to send request to the server");
        return 1;
    }

    // Буфер
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server_response_addr;
    socklen_t server_response_addr_len = sizeof(server_response_addr);
    ssize_t bytes_received = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_response_addr, &server_response_addr_len);
    if (bytes_received < 0) {
        perror("Failed to receive response from the server");
        return 1;
    }
    buffer[bytes_received] = '\0';

    
    printf("Response from the server: %s\n", buffer);

    // Закрытие сокета
    close(sockfd);

    return 0;
}
