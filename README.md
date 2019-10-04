# Systems Level Programming w/ Mr. Dyrland-Weaver at Stuyvesant 2019-2020

## Friday, 4 October 2019 
pointers 
variable type for storing memory addresses
8 bytes large 

| Primitives | Byte Size |
|------|-|
|char  |1|
|short |2|
|int   |4|
|long  |8|
|float |4|
|double|8|
 
### Pointers
- pointers are unsigned integers of 8 bytes (unless more specialized)
- stores a memory address(integer) that fits in 8 bytes or less 
- pointers can point to pointers 
- 8 bytes is a combination of os and hardware restrictions 

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

int x;

in memory x refers to a 4 byte chunck of memory 
has address 2000; 

int *p;

in memory p refers to a 8 byte chunk of memory 
has address 2010;

x = 12; 
in x, there is 12

uninitialized pointers point to unknown memory address

p = 51;
assigning a literal value to a pointer is a bad idea
points to memory address 51. (get a segmentation error probably)

only literal value is 0 -> does not point to anything (actually it points to null)

p = &x; (address of x)
p has a value of 2000; 
p points to x;

*(dereference)

*p = 6;
dereference means go to this location and interact with value; 

at memory location 2000, the value is now 6; 

go to this memory location 
get me the value 

pointers as parameters 
def foo(int *f) {
    *f = 10;
}

foo(p)

functions get own memory address space 
every parameter is copied because it is copied 

new variable f is made in the memory space for foo 
f is a copy of p
value of f is 2000 

f has its own memory address (20)

can modify primitive if you have its address

adding one to int star adds 4 to the memory address 

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
 