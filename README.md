# Multi-Operation-Server-Client in C

This C program is a simple multi-threaded server that listens for incoming connections on a specified port and sends a number to each client that connects to it.

## How it works

1. The server creates a socket using the `socket()` function with the address family set to AF_INET and the type of socket set to SOCK_STREAM, which specifies a stream socket that uses TCP for reliable, stream-oriented communication.

2. The server sets up a server address and port using the `sockaddr_in` structure and the `memset()` function. The server address is associated with INADDR_ANY, allowing it to listen for connections on all available network interfaces.

3. The server binds the socket to the server address and port using the `bind()` function.

4. The server listens for incoming connections using the `listen()` function, allowing it to queue up to 5 incoming connections that have not yet been accepted.

5. The server enters a loop where it accepts incoming connections from clients using the `accept()` function. Each client connection is stored in an array, and a new thread is created to handle each client using the `pthread_create()` function.

6. The server reads a number from the user using the `scanf()` function, which will be sent to each client by the threads that handle them.

7. Each thread's handler function, `handle_client()`, is responsible for sending the number to the client using the `send()` function to send data over the socket. The client performs a specific operation on the received number based on its role:

  - `client1`: Calculates the square of the number. <br>
  - `client2`: Calculates the factorial of the number. <br>
  - `client3`: Calculates the exponential of the number using the mathematical constant e (2.71828). <br>
    The clients then send the results of their operations back to the server using the `send()` function.

8. The server receives the results from each client using the `recv()` function. It then adds all the results together to calculate the final sum of the three numbers. 

9. After all of the threads have been created, the program waits for them to finish using the `pthread_join()` function, which blocks the program until the specified thread finishes execution.

10. Finally, the server closes the server socket and all of the client sockets using the `close()` function and exits.

The server program uses the `select()` function to block and wait for incoming connections from clients. It then creates a separate thread to handle each client, sends the number entered by the user to each client, receives all the results of the operations handled by these clients, adds them all together, and displays them on the screen. Once all of the threads have finished, the sockets are closed.

## Difference Between a Process and a Thread

In computer science, a process is an instance of a program that is being executed by a computer. A process has its own memory space, resources, and execution context, and it can run concurrently with other processes.

A thread, on the other hand, is a unit of execution within a process. A process can contain multiple threads, and these threads can run concurrently within the process, sharing the process's resources and memory space.

One key difference between processes and threads is the level of isolation between them. Processes are isolated from each other and have their own memory space, so if one process crashes or is terminated, it does not affect the other processes running on the system. Threads, on the other hand, share the memory space of the process in which they are running, so if one thread crashes or is terminated, it can potentially affect the other threads in the process.

Another difference is the level of overhead involved in creating and managing processes and threads. Creating a new process typically involves more overhead than creating a new thread, as it involves setting up a new memory space and execution context for the process. However, threads are generally lighter-weight and easier to create and manage than processes.

## File Descriptor

A file descriptor is a small integer value that uniquely identifies an open file or socket in a Unix-like operating system. File descriptors are used to reference files and sockets in various system calls and functions that perform input and output operations.

## `memset()`

`memset(&server_address, 0, sizeof(server_address))` is a function call in the C programming language that sets a block of memory to a specified value. It takes three arguments:

1. A pointer to the block of memory to be set, which is `&server_address` in this case. `server_address` is a variable of some type (the type is not specified in the given code).

2. The value to be set, which is 0 in this case.

3. The number of bytes to be set, which is `sizeof(server_address)` in this case. `sizeof(server_address)` is a compile-time operator that returns the size of the `server_address` variable in bytes.

The `memset()` function sets each byte in the specified block of memory to the specified value. In this case, it sets each byte of the `server_address` variable to 0. This has the effect of clearing the memory occupied by the `server_address` variable and setting all of its bytes to zero.

## `FD_ISSET()`

The `FD_ISSET()` macro is used to test whether a particular file descriptor is a member of an `fd_set` variable. It takes two arguments: the file descriptor to be tested and a pointer to the `fd_set` variable.

In the given code, `FD_ISSET(server_socket, &read_fds)` tests whether the file descriptor stored in the `server_socket` variable is a member of the `read_fds` `fd_set` variable. If the file descriptor is a member of the set, the macro returns a non-zero value; otherwise, it returns 0.

## Execution
![Example Execution](https://github.com/BouchanaHicham/multi-operation-client-server/blob/main/Execution_Commands.png)


## License

This project is licensed under the MIT License. You can find the full text of the license in the [LICENSE](LICENSE) file.

## Contributions

Contributions to this project are more than welcome. If you have any suggestions, bug fixes, or new features to add, please feel free to fork the repository and submit a pull request. We value your feedback and contributions!

## Author

**Bouchana Hicham**

