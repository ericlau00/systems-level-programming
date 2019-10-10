# Systems Level Programming w/ Mr. Dyrland-Weaver at Stuyvesant 2019-2020

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
 
