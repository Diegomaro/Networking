#include <string.h>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    // each character is 1 byte(ASCII), so this represents 512 bytes of data
    char msg[512]; 
    std::cout << "Message to be sent:";
    std::cin.getline(msg, 512);
    // Returns the file locator, id of where it is running
    // Sequential numbering, each new process gets next number
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0); 
    struct sockaddr_in target;
    // clean memory where target is stored, for undefined parameters of struct
    memset(&target, 0, sizeof(target)); 
    target.sin_family = AF_INET;
    //htons for double bytes, write to memory in big endian
    target.sin_port = htons(60000); 
    // convert "x.x.x.x to byte address in IPv4 or IPv6"
    inet_pton(AF_INET, "127.0.0.1", &target.sin_addr);
    // converting target to a regular sockaddr
    struct sockaddr *target_std = (struct sockaddr *)&target;
    sendto(udp_sock, msg, strlen(msg), 0, target_std, sizeof(target));
    close(udp_sock);
    return 0;
}