# Summary

1. [Data Structures](#data-structures)
   1. [Array](#array)
   2. [List](#list)
      1. [Singly Linked List](#singly-linked-list)
      2.  [Doubly Linked List](#doubly-linked-list)
      3.  [Circular Doubly Linked List](#circular-doubly-linked-list)
   3. [Stack](#stack)
      1. [Static Stack](#static-stack)
      2. [Dynamic Stack](#dynamic-stack)
   4. [Queue](#queue)
      1. [Static Queue](#static-queue)
      2. [Dynamic Queue](#dynamic-queue)
2. [How to Test, Build and Pack](#how-to-test-build-and-pack)
   1. [Test Command](#test-command)
      1. [Test Only One Data Structure](#test-only-one-data-structure)
      2. [Test Suite](#test-suite)
   2. [Build Command](#build-command)
   3. [Pack Command](#pack-command) 
3. [Creating a New Data Structure](#creating-a-new-data-structure)
4. [How to run your test-app for a Data Structure](#how-to-run-your-test-app-for-a-data-structure)
5. [Exercises](#exercises)
   1. [Self-Organizing List](#self-organizing-list)
   2. [ADT - Abstract Data Type](#adt---abstract-data-type)
6. [Some used Versions](#some-used-versions)

# Data Structures
A [_Data Structure_](#data-structures) is a way of organizing and storing data in a computer system. It provides a 
systematic and efficient way of accessing and manipulating data. Data structures are designed to suit different types of
data and various operations that need to be performed on that data.

## Array
An _Array_ is a fundamental [_Data Structure_](#data-structures) that allows storing a fixed-size sequence of elements 
of the same type. It provides a way to organize and access data in a contiguous block of memory. Each element in an 
array is identified by its index, which represents its position within the _Array_.

[Click here to see its Spec.](DSs1/Array/main/include/array.h)

[Click here to see its implementation.](DSs1/Array/main/src/array.c)

## List
A _List_ is a [_Data Structure_](#data-structures) that stores a collection of elements in a specific order. It is a 
fundamental data structure in computer science and is commonly used to organize and manipulate data.

### Singly Linked List
A _Singly Linked List_ is a [_Data Structure_](#data-structures) used to store a collection of elements. It consists of 
a sequence of nodes, where each node contains both the element and a reference (or pointer) to the next node in the 
_List_. The last node in the _List_ has a reference to null, indicating the end of the _List_.

[Click here to see its Spec.](DSs1/SinglyLinkedList/main/include/singly_linked_list.h)

[Click here to see its implementation.](DSs1/SinglyLinkedList/main/src/singly_linked_list.c)

### Doubly Linked List
A _Doubly Linked List_ is a [_Data Structure_](#data-structures) that extends the functionality of a [_Singly Linked List_](#singly-linked-list) 
by providing links or references to both the previous and next nodes in the [_List_](#list). Each node in a 
_Doubly Linked List_ contains three components: the data or element to be stored, a reference to the previous node, 
and a reference to the next node.

[Click here to see its Spec.](DSs1/DoublyLinkedList/main/include/doubly_linked_list.h)

[Click here to see its implementation.](DSs1/DoublyLinkedList/main/src/doubly_linked_list.c)

### Circular Doubly Linked List
A _Circular Doubly Linked List_ is a variation of a [_Doubly Linked List_](#doubly-linked-list) where the last node in 
the [_List_](#list) has a reference to the first node, creating a circular structure. This means that the next node of 
the last node points back to the first node, and the previous node of the first node points to the last node.

[Click here to see its Spec.](DSs1/CircularDoublyLinkedList/main/include/circular_doubly_linked_list.h)

[Click here to see its implementation.](DSs1/CircularDoublyLinkedList/main/src/circular_doubly_linked_list.c)

## Stack
A _Stack_ is a fundamental [_Data Structure_](#data-structures) in computer science that follows the **LIFO (Last-In, First-Out)** principle. 
It models a collection of elements with two primary operations: push and pop.

### Static Stack
A _Static Stack_ is a [_Stack_](#stack) [_Data Structure_](#data-structures) that is implemented using a fixed-size 
[_Array_](#array) or a static memory allocation. Unlike a [_Dynamic Stack_](#dynamic-stack), where the size can grow or 
shrink dynamically as elements are pushed or popped, a _Static Stack_ has a predetermined size that is allocated at the 
time of its creation.

[Click here to see its Spec.](DSs1/StaticStack/main/include/static_stack.h)

[Click here to see its implementation.](DSs1/StaticStack/main/src/static_stack.c)

### Dynamic Stack
A _Dynamic Stack_ is a [_Stack_](#stack) [_Data Structure_](#data-structures) that can grow or shrink in size dynamically 
as elements are pushed or popped. Unlike a [_Static Stack_](#static-stack), which has a fixed size allocated at the time
of creation, a _Dynamic Stack_ can adjust its capacity based on the number of elements it currently holds.

[Click here to see its Spec.](DSs1/DynamicStack/main/include/dynamic_stack.h)

[Click here to see its implementation.](DSs1/DynamicStack/main/src/dynamic_stack.c)

## Queue
A _Queue_ is a [_Data Structure_](#data-structures) that follows the **FIFO (First-In, First-Out)** principle, where 
elements are added at the rear and removed from the front. It allows for efficient insertion and deletion operations.

### Static Queue
A _Static Queue_, if referring to a fixed-size [_Queue_](#queue), would be implemented using a fixed-size array or a 
static memory allocation. The capacity of the _Static Queue_ would be predetermined and remain constant throughout its 
lifetime.

[Click here to see its Spec.](DSs1/StaticQueue/main/include/static_queue.h)

[Click here to see its implementation.](DSs1/StaticQueue/main/src/static_queue.c)

### Dynamic Queue
A _Dynamic Queue_ is a [_Queue_](#queue) [_Data Structure_](#data-structures) that can grow or shrink dynamically as 
elements are enqueued (added) or dequeued (removed). Unlike a [_Static Queue_](#static-queue), which has a fixed size 
allocated at the time of creation, a _Dynamic Queue_can adjust its capacity based on the number of elements it currently 
holds.

[Click here to see its Spec.](DSs1/DynamicQueue/main/include/dynamic_queue.h)

[Click here to see its implementation.](DSs1/DynamicQueue/main/src/dynamic_queue.c)

# How to Test, Build and Pack
To compile all the code, the **Makefile** was used. This way, 
[you can run unit tests for each [_Data Structure_](#data-structures) separately](#test-only-one-data-structure), 
[but it is also possible to run a test suite that test all _Data Structures_](#test-suite). [It is also possible to write
and  run a small program to use the implementation of a [_Data Structure_](#data-structures)](#how-to-run-your-test-app-for-a-data-structure), 
however the objective of this repository is to create a library that contains the _Data Structures_ described above, 
for this we can run a [_Build command_](#build-command) or a [_Pack command_](#pack-command).

## Test Command

### Test only one Data Structure
To test any of Listed Data Structures, you may navigate to their respective directory and run the following command in 
the terminal:

```shell
make run_tests
```

For example, if I want to run Unit Tests for Array, then:

```shell
`cd DSs1/Array && make run_tests`
```

### Test Suite
To run the test suite, just run in the terminal:

```shell
make test
```

## Build Command
The _Build Command_ is used to generate and compile the Library headers `.h` and Static Lib `libds1.a`.
when you run in the terminal:

```shell
make build
```

it runs the test suite and if all the tests pass it will create some directories:
* `LIBDS1`
* `LIBDS1/include`
* `LIBDS1/lib`

The headers are in `LIBDS1/include` and the Static Lib`libds1.a` in `LIBDS1/lib`.

## Pack Command
The _Pack Command_ goes one step further than the [_Build Command_](#build-command), as its life cycle ends after 
packing the contents of the `LIDBDS1` directory as `libds1.tar.gz` and deleting the `LIDBDS1` directory. Since the 
_Pack Command_ depends on the [_Build Command_](#build-command), when executed in the terminal:

```shell
make pack
```

if any tests fail, the process is interrupted.

# Creating a new Data Structure
To create a new [_Data Structure_](#data-structures), you can use CLI instead create each directory manually.
Just run the below command in the terminal and follow the steps:
```shell
make create
```
It will create the needed directory structure to implement the new [_Data Structure_](#data-structures).

# How to run your test-app for a Data Structure
You can write a small program that implements any of the _Data Structures_, just write it in the file (`app_ .c`) inside
the `/main/apps` directory and run it in the terminal (inside [_Data Structure_](#data-structures) directory):

```shell
make run_apps
```

It is said at the beginning of every header of a [_Data Structure_](#data-structures) in this library, but it is worth mentioning here that, 
as the implementation followed a concept of generics, to use it with any data type, it is necessary to implement at
least 3 functions:
* **Type printing function**: To print data correctly.
  * like: `void (*type_print_function)(void * data)` 
  * example:
```c
void _print_int(void *data) {
    printf("%d", _convert_to_int(data));
}
```
* **Type convert function**: As some functions returns void*, one must use a function to convert void* to type*.
  * like: `type (*type_convert_function)(void * data)`
  * example:
```c
int _convert_to_int(void *data) {
    return *((int *) data);
}
```
* **Type comparison function**: To compare correctly data.
  * like: `int (*type_compare_function)(void *data1, void *data2)`
  * example:
```c
int _compare_int(void *data1, void *data2) {
    int d1 = _convert_to_int(data1), d2 = _convert_to_int(data2);
    return d2 - d1;
}
```

# Exercises

## Self-Organizing List
A _Self-Organizing List_ is a [_Data Structure_](#data-structures) that reorganizes its elements based on the frequency of access or some 
other criteria in order to optimize future access patterns. It dynamically adjusts the order of elements to improve the 
efficiency of common operations, such as searching or accessing frequently used elements.

- Define a [_Self-Organizing List_](/Exercises/Self-organizing%20List/main/include/self_organizing_linked_list.h) of 
[Product](/Exercises/Self-organizing%20List/main/include/product.h) and 
[implements](/Exercises/Self-organizing%20List/main/src) it.

- Can run the [app](/Exercises/Self-organizing%20List/main/apps/products_self_organizing_linked_list.c) in the terminal:

```shell
make run_apps
```

- Can run tests in the terminal:

```shell
make run_tests
```

## ADT - Abstract Data Type
_ADT_ is a high-level description of a [_Data Structure_](#data-structures) that defines the behavior of a data type independently of its 
implementation details. _ADTs_ provide a logical representation of data and operations that can be performed on that 
data, without specifying how those operations are implemented.

- Define an _ADT_ called [float_vector](/Exercises/ADT/include/float_vector.h) and 
[implements](/Exercises/ADT/src/float_vector.c) it.


# Some used versions
* OS: Ubuntu 20.04.6 LTS (Focal Fossa)
* GCC: 9.4.0
* C: C17 (201710L)
* Unity Framework: 2.5.2
