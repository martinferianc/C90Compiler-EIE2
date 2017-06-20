Documentation
=============

AST
===

Overview Diagram
----------------

![my-ast.png](my-ast.png)

Description
-----------

Every node in the AST inherits only from one base pure abstract class named `Expression`.

```Cpp
class Expression
public:
  virtual string print(const bool& complete) const =0;
  virtual void add(Expression* _exp)= 0;
  virtual void codeGen(const string& destReg, Context& context) = 0;
  //... more functions
};
```

Every node then implements the set of methods in a specialised way. The nodes can be grouped into families, according to their characteristic type fields (`id`, `type`), containers (`vector<Expression*>`) or similar behaviour (_Jump Statement_).

The _Top Level_, _Container_  or _Complex_ classes have vectors which hold expressions belonging to the respective scope. The `Program` class is at the top of the tree. Other classes have up to three branches which can hold an expression - which can be from any other class family.

The branches and leaf nodes of the tree are independent of each other, however a parent node can delegate the output of a child node into a register that has been previously claimed by the parent (`destReg`). Hence the classes containing other objects do not have to worry about their implementation, they may only execute their own task and free their own resources. They can however interact with each other through the `Context` class which keeps all the bindings and meta-data and every node has read-write access.

Strengths
---------

### Strength 1

The presented AST design has a very practical feature which is the common API. Because every class inherits from `Expression` which is purely abstract, every class has one and only one standard set of functions that it implements in similar way and uses for interaction.

### Strength 2

Another advantage of this approach is its atomicity and polymorphism. Every class implements its own version of the `codeGen` method, not directly relying on the previous object, but only on context provided by the `Context` class and it's own information (e.g. `type`, `id`).

Limitations
-----------

### Limitation 1

The tree structure has limited inheritence, which creates a requirement for duplicate classes. For example, `ParameterList`, `VariableList` and `ArgumentList` could be combined into a `List` class, achieving the same functionality.

### Limitation 2

Every time a method is needed for a given task, it is evaluated if it is needed in general scope of the AST. If yes, then it has to be implemented in every single class, which can introduce errors and redundancy.

Variable binding
================

Binding Diagram (extra, hopefully not a problem)
----------------

![binding.png](binding.png)

General approach
----------------

The general approach that was considered was to have two containers (vectors): `variables` of Class `Var`, `registers` of Class `Reg` within the Context. To figuratively bind the most current information from both vectors together a dictionary was introduced: `bindings` to hold the _variable id_ : _reg_id_ pairs. The information about the bindings is divided between the two classes. A variable remembers it's memory location, scope (might be multiple because of multiple declarations) and current register binding. The register remembers the variable id, register id and a frame pointer. It is remembering the frame pointer because the register selected might have been from range 16-23, which according to convention the callee has to save and load.

When a variable is found in a scope a function, the compiler uses the Context API to get resources or information.
```Cpp
bool Context::isInContext(const string& var_id)
```
If it isn't, it asks for a new register to be bound with:
```Cpp
string Context::getFreeRegister(const string& parameter_flag)
```
After a register is freed the variable is bound via:
```Cpp
void Context::makeBinding(const string& var_id, const string& reg_id);
```
To fetch a register for that variable, even if it is in memory, the context has a function:
```Cpp
string Context::getReg(const string& var_id)
```
To deallocate unused variables, the context deallocates the binding by using:
```Cpp
void Context::releaseBinding(const string& var_id)
```
Strengths
---------
### Strength 1

The design which was considered was simplistic and minimalistic, which enabled quick iterations of different approaches, if something didn't work as expected. The bindings and register allocation from context could be all done by using 4-5 functions in a `Context` class.

### Strength 2

The important information was split into more containers, which reduced chances of missing information and emphasised scoping of variables and different variable types.

Limitations
-----------

### Limitation 1

The aim of the binding was to be simplistic and modular, but because of how modular the design is, it was tricky to find the appropriate variable. The variables could have been differentiated further by having explicit classes.

### Limitation 2

This approach duplicates information, which must be then taken care of. E.g.: the variable remembers a register id and a register remembers also the variable id. The reasoning behind is the avoid the information to be lost and eventually it can be fetched from the containers back into the current binding. If something was about to be changed, it had to be changed in all three containers.

Reflection
==========

Strengths
---------

### Strength 1

The structural hierarchy of the compiler has been thought through and classes have their own header files and cpp files, implying an orgnaized file structure. The built automation reflects the same approach and it builds files that only have been changed, making debugging, extending and iterating between different approaches very fast.

### Strength 2

It continues to _pretty print_ in XML output, which now describes every detail of every class and also scoping. This makes debugging of grammar, AST or assembly very easy.

Scope for Improvement
---------------------

### Improvement 1

The compiler is not trying to do any optimizations at all (like constant propagation, dead branch removal). It was thought that the current AST structure does not hold enough detail to enable it and make it work reliably. An improvement would be to try and optimize it in multiple passes.

### Improvement 2

Currently a function is only estimating how much space should it need on the stack and then, multiplies that by 3. That is using extensive space on the stack which is mostly redundant. A solution to that would be a precise prediction of how much memory is being used.
