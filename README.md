# Hash Comparison

This little project aim to compare a knowed hash with a file which is fill with word to hash and compare with the knowed hash. 

After you compile this little program with the Makefile you can execute the programm with the following command : 
  - ./HashCheck FileToHash KnowHash HashType HashMode

Different mode are available : 
  - file mode (-f) : hash the file to compare with the knowed hash.
  - line mode (-l) : hash each line of the file to compare with the knowed hash.

This little program allow the users to choose the type of hash : 
  - MD5
  - SHA1
  - ...
