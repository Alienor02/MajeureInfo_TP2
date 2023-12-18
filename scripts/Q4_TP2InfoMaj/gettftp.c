#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


#define INPUT_SIZE 100
#define ERR_OUTPUT_SIZE 100
#define MAX_BUFFER_SIZE 512


void dispInfos(char host[], char file[], struct sockaddr_in *server_addr){
    char dispHost[strlen(host)+7];
    char dispFile[strlen(file)+7];
    char ip_buffer[INET_ADDRSTRLEN];
    char dispAddr[INET_ADDRSTRLEN+12];
    char dispPort[INET_ADDRSTRLEN+14];

    sprintf(dispHost, "Host: %s\n", host);
    sprintf(dispFile, "File: %s\n\n", file);
    if (inet_ntop(AF_INET, &(server_addr->sin_addr), ip_buffer, sizeof(ip_buffer)) == 0) {
        perror("inet_ntop");
        exit(EXIT_FAILURE);
    }

    sprintf(dispAddr, "Server IP: %s\n", ip_buffer);
    sprintf(dispPort, "Server Port: %d\n", ntohs(server_addr->sin_port));

    write(STDOUT_FILENO, dispHost, strlen(dispHost));
    write(STDOUT_FILENO, dispFile, strlen(dispFile));
    write(STDOUT_FILENO, dispAddr, strlen(dispAddr));
    write(STDOUT_FILENO, dispPort, strlen(dispPort));
}


int main(int argc, char *argv[]) {

    char host[INPUT_SIZE];
    char file[INPUT_SIZE];
    
    
    /*
    if (argc == 1) { // If no arguments were given, assume that host="srvtpinfo1.ensea.fr" and file="file"
        sprintf(host, "srvtpinfo1.ensea.fr");
        sprintf(file, "file");
    }
    
    else {
    */


    // Check if there is the correct number of arguments
    if (argc != 3) {
        char argError[ERR_OUTPUT_SIZE];
        sprintf(argError, "Error: the program %s needs two arguments <server> <file>\n", argv[0]);
        write(STDERR_FILENO, argError, strlen(argError));
        exit(EXIT_FAILURE); // If there is not 3 arguments, exit program
        // Find the server and file
    }
    sprintf(host, "%s", argv[1]);
    sprintf(file, "%s", argv[2]);
    
    /*
    }
    */


    // Call getaddrinfo to get the server's address
    struct addrinfo hints, *server_info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;    // IPv4
    hints.ai_socktype = SOCK_DGRAM; // Datagram socket for UDP

    char tftPort[10];
    if (!strcmp(host, "127.0.0.1")){ // The port is "1069" for the server available on moodle
        sprintf(tftPort, "1069");
    }
    else{
        sprintf(tftPort, "69");
    }
    int status = getaddrinfo(host, tftPort, &hints, &server_info);

    if (status != 0) {
        char addrError[ERR_OUTPUT_SIZE];
        sprintf(addrError, "getaddrinfo error: %s\n", gai_strerror(status));
        write(STDERR_FILENO, addrError, strlen(addrError));
        exit(EXIT_FAILURE);
    }


    // Access server_info to get server address
    struct sockaddr_in *server_addr = (struct sockaddr_in *)server_info->ai_addr;

    // Display every information in the console
    dispInfos(host, file, server_addr);

    // Création d'une socket
    int sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Making a RRQ request
    char rrqPacket[MAX_BUFFER_SIZE];
    int packetSize = snprintf(rrqPacket, sizeof(rrqPacket), "RRQ%s%c%s%c%s%c%s%c",
                              file, 0, "octet", 0, "blksize", 0, "512", 0);

    // Sending the RRQ request to the server
    if (sendto(sockfd, rrqPacket, packetSize, 0, (struct sockaddr *)server_info->ai_addr, server_info->ai_addrlen) == -1) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Reception of one or several package DAT and its ACK signal
    int blockNumber = 1;
    while (1) {
        char dataPacket[MAX_BUFFER_SIZE];
        ssize_t bytesRead = recvfrom(sockfd, dataPacket, sizeof(dataPacket), 0, NULL, NULL);
        if (bytesRead == -1) {
            perror("recvfrom");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // Possible use of the (DAT) information

        // Sending the ACK signal
        char ackPacket[4] = {0, 4, blockNumber >> 8, blockNumber & 0xFF};  // Opcode ACK: 04
        if (sendto(sockfd, ackPacket, sizeof(ackPacket), 0, (struct sockaddr *)server_info->ai_addr, server_info->ai_addrlen) == -1) {
            perror("sendto");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // Increment the block number for the next ACK
        blockNumber++;

        // Si le paquet est moins de MAX_BUFFER_SIZE, c'est le dernier paquet
        if (bytesRead < MAX_BUFFER_SIZE) {
            break;
        }
    }

    // Closing the socket
    close(sockfd);


    // Free the list created by getaddrinfo
    freeaddrinfo(server_info);
    
    return 0;
}


