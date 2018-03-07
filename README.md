# C90 to MIPS Compiler
This is a C90 (ANSI C) to MIPS compiler. The compiler uses Flex for the lexer, Bison for the parser and virtual functions for the assembly code generation.

The repository also contains parser and lexer in separate directories under the `/src` directory. It also contains a plenty of test for all three programs. 

More information on the design of the compiler can be seen in the [docs](/doc/README.md).

## Specification
This piece of work was done in partial fulfilment of a language processors module. The specification for the coursework can be found [here](https://github.com/LangProc/langproc-2016-cw).

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

## Building and Running
This must be run on an environment with Flex and Bison installed, a [vagrant file](Vagrantfile) configured to the correct target environment has been included , run `vagrant up`, `vagrant ssh`, `cd /vagrant/` and finish with `exit`.

The compiler can built by doing:
```
make bin/c_compiler
```

The compiler accepts valid C code through `stdin` and will return MIPS code through `stdout`, for example, if we create a file `test.c` and we store it under `/test/c_compiler/test`:
```C
int main(){
  int j = 10;
  int i = 2;
  return i + j;
}
```
and then run it via the testing shell script:

```bash
./test_compiler_unit.sh 1
```

the file `output.s` will contain:
```assembly
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text

	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	addiu $sp,$sp,-80
	sw $31,76($sp)	# Storing return address
	sw $fp,72($sp)	# Storing current frame pointer
	move $fp,$sp
	move $t9,$0
	move $2,$0
	move $t0,$0	 #Making Binding j
	sw $t0,0($fp)	 #Saving variable: j
	lw $t0,0($fp)	 #Loading variable: j
	li $t1,10	 #Value to register 10
	move $t0,$t1	 #Assigning value 
	sw $t0,0($fp)	 #Saving variable: j
	move $t1,$0	 #Making Binding i
	sw $t1,4($fp)	 #Saving variable: i
	lw $t1,4($fp)	 #Loading variable: i
	li $t2,2	 #Value to register 2
	move $t1,$t2	 #Assigning value 
	sw $t1,4($fp)	 #Saving variable: i
	move $2,$0
	lw $t1,4($fp)	 #Loading variable: i
	lw $t0,0($fp)	 #Loading variable: j
	add $2,$t1,$t0	 #Adding values 
	b $EXIT_FUNC1
	nop
	 #Releasing binding: i
	 #Releasing binding: j
	 #==Clearing scope context==
$EXIT_FUNC1:
	 #==Loading used variables 16-23==
	move $sp,$fp
	lw $fp,72($sp)	# Loading current frame pointer
	lw $31,76($sp)	# Loading return address
	addiu $sp,$sp,80
	j $31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
```
which will also produce a pretty print XML structure of the AST:

```xml
<Program>
    <Function id="main" type="int">
        <Scope>
            <BinaryExpression>
                <Left>
                    <Variable id="j" type="int"/>
                </Left>
                <Operator op="="/>
                <Right>
                    <NumberInt value="10"/>
                </Right>
            </BinaryExpression>
            <BinaryExpression>
                <Left>
                    <Variable id="i" type="int"/>
                </Left>
                <Operator op="="/>
                <Right>
                    <NumberInt value="2"/>
                </Right>
            </BinaryExpression>
            <Return>
                <BinaryExpression>
                    <Left>
                        <Variable id="i" type=""/>
                    </Left>
                    <Operator op="+"/>
                    <Right>
                        <Variable id="j" type=""/>
                    </Right>
                </BinaryExpression>
            </Return>
        </Scope>
    </Function>
</Program>
```

## Credits
Martin Ferianc. 2017.
