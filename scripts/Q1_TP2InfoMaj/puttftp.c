#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define INPUT_SIZE 50


void dispInfos(char host[], char file[]){
    char dispHost[strlen(host)+7];
    char dispFile[strlen(file)+7];
    sprintf(dispHost, "Host: %s\n", host);
    sprintf(dispFile, "File: %s\n", file);
    write(STDOUT_FILENO, dispHost, strlen(dispHost));
    write(STDOUT_FILENO, dispFile, strlen(dispFile));
}

int main(int argc, char *argv[]) {

    char host[INPUT_SIZE];
    char file[INPUT_SIZE];
    
    
    /*
    if (argc == 1) { // If no arguments were given, assume that host=srvtpinfo1.ensea.fr and file=bidule
        sprintf(host, "srvtpinfo1.ensea.fr");
        sprintf(file, "file");
    }
    
    else {
    */


    // Check if there is the correct number of arguments
    if (argc != 3) {
        char argError[50];
        sprintf(argError, "Error: the program %s needs two arguments <server> <file>\n", argv[0]);
        write(STDERR_FILENO, argError, strlen(argError));
        exit(EXIT_FAILURE); // If there is not, exit program
        // Find the server and file
    }
    sprintf(host, "%s", argv[1]);
    sprintf(file, "%s", argv[2]);
    
    /*
    }
    */

    dispInfos(host, file);
    
    return 0;
}