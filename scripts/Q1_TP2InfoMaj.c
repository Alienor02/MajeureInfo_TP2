#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char* server;
    char* file;
    
    // If no arguments were given, assume server=truc and file=bidule
    if (argc == 1) {
        server = "truc";
        file = "bidule";
    }
    else {
        // Check if there is the correct number of arguments
        if (argc != 3) {
            printf("Error: the program %s can only read <server> <file>\n", argv[0]);
            exit(EXIT_FAILURE); // If there is not, exit program
            // Find the server and file
        }
        server = argv[1];
        file = argv[2];
    }

    printf("Server: %s\n", server);
    printf("File: %s\n", file);

    return 0;
}