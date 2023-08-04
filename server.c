#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/select.h>

#define PORT_NUMBER 12345
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3

struct client_data 
{
    int socket;
    int number;
};
int final_result = 0;
void* handle_client(void* arg)  //A void pointer is a type of pointer that can point to an object of any data type.
{
    struct client_data* data = (struct client_data*)arg;
    int socket = data->socket;
    int number = data->number;
    free(arg);

    // Send the number to the client
    if (send(socket, &number, sizeof(int), 0) < 0) 
    {
        perror("Error sending data to client");
        exit(1);
    }

    

     // Read the three numbers from the clients
  int Number_Received;
  if (recv(socket, &Number_Received, sizeof(int), 0) < 0) 
  {
    perror("Error receiving data from client 1");
    exit(1);
  }

  // Close the socket
  close(socket);

  // Add the numbers and display the result
  printf("Number Received: %d\n", Number_Received);
  
 
  
 // Add the numbers
  final_result += Number_Received;
    return NULL;
}

int main() 
{
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) 
    {
        perror("Error creating socket");
        exit(1);
    }

    // Set up the server address and port
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT_NUMBER);

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)     //is a function call in the C programming language that sets a block of memory to a specified value in this case 0
    {
        perror("Error binding socket to address and port");
        exit(1);
    }
    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) 
    {
        perror("Error listening for incoming connections");
        exit(1);
    }

    // Accept incoming connections
    int client_sockets[MAX_CLIENTS];
    pthread_t threads[MAX_CLIENTS];

    // Create a set of file descriptor sets for the select function
    fd_set read_fds, write_fds; //structure used to represent a set of file descriptors.
    int max_fd = server_socket;

    // Set up the read and write file descriptor sets
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_SET(server_socket, &read_fds);
    //A file descriptor is a small integer value that uniquely identifies an open file or socket in a Unix-like operating system

    // Wait for incoming connections
    int num_clients = 0;
    while (num_clients < MAX_CLIENTS) 
    {
        // Use select to block until there is an incoming connection
        if (select(max_fd + 1, &read_fds, &write_fds, NULL, NULL) < 0) //The select() function tests file descriptors in the range of 0 to nfds-1 that's why we put max_fd + 1
        {
            perror("Error using select");
            exit(1);
        }

        // Check if there is an incoming connection
        if (FD_ISSET(server_socket, &read_fds)) 
        {
            printf("Client %d Is Connected\n", num_clients + 1);
            socklen_t client_address_length = sizeof(struct sockaddr_in);
            client_sockets[num_clients] = accept(server_socket, (struct sockaddr*)&server_address, &client_address_length);
            if (client_sockets[num_clients] < 0) 
            {
                perror("Error accepting incoming connection");
                exit(1);
            }

            // Update the max file descriptor
            if (client_sockets[num_clients] > max_fd) 
            {
                max_fd = client_sockets[num_clients];
            }

            // Update the read file descriptor set
            FD_SET(client_sockets[num_clients], &read_fds);

            num_clients++;
        }
    }

    // Read a number from the user
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    // Create threads to handle the clients
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        struct client_data* data = (struct client_data*)malloc(sizeof(struct client_data));
        data->socket = client_sockets[i];
        data->number = num;
        if (pthread_create(&threads[i], NULL, handle_client, (void*)data) != 0) 
        {
            perror("Error creating thread");
            exit(1);
        }
    }
    // Wait for the threads to finish
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        pthread_join(threads[i], NULL); // threads[i] => The thread identifier of the thread to be waited for
    }

    // Close the sockets
    close(server_socket);
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        close(client_sockets[i]);
    }
    
    //Display the result
    printf("Summ Of All Numbers: %d\n", final_result);

    return 0;
}
    

