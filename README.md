# Minitalk

Minitalk is a 42 project that implements a simple client-server communication system using UNIX signals. The client sends a string to the server, which then prints it character by character using signal-based transmission.

## Features
- Sends messages from a client to a server using **SIGUSR1** and **SIGUSR2** signals.
- Handles signal reception properly to reconstruct and display messages.
- Ensures reliable message transmission without data loss.

## Requirements
- The project must use **only UNIX signals** (no sockets or pipes).
- Implement proper **signal handling** to process messages efficiently.
- The server must display received messages correctly.

## Compilation
Compile the project using:
```sh
make all
```
This will generate the `server` and `client` executables.

## Usage
### Start the server
Run the server and note the displayed **PID**:
```sh
./server
```

### Send a message
Use the client to send a message to the server using its PID:
```sh
./client <server_pid> "Your message here"
```
Example:
```sh
./client 12345 "Hello, world!"
```

## Signal Handling
- **SIGUSR1** and **SIGUSR2** are used to send bits of each character.
- The server reconstructs characters and prints them in order.
- The client ensures each bit is received before sending the next.

## Error Handling
- The client checks for valid arguments (PID and message).
- The server ensures correct signal handling to avoid crashes.
- Proper error messages are displayed for incorrect usage.

## Cleanup
To remove compiled files:
```sh
make fclean
```
