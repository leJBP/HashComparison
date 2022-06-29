# Hash Comparison

This little project is still in development 

## Introduction

This little project aim to compare a knowed hash with a file which is fill with word to hash and compare with the knowed hash. 

## Compilation

To easily compile use the makefile thank to the following command : 

    make all
    
At the end of the compilation you will be able to use the programm named HashCheck.

## Usage

After you compile this little program with the Makefile you can execute the programm with the following command : 
  
    ./HashCheck FileToHash KnowHash HashType HashMode

Different mode are available (HashMode argument) : 
  - file mode `-f` : hash the file to compare with the knowed hash.
  - line mode `-l` : hash each line of the file to compare with the knowed hash.

This little program allow the users to choose the type of hash (HashType argument) : 
  - [MD5](https://en.wikipedia.org/wiki/MD5) `-md5`
  - [SHA1](https://en.wikipedia.org/wiki/SHA-1) `-sha1`
  - ...

## Working

This program work in different way depends on the `HashMode`. Due to the efficiency of this language i think there is no need to share the work (when the program is in line mode `-l`) with some son `fork()`. Feel free if you want to submit some modification in order to improve this program.
