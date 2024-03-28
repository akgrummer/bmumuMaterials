#### What is this?
This directory contains three files:
1. `Linkdef.h`:This file contains the lines needed to make ROOT aware of the existence of certain classes, which need to go in a dictionary (library).
2. `generic.h`:This file uses the classes/structures defined in `Linkdef.h`. If the classes/structures are not used anywhere, they will not appeak in the dictionary.
3. `Makefile`: This file is used to build the dictionary.

#### Usage
In order to build the dictionary do:
```bash
make
```
in the terminal, in order to remove the old files do:
```bash
make clean
```
Once the library `libgeneric.so` is built, do:
```c++
gSystem->Load("/path/to/library/libgeneric.so");
```
to load the library.
### Why do I need this?
The library is needed in order to read and write objects of non trivial classes in a ROOT TTree. For instance, if one branch contains objects of type:
```c++
std::map<std::string, bool>
```
you will not be able to read the tree without first loading the library.

