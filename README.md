# C89 compiler

This is repo containing the attempt to build a C89 compiler into a MIPS1 ISA

The compiler is built:

````
make bin/c_compiler
````
and the resulting program is in `bin/c_compiler`.

Example run and test after building:

````
make test
````

The documentation is in the `doc` folder.

### Currently implemented features

1 - [x] Local variables

2 - [x] Integer arithmetic

3 - [x] While

4 - [x] IfElse, SwitchCase

5 - [x] For

6 - [x] Function calls

7 - [x] Arrays

8 - [x] Pointers

9 - [ ] Strings

10 - [ ] Structures

11 - [ ] Floating-point
