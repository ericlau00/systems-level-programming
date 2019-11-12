# systems-level-programming
Systems Level Programming w/ Mr. Dyrland-Weaver at Stuyvesant 2019-2020

This repository contains notes, work from introductory lessons, and projects of the course.

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
- ` umask - <sys/stat.h>`
  - set the file creation permission mask
  - By default, created files are not given the exact permissions provided in the mode argument to open. Some permissions are automatically shut off
  ```
    -  mask:         000 000 010 (write for others is shut off)
    - ~mask:         111 111 101 (bit wise negation)
    -  mode:         110 110 110 
    - ~mask & mode : 110 110 101 (bit wise negation of mask, bitwise and mode) 
  - the default linux mask is 002
  - umask(0) //no mask
  ```

- ` read - <unistd.h>`
  - read data from a file
  - ` read(fd, buff, n) `
    - read n bytes from fd's file into buffer 
    - returns the number of bytes actually read. Returns -1 and sets errno if unsuccessful. 
    - buff must be a pointer 
```c
  char buff[100];
  int fd = open("foo", O_RDONLY);
  read(fd, buff, sizeof(buff));
```
  
- ` write - <unistd.h>`
  - write data to a file 
  - ` write(fd, buff, n) `
    - write n bytes to fd's file from buffer 
    - returns the number of bytes actually written. Returns -1 and sets errno if unsuccessful. 
    - buff must be a pointer 
    
- ` close `
  - closes file 
  - returns -1 and sets errno if unsuccessful.
  - `close(fd)`
  
## Thursday, 7 November 2019
- ` open - <fcntl.h>`
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
- `%x //hexadecimal integer `

- you can define native integers in base 2, 8 and 16 by using the following prefixes 
- `0b : binary`
- `0 : octal `
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
` struct {int a; char x; } s;  //s is a variable of type: struct {int a; char x;} `
- struct instantiation 
- we use the .operator to access a value inside a struct 
- `s.a = 10; s.x = '@'; `
- c interacts with structs the same way it does primitives 
- structs passed into functions will have a copy made of them for local function 
  - values of original struct are not changed even if changed in passed struct 
- may have extra memory for padding but has guaranteed amount of variables inside structs 
- storing pointers in a struct is not advised if you want to actually store values in an array because it will only have enough space for the pointer, not whole array 
- ` struct foo {int a; char x;}; //variable name is NOT foo. foo is the "name" of the structure so it is no longer anonymous `
- foo is a prototype for the struct 
- ` struct foo s0; ` 
- gcc will correctly transfer values between non-anon structs 
- generally a bad idea to typedef a struct
  - this hides that a variable is a struct 
- there needs to be a semicolon after brace closes struct because gcc expects a variable name at end of struct prototype.
- normally don't declare structs inside mai
  - struct prototypes are defined outside of any particular function 
  - can also declare struct prototypes in header files 
- . operator has precedence over the * (dereference) operator
  - To access data from a struct pointer, you would do:
  - ` struct foo *p; p = &s; (*p).a; `
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

```
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
 
