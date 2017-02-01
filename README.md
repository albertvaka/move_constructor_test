# C++11 move constructor impact
## (and the importance of noexcept)

This program shows which constructors are being executed as we push instances of a class into an std::vector.

We test three diferent cases:

  * Using a class without move constructor (ala C++03).
  * Using a class with move constructor.
  * Using a class with a noexcept move constructor.

## Execution results

Here is the output we get when running this test program, slightly prettified. See some conclusions below.

### Test with simple class
```
  create capacity=0 vector
  push 1
    constr 1
    copy 1
    destr 1
  push 2
    constr 2
    copy 2
    copy 1
    destr 1
    destr 2
  push 3
    constr 3
    copy 3
    copy 1
    copy 2
    destr 1
    destr 2
    destr 3
  destroy vector
    destr 1
    destr 2
    destr 3
```
    
### Test with a class with move constructor
```
  create capacity=0 vector
  push 1
    constr 1
    move 1
    destr 1
  push 2
    constr 2
    move 2
    copy 1
    destr 1
    destr 2
  push 3
    constr 3
    move 3
    copy 1
    copy 2
    destr 1
    destr 2
    destr 3
  destroy vector
    destr 1
    destr 2
    destr 3
```

### Test with a class with noexcept move constructor
```
  create capacity=0 vector
  push 1
    constr 1
    move 1
    destr 1
  push 2
    constr 2
    move 2
    move 1
    destr 1
    destr 2
  push 3
    constr 3
    move 3
    move 1
    move 2
    destr 1
    destr 2
    destr 3
  destroy vector
    destr 1
    destr 2
    destr 3
```

Pushing something into an `std::vector` always causes a copy or move (if available) to happen. Move can be implemented faster on non-trivial classes, so it is a good idea to have it.

Note, however, that the move constructor is not always used in our second test! Unless we define a `noexcept` move constructor, a copy is still made when the `std::vector` grows internally. You can read why this happens in [this StackOverflow answer][1]. 

All this applies no matter what `-O` level we specify, and for some reason even if `-fno-exceptions` is set in `g++`.

[1]: http://stackoverflow.com/a/15730993/798724

## Running it yourself

You can compile it by using `g++` and run it like this:

```
g++ main.cpp -o test.x
./test.x
```

