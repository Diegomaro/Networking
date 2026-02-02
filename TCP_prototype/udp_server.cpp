#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

int main(){
    char buffer[1024];
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    struct sockaddr_in host;
    socklen_t host_len = sizeof(host);
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(60000);
    struct sockaddr *server_std = (struct sockaddr *)&server;
    struct sockaddr *sender_std = (struct sockaddr *)&host;
    bind(udp_sock, server_std, sizeof(server));
    std::cout << "Listening on UDP port 60000..." << std::endl;
    ssize_t msg_length = recvfrom(udp_sock, buffer, sizeof(buffer) - 1, 0, sender_std, &host_len);
    buffer[msg_length] = '\0';
    std::cout << "Message received:" << buffer << std::endl;
    close(udp_sock);
    return 0;
}
