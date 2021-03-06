# systems-level-programming

Systems Level Programming w/ JonAlf Dyrland-Weaver at Stuyvesant 2019-2020

This repository contains notes, assignments, and projects from the course.

## Wednesday, 8 January, 2020

[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)

IP Addresses in CS Dojo - 149.89.150.(100 - 134, 33, 34)

```c
// forking_server.c
#include "networking.h"

void process (char * s);
void subserver(int from_client);

int main() {
  int listen_socket;
  int f;
  listen_socket = server_setup(); // probably don't touch this
  // creates a socket on a well defined port 9001
  // puts it in the listening state
  // server_setup is not a blocking function

  while (1) {
    int client_socket = server_connect(listen_socket); // probably don't touch this
    // this is triggered by client trying to enter the listening socket
    // a new socket is created and the port number is unknown

    f = fork();
    if (f == 0 )
      subserver(client_socket);

      // subserver and main server talk to socket

    else

      // parent closes connection to client
      // listening socket does not get closed
      close(client_socket);
  }
}

void subserver(int client_socket) {

}
```

```c
//client.c
int main(int argc, char ** argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];

  if(argc == 2)
    server_socket = client_setup(argv[1]); // provide the IP address you are connecting to
  // client creates a socket and send data to it at 9001
  // subserver says hi
  // socket at client end changes to go to the socket at the subserver

  else
    server_socket = client_setup(TEST_IP);

  while (1) {
    // read from standard in
    // write to socket
    // read from socket
  }
}
```

```c
//networking.h
#define BUFFER_SIZE 256
#define PORT "9001" // pick a different port! (expect this to be a string because there is a potential problem of Endian-ness between OSes)
#define TEST_IP "127.0.0.1" // the computer's local IP address (expect this to be a string)
```

```c
//networking.c

// DO NOT CHANGE THIS FILE

// accept function is the server side of the three way handshake (blocking function)
// connect function is the client side of the three way handshake
```

In a peer to peer connection, one computer waits for a connection, and another computer will connect.

The listening computer will act as the "server" in listening state
The other computer will act as the "client" in conncting state

## Tuesday, 7 January, 2020

Sockets act like a pipe

- Send buffered data between two processes
- Section of memory which deals with network transfers
- Socket needs to be a unique connection between two computers
- IP (Internet Protocol) Address
  - IP Addresses are externally provided by internet service providers
- Port
  - Every computer has 65,536 available ports which allows for multiple sockets for a single IP address.
  - Web servers that use HTTP use port 80 (for web traffic)
  - Ports are assigned internally
- Incoming/ Outgoing Addresses
  - Two sockets with same IP Addresses and ports with different protocols interact differently

Transmission Control Protocol (Stream)

- End result to a TCP socket is either:
  - Data will be sent in entirety and the order is correct
  - Error
  - Files are not send in entirety; they are sent in packets
    - Two packets from same data may be sent in different ways
    - Later packet may come before a previous one
    - In TCP, packets are ordered and correct for different packet ordering.
    - TCP also requests for missing packets
  - Three way handshake
    - Client to server (client does not know if server receives message)
    - Server knows it can receive data
    - Server responds
    - Client knows that it can receive data, and send data
    - Server does not know that it can send data until client sends back to server again

Universal Datagram Protocol (UDP)

- There is no three way handshake
  - Unaware if anyone is listening
- Does not handle packet ordering or missing packets
- Much faster protocol and transmission than TCP
- Used for streaming media

## Monday, 6 January, 2020

Network code should run on different computers but you have to have cross OS communication. It is unclear as to the internal machine language across different OSes. There needs to be consistent language. Something like integer representations could be different (endian-ness).

There are standards and protocols in place like internet protocol (IP). Other protocols also exist such as ethernet to connect locally. Ethernet is the overwhelming standard but there was a token standard protocal in the past (See differences [here](https://en.wikipedia.org/wiki/Token_ring#Comparison_with_Ethernet)). Ethernet won out over token ring because it was free.

If I want two computers to talk to each other, they still have to be connected to each other for physical bit transfer. You still have to address the physical level of abstraction.

OSI 7 Layer Model

- Framework for understanding how networks work
- At any given layer, you do not have to worry about the layers below or above
- 7 Application
  - Most abstract layer (like a web browser, game, or email client).
  - This is the program that you are writing
- 3 Network
  - Networks talking to networks via IP addresses.
  - Putting together a socket creates a network level connection between two computers in code

  ```c
  int sd, i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  // AF_INET is IPv4
  // AF_INET6 is IPv6

  // SOCK_STREAM is TCP (transmission control protocol)
  // guarantees that receiving computer gets the data and can replicate it in the order it was sent. (as good as a local pipe connection) Has pieces in place to request missing parts.

  // UDP provides information regardless of whether people receive it.
  ```

  - Messages need to be formatted in a standard way and routes need to send data in a particular way.
- 2 Data Link
  - MAC (medium access control) address provides a local connection between computers on the same network
    - MAC addresses are attached to network cards
    - They are hexadecimal addresses
    - They only need to be unique on the same network
    - Duplicate MAC addresses probably won't end up on the same local network at the same time
    - Duplicate MAC addresses are not regulated as closely as IP addresses
    - Can change MAC addresses through software
  - When you plug a computer into a switch, the switch knows the MAC address of all of the computers and will send the correct information to the correct MAC address.
    - Not the case for wireless access points or hubs.
      - Sends all data for all computers to all computers.
      - Computer ignores everything that is not for his MAC address.
      - Some software can allow you to see all of the information in a wireless access point (Wireshark).
- 1 Physical
  - Most concrete layer
  - Checks physical connections of lights and wires
  - Fiber optic cables don't have loss of signals over time
  - Speed and width of data transfer is still growing
  - Is it faster than a car full of flash drives?

## Friday, 3 January, 2020

### Server / Client Design Patterns

When writing a multi-program project with interprogram communication, figuring out those connections is important!

- Peer-to-peer-program
  - Client 0 will wait for other client to say hello and then send a message
  - Direct connection between clients
  - Good for well structured interactions (e.g. turn-based games)
  - peer-to-peer format with more than 2 players may get harder to manage

- Single Server
  - One server handles all connections and all communications.
  - Client sends input, waits for something to resposnd, and server sends something back
  - Can be implemented using pipes or sockets
  - Server needs to know which client it responds to and which client it is receiving information from
  - Good for real-time components that are not structured (e.g. chats)
  - One server can get bogged down with a lot of connections

- Forking Server
  - Standardly used in file servers, ssh, etc.
  - One main server exists but is fairly specialized
    - Handles all connections
    - Does not handle communication
    - Creates a new subserver to handle all communication
  - Main server receives initial communication, forks a new subserver. The subserver sends a resposne to the client. Main server connection is severed from the client. Subservers are disconnected from main server
  - Cannot communicate between clients or subservers once connections are severed.

- Dispatch Server
  - One main server
    - Handles all connections
    - Handles all incoming data from clients
    - Subservers handle all outgoing data to clients
    - Routes messages to appropriate subservers
  - Main server has array of pipes that connect to subservers

## Wednesday, 18 December, 2019

- Semaphore operations
  - Create a semaphore
  - Set an initial value
  - Remove a semaphore
  - Up(S) / V(S) - atomic
    - Release the semaphore to signal you are done with its associated resource
    - Pseudocode
      - S++
  - Down(S) / P(S) - atomic
    - Attempt to take the semaphore.
    - If the semaphore is 0, wait for it tobe available
    - Pseudocode
      - while (S == 0) { block } S--;
  - `ipcs -s`

```c
int main() {
  int semd;
  int r;
  int v;
  semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644); // can't use same key for semaphore and shared memory
  // argument 1 represent only making one semaphore in the set of semaphore made

  if (semd == -1) { // if semaphore already exists
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0); // no permissions are needed (0)
    //argument 1 represents getting 1 semaphore

    v = semctl(semd, 0, GETVAL, 0);
    // argument 0 represents the index of the semaphore set (get semaphore 0)

    printf("semctl returned: %d\n", v);
  }
  else { // if semaphore does not exist
    union semun us; // a union is a list of possible data but will only use one of them.
    // PROGRAM HAS TO DEFINE union semun SEE man semctl (on linux)

    us.val = 1; // has value that the semaphore will have
    r = semctl(semd, 0, SETVAL, us);
    printf("semctl returned: %d\n", r);
  }
}
```

```c
int main() {
  int semd;
  int r;
  int v;

  semd = semget(KEY, 1, 0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; // data member of the struct, defines what you are doing to the semaphore (down the semaphore)

  semop(semd, &sb, 1); // perform the operation defined in sb on the semaphore
  printf("got the semaphore!\n");
  sleep(10);

  sb.sem_op = 1; // once previous operation is done, do this new operation
  semop(semd, &sb, 1);
  // argument 1 represents number of semaphores you want to operate on

  return 0;
}
```

## Tuesday, 17 December, 2019

### How do we flag down a resource?

- When a new shared memory segment is created, its contents are initialized to zero values.

```c
int main() {
  int shmd;
  char * data;
  char input[3];

  shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644); //usually 0600
  data = shmat(shmd, 0, 0);

  if(!(*data))
    printf("New segment, no data to display\n");
  else
    printf("Current contents: [%s]\n", data);

  printf("Would you like to modify the segment?(y/n) ");
  fgets(input, 3, stdin);

  if(input[0] == 'y') {
    printf("Enter new data: ");
    fgets(data, SEG_SIZE, stdin);
    *strchr(data, '\n') = 0;
    printf("Current contents: [%s]\n", data);
  }

  shmdt(data); // detach pointer from variable

  printf("Would you like to remove the segment?(y/n) ");
  fgets(input, 3, stdin);

  if(input[0] == 'y') {
    shmctl(stmd, IPC_RMID, 0);
    printf("segment deleted\n");
  }
}
```

#### Concurrency problems

Several programs can use shared memories at the same time and you could delete data that another program is using.
TWo concurrent programs can write to a file but two write processes might get mixed up in the processor, writing interweavedly.

#### Semaphores

- created by Edsger Dijkstra
- IPC construct used to control access to a shared resource (like a file or shared memory).
- Most commonly, a semaphore is used as a counter representing how many processes can acess a resource at a given time.
  - If a semaphore has a value of 3, then it can have 3 active "users".
  - If a semaphore has a value of 0, then it is unavailable.
- Most semaphore operations are "atomic", meaning they will not be split up into multiple processor instructions.

- Semaphore operations
  - Create a semaphore
  - Set an initial value
  - Remove a semaphore
  - Up(S) / V(S) - atomic
    - Release the semaphore to signal you are done with its associated resource

    - Pseudocode
      - S++
  - Down(S) / P(S) - atomic

## Monday, 16 December, 2019

### Sharing is caring

Shared Memory

- `<sys/shm.h>, <sys/ipc.h>, <sys/types.h>`
- A segment of heap memory that can be accessed by multiple processes.
- Shared memory is accessed via a key that is known by any process that needs to access it.
- Shared memory does not get released when a program exits.
- 5 Shared memory operations
  - Create the segment (happens once) - `shmget`
  - Access the segment (happens once per process) - `shmget`
  - Attach the segment to a variable (once per process) - `shmat`
  - Detach the segment from a variable (once per process) - `shmdt`
  - Remove the segment (happens once) - `shmctl`

```c
#include <sys/ipc.h>

#define KEY 24601

int main() {
  int * data;
  int shmd;

  shmget(KEY, sizeof(int), IPC_CREAT | 0640);
  printf("shmd: %d\n"); // 131072

  data = shmat(shmd, 0, 0);

  printf("*data: %d\n", *data); // 0
  *data = *data + 10;
  printf("*data: %d\n", *data); // 10

  shmdt(data); // shared memory still exists but pointer is removed
  printf("*data: %d\n", *data); // segmentation fault

  return 0;
}
```

`ipcs -m`
`ipcrm -m SHARED_MEMORY_ID`

## Thursday, 12 December, 2019

### A Pipe by any Other Name...

Named Pipes

- Also known as FIFOs (first in first out).
- Same as unnamed pipes except FIFOs have a name that can be used to identify them via different programs.
- Like unnamed pipes, FIFOs are unidirectional.
- `mkfifo`
  - Shell command to make a FIFO

- `mkfifo - <sys/types.h> <sys/stat.h>`
  - c function to create a FIFO
  - Return 0 on success and -1 on failure
  - Once created, the FIFO acts like a regular file, and we can use open, read, write, and close on it.
  - FIFOs will block on open until both ends of the pipe have a connection.
  - `mkfifo(name, permissions)`

## Wednesday, 11 December, 2019

### Ceci n'est pas une pipe

Pipe

- A conduit between 2 separate processes on the same computer.
- Pipes have 2 ends, a raed end and a write end.
- Pipes act just like files (i.e. you can `read()` and `write()` to send any kind of data).
- Pipes exist in memory.
- Unnamed pipes have no external identifier.

- `pipe - <unistd.h>`
  - Create an unnamed pipe.
  - Returns 0 if the pipe was created, -1 if not.
  - `pipe(descriptors)`
    - `descriptors`
      - Array that will contain the descriptors for each end of the pipe. Must be an `int` array of size 2.
      - `descriptors[0]` is the read end.
      - `descriptors[1]` is the write end.

## Friday, 6 December, 2019

### Redirection; how does it ... SQUIRREL

#### File Redirection

- Changing the usual input/output behavior of a program
- Command line redirection
  - `>` redirects stdout to a file
    - Overwrites the contents of the file.
    - `>>` redirects stdout to a file by appending.
  - `2>` redirects stderr to a file
    - Overwrites the file (`2>>` appends)
  - `&>` redirects stdout and stderr
    - Overwrites the file (`&>>` appends)
  - `<` redirects stdin from a file

#### Redirection in c programs

- `dup2 - <unistd.h>`
  - `dup2( fd1, fd2 )` redirects `fd2` to `fd1`
  - Any use of fd2 will now act on the file for fd1
- `dup - <unistd.h>`
  - `dup(fd)` duplicates an exiting entry if the file in the table
  - Returns a new file descriptor for the duplicate entry

## Monday, 2 December, 2019

### Wait for it...

#### Managing Sub-Processes

- `wait() <sys/wait.h>`
  - Stops a parent process from running until any child has exited.
  - Returns the pid of the child that exited, or -1 (errno), and gathers information about the child process (this is called reaping)
  - If multiple child processes exit, an arbitrary one will be reaped.
  - `wait(status)`
  - Status macros
    - Usage: `MACRO(status)`
    - `WIFEXITED`: True if child exited normally
    - `WEXITSTATUS`: The return value of the child
    - `WIFSIGNALED`: True if child exited due to a signal
    - `WTERMSIG`: The signal number intercepted by the child

## Wednesday, 27 November 2019

### What the fork?

Managing Sub-Proccesses

- `fork() - <unistd.h>`
  - Creates a separate process based on the current one, the new process is called a child, the original is the parent.
  - The child process is a duplicate of the parent process.
  - All parts of the parent process are copied, including stack and heap memory, and the file table.
  - Returns 0 to the child and the child's pid, or -1 (error), to the parent.

## Tuesday, 26 November 2019

- `strsep - <string.h>`
  - Parse a string with a common delimiter
  - In place parsing
  - `strsep( source, delimiters )`
    - Locates the first occurence of any of the specified `delimiters` in a string and replaces it with `NULL`
    - `delimiters` is a string, each character is interpreted as a distinct delimiter
    - Returns the beginning of the original string, sets `source` to the string starting at 1 index past the location of the new `NULL`

    ```c
    char line[100] = "woah-this-is-cool";
    char *curr = line;
    char *token;
    token = strseo(&curr, "-");
      // replaces the - after woah with NULL
      // returns a pointer to the w in "woah"
      // sets curr to point to the t in "this-is-cool"
    ```

## Monday, 25 November 2019

### Executive Decisions

The `exec` family - `<unistd.h>`

- A group of c functions that can be used to run other programs.
- Replaces the current process with the new program.
- `execl`
  - `execl(path, command, arg0, arg1 ... NULL)`
    - `path` - the path to the program (ex: `"/bin/ls"`)
    - `command` - the name of the program (ex: `"ls"`)
    - `arg 0 ...` - Each command line argument you wish to give the program (ex: `"-a", "-l"`)
    - The last argument must be `NULL` to signify the end of the number of arguments
- `which <program-name>` gives location of where program is located
- `echo <text>` prints stuff
- `echo $PATH` gives list of directories where shell looks for executable programs (PATH environment variables)
- `execlp`
  - `execlp(path, command, arg0, arg1 ... NULL)`
  - Works like `execl`, except it used the `$PATH` environment variable for commands.
- `execvp`
  - `execvp(path, argument_array)`
    - `argument_array`
      - Array of strings containing the arguments to the command.
      - `argument_array[0]` must be the name of the program.
      - The last entry must be `NULL`

## Friday, 22 November 2019

```c
static void sighandler(int signo) {
  if(signo == SIGINT) {
    printf("haha! Can't touch this!\n");
  }
  if(signo == SIGSEGV) {
    printf("northing to see here..\n");
  }
}
```

### Sending Mixed Signals

Signal handling in c programs `<signal.h>`

- `sighandler`
  - To intercept signals in a c program you must create a signal handling function
  - Some signals (like `SIGKILL`, `SIGSTOP`) cannot be caught
  - `static void sighandler( int signo )`
    - Must be `static`, must be `void`, must take a single `int` parameter
    - `static`
      - Static values in c exist outside the normall call stack, they can be accessed regardless of the function at the top.
      - For static variables, this also means they retain their value even if the function they are declared in has ended.
      - Static values (variables and functions) can only be access from within the file they are declared.
- `exit(int)`
  - quits a program

## Thursday, 21 November 2019

### Mixed Signals

- Signal
  - Limited way of sending information to a process.
  - Sends an integer value to a process
  - `$ kill`
    - Command line utility to send a signal to a process
    - `$ kill pid`
      - Sends signal 15 (`SIGTERM`) to `pid`
    - `$ kill -signal pid`
      - Sends `signal` to `pid`
    - `$ killall [-signal] process_name`
    - Signals in c programs `<signal.h>`

## Wednesday, 20 November 2019

### Are your processes runing? - Then go out and catch them!

- Processes
  - Every running program is a process
  - A process can create subprocesses, but these are no different from regular processes
  - A processor can handle 1 process per cycle (per core).
  - "Multitasking" appears to happen because the processor switches between all the active processes quickly.

## Tuesday, 19 November 2019

- `sscanf - <stdio.h>`
  - Reads in data from a string using a format string to determine types
  - `sscanf( char * s, char * format, void * var 0, void * var1, ...)`
  - Copies the data into each variable
  - example:

    ```c
    int x; float f; double d;
    sscanf(s, "%d, %f, %lf", &x, &f, &d);
    ```

  - returns number of conversions made

## Monday, 18 November 2019

### You want Input? fget(s) about it!

Command Line Arguments:

- `int main (int argc, char * argv[])`
- Program name is considered the first command line argument
- `argc`
  - number of command line arguments
- `argv` (argument vector)
  - array of command line arguments as strings

- `fgets - <stdio.h>`
- Read in data from a file stream and store it in a string.
- `fgets( char * s, int n, FILE * f);`
  - Reads at most `n - 1` characters from file stream `f` and stores it in `s`, appends `NULL` to the end.
- Stops at newline, end of file, or the byte limit.
- File stream
  - `FILE *` type, more complex than a file descriptor, allows for buffered input.
  - `stdin` is a `FILE *` variable
- Example:
  - `fgets(s, 100, stdin)`

## Thursday, 14 November 2019

### Where do compsci clergy keep their files? - In d'rectory!

All directories are 4096 bytes and are executable.

Directories

- A linux directory is a file containing the names of the files within the directory along with basic information, like file type.
- Linux will increase the directory size if needed.

`opendir - <dirent.h>`

- open a directory file
- This will ***not*** change the current working directory (cwd), it only allows your program to read the contents of the directory file
- `opendir(path)`
  - Returns a pointer to a directory stream (`DIR *`)

`readdir - <dirent.h>`

- `readdir(dir_stream)`
  - Returns a pointer to the next entry in a directory stream, or NULL if all entries have already been returned.
  - `struct dirent - <sys/types.h>`

## Wednesday, 13 November 2019

`stat - <sys/stat.h>`

- Get information about a file (metadata)
  - As storage got cheaper and OSs got faster, more metadata exists
  - For text files, metadata contains hash tables for the contents of the file, allowing for searches to return relevant returns based on content queries.
- `stat(path, stat_buffer)`
  - `stat_buffer`
    - must be a pointer to a `struct stat`
    - All the file information gets put into the stat buffer
    - Some of the fields in `struct stat`:
      - `st_size`
        - file size in bytes
      - `st_uid, st_gid`
        - user id, group id
      - `st_mode`
        - file permissions of int type
      - `st_atime, st_mtime`
        - last access, last modification
        - These are `time_t` variables. We can use functions in `time.h` to make sense of them
          - `ctime(time)` returns a string based on time variable

## Tuesday, 12 November 2019

### Seek and ye shall find

`lseek - <unistd.h>`

- Set the ucrrent position in an open file
- `lseek(file_descriptor, offset, whence)`
  - `offset` - number of bytes to move the position by. Can be negative
  - `whence` - where to measure the offset from
    - `SEEK_SET` - offset is evaluated from the beginning of the file
    - `SEEK_CUR` - offset is relative to the current position in the file
    - `SEEK_END` - offset is evaluated from the end of the file
  - returns the number of bytes the current position is from the beginning of the file or -1 (errno).

**Files are storage, not memory. You cannot go past the bounds of a file!**

## Friday, 8 November 2019

### Read your writes!

```c
  printf("O_RDONLY: \t%d\n", O_RDONLY); // 0
  printf("O_WRONLY: \t%d\n", O_WRONLY); // 1
  printf("O_RDWR:   \t%d\n", O_RDWR);   // 2
  printf("O_CREAT:  \t%d\n", O_CREAT);  // 64
  printf("O_EXCL:   \t%d\n", O_EXCL);   // 128 if a file exists and you want to create it, will return an error
  printf("O_TRUNC:  \t%d\n", O_TRUNC);  // 512 starts at beginning of file
  printf("O_APPEND: \t%d\n", O_APPEND); // 1024 starts at end of file
  // each constant in decimal is a 1 with a bunch of 0s after
  // bitwise or (|) will combine them
```

If you do not set the mode argument when creaing a file, you will get random permissions.

- `umask - <sys/stat.h>`
  - set the file creation permission mask
  - By default, created files are not given the exact permissions provided in the mode argument to open. Some permissions are automatically shut off

  ```c
    -  mask:         000 000 010 (write for others is shut off)
    - ~mask:         111 111 101 (bit wise negation)
    -  mode:         110 110 110
    - ~mask & mode : 110 110 101 (bit wise negation of mask, bitwise and mode)
  - the default linux mask is 002
  - umask(0) //no mask
  ```

- `read - <unistd.h>`
  - read data from a file
  - `read(fd, buff, n)`
    - read n bytes from fd's file into buffer
    - returns the number of bytes actually read. Returns -1 and sets errno if unsuccessful.
    - buff must be a pointer

```c
  char buff[100];
  int fd = open("foo", O_RDONLY);
  read(fd, buff, sizeof(buff));
```

- `write - <unistd.h>`
  - write data to a file
  - `write(fd, buff, n)`
    - write n bytes to fd's file from buffer
    - returns the number of bytes actually written. Returns -1 and sets errno if unsuccessful.
    - buff must be a pointer

- `close`
  - closes file
  - returns -1 and sets errno if unsuccessful.
  - `close(fd)`

## Thursday, 7 November 2019

- `open - <fcntl.h>`
  - Add a file to the file table and returns its file descriptor
  - If open fails, -1 is returned, extra error information can be found in errno.
    - errno is an int variable that can be found in `<errno.h>`
    - `strerror(errno)` returns the string descriptor of the errno

    ```c
    if (fd < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    ```

  - `open(path, flags, mode)`
    - mode
      - only used when creating a file. Set the new file's permissions using a 3 digit octal #.
    - flags
      - determine what you plan to do with the file, using the following constants and combine with |:
        - O_RDONLY
        - O_WRONLY
        - O_RDWR
        - O_APPEND
        - O_TRUNC
        - O_CREAT
        - O_EXCL: when combined with O_CREAT, will return an error if the file exists.

## Wednesday, 6 November 2019

### Opening up a world of possibilities

- Everything is a file
- File permissions
  - 3 types of permissions
    - read
    - write
    - execute
  - See permissions with `ls -l`
  - Permissions can be represented as 3-digit binary #s, or 1-digit octal #s
    - 100 <==> 4 => read only
    - 111 <==> 7 => read, write, execute
  - There are 3 permission "areas"
    - user, group, others
    - Membership in each area is mutually exclusive
    - The creator of the file is the default setting for the user and group of a file.
  - `chmod permissions file` (change mode)
    - command line utility to change file permissions
    - The owner of a file (or root) can change permissions
    - File ownership and group can be changed with the `chown` and `chgrp` command line utilities
- File Table
  - A list of all files being used by a program while it is running
  - Contains basic information like the file's location and size
  - The file table has limited space, which contains a power of 2 and commonly 256.
  - `getdtablesize()` will return the file table size
  - Each file is given an integer index, starting a 0, this is the file descriptor
  - There are 3 files always open in the table:
    - 0 or STDIN_FILENO: stdin
    - 1 or STDOUT_FILENO: stdout
    - 2 or STDERR_FILENO: stderr

## Monday, 4 November 2019

### A Bit O' Wisdom

- binary, octal and hexadecimal integers
- `%d //decimal intenger`
- `%o //octal integer`
- `%x //hexadecimal integer`

- you can define native integers in base 2, 8 and 16 by using the following prefixes
- `0b : binary`
- `0 : octal`
- `0x : hexadecimal`

- Why do programmers confuse halloween with christmas?
- Because 31 oct is 25 dec

#### Bitwise operators

- Evaluated on every bit of a value
- ~x is negation (flip every bit of x)
- a | b is bitwise or (perform logical or for each pair of bits in (a,b))
- a & b is bitwise and (perform logical and for each pair of bits in (a,b))
- a ^ b is bitwise xor

```c
char i = 13
i: 00001101

!i: 0
~i: 11110010

char x = 8;
x: 00001000
~i | x : 11111010
~i & x : 00000000

a = a ^ b // a contains bits not in common
b = a ^ b // b now contains a
a = b ^ a // a now contains b

r = a ^ b
b = r ^ b => a ^ b ^ b = 0 ^ a
a = r ^ b => a ^ b ^ a = 0 ^ b
```

- **Swapping Bits Using Only Bitwise Operators**

| a | b | a = a ^ b | b = a ^ b | a = b ^ a |
|---|---|-----------|-----------|-----------|
| T | T | F         | T         | T         |
| T | F | T         | T         | F         |
| F | T | T         | F         | T         |
| F | F | F         | F         | F         |

## Monday, 28 October 2019

`make DEBUG=true` compiles gcc with -g flag

```make
ifeq ($(DEBUG), true) //variable DEBUG is defined at the commandline
  CC = gcc -g //convention that variable names are all caps
else
  CC = gcc
endif

all: main.o llist.o
  $(CC) -o test_list main.o llist.o
```

## Thursday, 24 October 2019

### Get 'Dem Bugs

- GDB - GNU DeBugger
  - to use gdb, you must compile using the -g flag with gcc
  - Basic usage `$ gdb program`
    - This starts a gdb shell from which you can run your program
  - Commands from in the gdb shell
    - run: runs the program until it ends, crashes, gets a signal
    - list: show the lines of code run around a crash
    - print var: print the value of var
    - backtrace: show the current stack
    - break number: breaks at line number
  - Running a program in pieces
    - run: restarts the program
    - continue: run the program until the next breakpoint, crash, end
    - next: runs the next line of the program
      - if next line is a function call, it will call entire function
    - step: run the next line of the program, if that is a function call, run only the next line of that function

- Valgrind
  - Tool for debugging memory issues in C programs
  - You must compile with -g in order to use valgrind
  - Usage:
    - `valgrind --leak-check=yes ./program`
    - provides heap memory summary

## Wednesday, 23 October 2019

```c
  calloc(size_t n, size_t x)

  // allocates n * x bytes of memory, ensuring every bit is 0;
  // extra work is being done by the os by malloc
  // no need to use calloc if you immediately add data
  // use when making strings so you know you have a terminating null

  //works like malloc in all other ways

  realloc(void *p, size_t x)

  // changes the amount of memory allocated for a block to x bytes
  // x is not how much you increase the allocation by

  // p must point to the beginning of a block

  // returns a pointer to the beginning of the block ( this is not always the same as p )

  // if x is smaller than the original size of the allocation, the extra bytes will be released
  // if x is larger than the original size then either:
      // 1. if there is enough space at the end of the original allocation, the original allocation will be updated
      // 2. if there is not enough space, a new allocation will be created, containing all the original values. The original allocation will be freed
```

## Tuesday, 22 October 2019

### Malloc & Free: The Dynamic Duo!

- Dynamic memory allocation

```c
  malloc(size_t x)
  // allocates x bytes of heap memory
  // returns the address at the beginning of the allocation
  // returns a void *

  int *p
  p = malloc(5 * sizeof(int));

  // variable type limits what you can do

  free(void * p)
  // releases dynamically allocated memory
  // has one parameter, a pointer to the beginning of a dynamically allocated block of memory
  // cannot free parts of allocation have to free all of an allocation
  // can still access a piece of memory after releasing it but this is not a good idea
  // set a pointer to NULL after freeing it as a caution

  // every call to malloc/calloc should have a corresponding free.

  calloc(size_t n, size_t x)

  // allocates n * x bytes of memory, ensuring every bit is 0;
```

## Monday, 21 October 2019

How to get into a heap of trouble

```c
struct login {
  char password[100];
  int id;
};
```

- can be an efficiency problem if you copy the login struct over and over again if passing to method or returning it
- if login struct instead has a pointer to an array, you cannot be sure that that array will exist forever

### Stack memory vs Heap memory

- every program can have its own stack and heap
- Stack memory
  - as a data structure, it is last in first out (push stuff onto stacks and then pop them off)
  - Stores all normally declared variables including pointers, structs, arrays, and function calls
  - Functions are pushed onto the stack in the order that they are called, and popped off when completed
  - When a function is popped off the stack, the stack memory associated with it is released

```c
int main(){
  printf("%lf\n", sqrt(2));
  return 0;
}
```

- sqrt is the third function call that is put on the stack
  - sqrt completes and gets popped off
- printf is the second function call that is put on the stack
  - printf completes and gets popped off
- main is the first function call that is put on the stack
  - main completes and gets popped off

- Heap memory
  - Stores dynamically allocated memory
  - memory is allocated during runtime
  - Data will remain in the heap until it is manually released (or the program terminates)

## Friday, 18 October 2019

`struct login u = new_account(4190);`

- memory is allocated of size `struct login` for u
- new_account creates a `struct login` locally but returns the data
- this data is copied over into the memory at u.

## Tuesday, 15 October 2019

### Struct

- create a new type that is a collection of values
- similar to an enum
- Student data (string name, id integer, average double)
- these do not work like objects
  - they have no methods
- struct declaration
`struct {int a; char x; } s;  //s is a variable of type: struct {int a; char x;}`
- struct instantiation
- we use the .operator to access a value inside a struct
- `s.a = 10; s.x = '@';`
- c interacts with structs the same way it does primitives
- structs passed into functions will have a copy made of them for local function
  - values of original struct are not changed even if changed in passed struct
- may have extra memory for padding but has guaranteed amount of variables inside structs
- storing pointers in a struct is not advised if you want to actually store values in an array because it will only have enough space for the pointer, not whole array
- `struct foo {int a; char x;}; //variable name is NOT foo. foo is the "name" of the structure so it is no longer anonymous`
- foo is a prototype for the struct
- `struct foo s0;`
- gcc will correctly transfer values between non-anon structs
- generally a bad idea to typedef a struct
  - this hides that a variable is a struct
- there needs to be a semicolon after brace closes struct because gcc expects a variable name at end of struct prototype.
- normally don't declare structs inside mai
  - struct prototypes are defined outside of any particular function
  - can also declare struct prototypes in header files
- . operator has precedence over the * (dereference) operator
  - To access data from a struct pointer, you would do:
  - `struct foo *p; p = &s; (*p).a;`
  - new operater is `p->x;`

## Thursday, 10 October 2019

### Finding your type (cont'd)

- using `typedef` is useful so that the same source doe is portable to different systems.
- size of a pointer is 8 and size of a size_t is 8 on 64 bit machine
- size of a pointer is 4 and size of a size_t is 4 on 32 bit machine
- can typedef a typedef

## Tuesday, 8 October 2019

### Makefile

- automates creation of executables
- not specific to C though it was made in mind for C
- puts different files together for single executable
- gcc outputs executable file via system
- javac outputs a java .class file (binary machine code) that is not fully executable
- .class files are run by java virtual machine
- can only have one main function in C program
- multi-file C program has one main with various other functions
- however C files you have, you should have that many separate make compilation components
- gcc -c makes C files into machine code that goes into gcc -o to make an executable file
- each compilation should be .c file and all .h dependencies
- there should be a .o file for each .c file, and these .o files should  be put in the all executable creation line
- create make files even for one file programs for convenience
- make stops when there is an error in one of the lines of execution

### Finding your type

- size_t is a primitive
- typedef provides a new name for an existing data type
- `typedef real_name new_name;`
- `typedef unsigned long size_t;`
- `size_t x = 139; //x is really of type unsigned long`
- better readability
- size_t tells you more about a variable type than unsigned long does
- do not have to worry about the size of size_t despite being on different computers that have different variable type sizes

## Friday, 4 October 2019

| Primitives | Byte Size |
|------|-|
|char  |1|
|short |2|
|int   |4|
|long  |8|
|float |4|
|double|8|

### Pointers

- pointers are variable types for storing memory addresses
- pointers are unsigned integers of 8 bytes (unless more specialized)
- stores a memory address(integer) that fits in 8 bytes or less
- pointers can point to pointers
- the reason for pointers being 8 bytes large is a combination of os and hardware restrictions

#### CPU

- stuff goes into a CPU (instruction (add next two values to come in/ copy next value to memory location) or data)
  - instructions (e.g. add next two values to come in, copy next value to memory location)
  - several inputs are fed in at once / all read at same time
  - each input is a bit
  - As standard, 64 bits (8 bytes) come in at a time
- CPU outputs a result
  - 2 gHz - runs 2 billion cycles per second

- processer must be able to read memory address in one input
  - thus pointers are 8 bytes in 64 bit processer machines
  - size of the pointer will depend on the size of the processing available
  - running same program on different computers may result in different pointer sizes
  - there are 2^64 theoretical memory addresses

```c
int x; // in memory, x refers to a 4 byte chunk (for example purposes, the address is 2000)

int *p; // in memory, p refers to an 8 byte chunk (for example purposes, theg address is 2010)

x = 12; // the value 12 is assigned to x

// uninitialized pointers point to unknown memory address

p = 51;
//assigning a literal value to a pointer is a bad idea
// points to memory address 51. (get a segmentation error probably)

//only literal value  that is viable is 0 -> points to null

p = &x; (address of x)
//p has a value of 2000;
//p points to x;

//* (dereference means go to this location and interact with value)

*p = 6; //at memory location 2000, the value is now 6;

// pointers as parameters
def foo(int *f) {
    *f = 10;
}

foo(p)

//functions get own memory address space and every parameter is copied

//new variable f is made in the memory space for foo
//f is a copy of p
//value of f is 2000

//f has its own memory address (20)

//can modify primitive if you have its address

//adding one to int star adds 4 to the memory address
```

## Thursday, 3 October 2019

java .java -> .class -> jvm -> os -> hardware

c .c -> executable ->os -> hardware

protected memory
os allocates memory for programs and keeps track
programs cannot access memory outside of their allocation
most operating systems have a c level that can do stuff with data security

segmentation fault

- most common C error?
- program is trying to access segment of memory that it shouldnt
- sent by operating system to program
- trying to access the 10000000th element of an array in an array with size 5

 most problems in code are trying to access code that you dont have

- java just had more clear warnings than c

operating system may not give you a contiguous block of bytes when allocating memory
they may be fragmented

char *p; pointer

char s0[6]; memory address

p = s0; p now points to the start of the s0 array

char s0[6] = "hello"; [h][e][l][l][o][0] // this is a mutable piece of memory but another immutable literal is made

p = s0; // points to the mutable string

p[0] = 'j'; // mutable string is changed

p = "hello" //now points to the immutable literal
