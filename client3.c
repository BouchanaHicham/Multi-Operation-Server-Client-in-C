	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

int main(int argc, char** argv) 
{
  // Check for the correct number of command-line arguments
  if (argc != 3) 
  {
    printf("Usage: %s <server IP address> <port number>\n", argv[0]);
    exit(1);
  }

  // Parse the server IP address and port number from the command-line arguments
  char* server_ip_address = argv[1];
  int port_number = atoi(argv[2]);

  // Create a socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) 
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address and port
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(server_ip_address);
  server_address.sin_port = htons(port_number);

  // Connect to the server
  if (connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) 
  {
    perror("Error connecting to server");
    exit(1);
  }

  // Receive the number from the server
  int num;
  if (recv(client_socket, &num, sizeof(int), 0) < 0) 
  {
    perror("Error receiving data from server");
    exit(1);
  }

  // Double the number
  float result = pow(2.71828, num);
        printf("Exponential: %f\n", result);
  
  int Sent_Result = result;
   // Send the result back to the server
    if (send(client_socket, &Sent_Result, sizeof(int), 0) < 0) 
    {
        perror("Error sending data to server");
        exit(1);
    }

  // Display the result
  printf("The double of %d is %f\n", num, result);

  // Close the socket
  close(client_socket);
  
 

  return 0;
}

