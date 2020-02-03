# PM-0 VM for PL-0

a  virtual  machine  (VM)  known  as  the  P-machine 
(PM/0).  The  P-machine  is  a  stack  machine  with  two  memory  stores:  the  stack,  which  is 
organized  as  a  stack  and  contains  the  data  to  be  used  by  the  PM/0  CPU,  and  the  text, 
which contains the instructions for the VM. The PM/0 CPU has four registers to handle the 
stack  and  text  segments:  The  registers  are  named  base  pointer  (BP),  stack  pointer  (SP), 
program counter (PC) and instruction register (IR). They will be explained in detail later on 
in this document. The machine also has a register file (RF) with eight (8) registers (0-7).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Things you will need

```
C compiler
```

## Running the tests

An input and output files have been coded in the program. Running without changing those files will generate an example output.

### To test your own input 

Do the following

```
Delete the input.txt file given and replace with your own
Make sure the file name is �input.txt�
```
Or
```
Change line 426 to strcpy(input_file_name, �*your file name*�);
Make sure it is a .txt file
```





## Authors

* **Diego Rodrigues** - [diegoro1](https://github.com/diegoro1)

