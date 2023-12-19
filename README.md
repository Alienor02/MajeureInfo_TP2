# Lab Report for TPSP2: TFTP Client in C

This collaborative project was developed by Aliénor D'IRUMBERRY DE SALABERRY and Aurélien POINSEL.

## Overview
This project focuses on the implementation of a TFTP (Trivial File Transfer Protocol) client in C. This TFTP client comprises two main components: `gettftp` for downloading files from the server and `puttftp` for uploading files to the server. The project adheres to the TFTP protocol specifications and progressively implements features according to the lab requirements.

## Project Structure
The project is organized into two primary C files:

- **`gettftp.c`:** Implements the `gettftp` functionality, allowing the client to download files from the TFTP server.
- **`puttftp.c`:** Implements the `puttftp` functionality, enabling the client to upload files to the TFTP server.

Both files use a set of utility functions (not shown) to handle common tasks such as retrieving server information, creating sockets, and managing TFTP packet construction.

## Features
The TFTP client includes the following features, developed up to question 4.c):

1. **Command-Line Interface:** Accepts command-line arguments for specifying the TFTP server, file, and operation (`gettftp` or `puttftp`).

2. **Server Information Retrieval:** Uses `getaddrinfo` to obtain server information, including IP address and port.

3. **Socket Creation:** Reserves a UDP socket for communication with the TFTP server.

4. **Displaying Server Information:** Outputs relevant information about the server, file, IP address, and port.

5. **RRQ Construction and Transmission (`gettftp`):** Constructs a Read Request (RRQ) packet and sends it to the server for file retrieval.

6. **Data Reception (`gettftp`):** Receives data packets from the server, handles acknowledgment (ACK) packets, and reconstructs the file.

Note : features 5 and 6 have not been proven to work properly yet

## Potential Enhancements
While the project is functional up to question 4.b), there are several potential enhancements to consider:

1. **Complete `puttftp` Implementation:** Develop the functionality for uploading files to the TFTP server.

2. **Option Blocksize Implementation:** Implement the option blocksize, as specified in RFC2348, to optimize file transfer performance.

3. **Error Handling Improvements:** Enhance error handling for various scenarios, including packet loss, packet errors, and other exceptional conditions.

4. **Code Comments and Documentation:** Add comments for complex sections, algorithms, and functions. Provide comprehensive documentation to explain the purpose and usage of important functions.

## Conclusion
The TFTP client project has provided valuable insights into network programming and practical experience with socket communication and protocol implementation. While the client is able to download files (`gettftp`), there are opportunities for further development and refinement, especially regarding uploading files (`puttftp`). The project has deepened our understanding of network protocols and honed our C programming skills. Future enhancements can build upon the existing foundation to create a more robust and elaborated TFTP client.
