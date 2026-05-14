#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from SOC Analyst Client";
    char buffer[1024] = {0};

    // 1. Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 2. Преобразование IP-адреса (localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // 3. Установка соединения с сервером
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // 4. Отправка тестового сообщения
    send(sock, hello, strlen(hello), 0);
    printf("Message sent to server\n");

    // 5. Чтение ответа (Echo)
    int valread = read(sock, buffer, 1024);
    printf("Server replied: %s\n", buffer);

    // Закрытие соединения
    close(sock);
    return 0;
}
