#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 2000

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char message[MAX_MESSAGE_SIZE], server_reply[MAX_MESSAGE_SIZE];
    char ip[16];
    int port;

    // Ввод IP и порта
    printf("Введите IP: ");
    fgets(ip, sizeof(ip), stdin);
    ip[strlen(ip) - 1] = '\0'; // удаление символа новой строки
    printf("Введите порт: ");
    scanf("%d", &port);
    getchar(); // очистка буфера ввода после считывания порта

    // Создание сокета
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Не удалось создать сокет");
        return 1;
    }
    printf("Сокет создан\n");

    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка подключения");
        return 1;
    }
    printf("Подключено\n");

    // Общение с сервером
    while (1) {
        printf("Введите сообщение: ");
        fgets(message, sizeof(message), stdin);

        // Отправка сообщения на сервер
        if (send(sock, message, strlen(message), 0)  < 0) {
            puts("Ошибка отправки");
            return 1;
        }

        // Получение ответа от сервера
        if (recv(sock, server_reply, sizeof(server_reply), 0) < 0) {
            puts("Ошибка приема");
            break;
        }

        puts("Ответ сервера: \n");
        puts(server_reply);
    }

    // Закрытие сокета
    close(sock);

    return 0;
}
