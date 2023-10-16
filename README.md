# Summary

1. [Data Structures](#data-structures)
   1. [Array](#array)
   2. [Matrix](#matrix)
   3. [List](#list)
      1. [Singly Linked List](#singly-linked-list)
      2.  [Doubly Linked List](#doubly-linked-list)
      3.  [Circular Doubly Linked List](#circular-doubly-linked-list)
   4. [Stack](#stack)
      1. [Static Stack](#static-stack)
      2. [Dynamic Stack](#dynamic-stack)
   5. [Queue](#queue)
      1. [Static Queue](#static-queue)
      2. [Dynamic Queue](#dynamic-queue)
   6. [Graph](#graph)
      1. [Undirected Weighted Graph](#undirected-weighted-graph)
         1. [Adjacency Matrix Version](#adjacency-matrix-version)
         2. [Adjacency Linked List Version](#adjacency-linked-list-version)
2. [Helpers](#helpers)
    1. [Exception Handler](#exception-handler)
    2. [Node](#node)
    3. [Vertex](#vertex)
3. [Build Tool Guide](#build-tool-guide)
   1. [Creating](#creating)
      1. [New Data Structure](#new-data-structure)
      2. [New Helper](#new-helper)
   2. [Adding Dependency](#adding-dependency)
      1. [To Data Structure](#to-data-structure)
      2. [To Helper](#to-helper)
      3. [Get Dependencies Already Added](#get-dependencies-already-added)
      4. [Access Modifier](#access-modifier)
      5. [.info File](#info-file)
   3. [Testing](#testing)
      1. [Just one Data Structure Or Helper](#just-one-data-structure-or-helper)
      2. [Test Suite](#test-suite)
         1. [test](#make-test)
         2. [test-debug](#make-test-debug)
         3. [check](#make-check)
   4. [Building](#building)
   5. [Packing](#packing)
4. [Remarks](#remarks)
   1. [TYPE Specific Functions](#type-specific-functions)
   2. [Write Code To Test Implementation](#code-to-test-implementation)
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

[Click here to see its Spec.](main/Array/main/include/array.h)

[Click here to see its implementation.](main/Array/main/src/array.c)

## Matrix
A _Matrix_ is a two-dimensional [_Array_](#array) (like an Array of Arrays) organized in rows and columns. A _Matrix_ is
made up of rows and columns. The number of rows and columns in a _Matrix_ determines its size or dimensions. For example,
an "m x n" _Matrix_ has "m" rows and "n" columns.

[Click here to see its Spec.](main/Matrix/main/include/matrix.h)

[Click here to see its implementation.](main/Matrix/main/src/matrix.c)

## List
A _List_ is a [_Data Structure_](#data-structures) that stores a collection of elements in a specific order. It is a 
fundamental data structure in computer science and is commonly used to organize and manipulate data.

### Singly Linked List
A _Singly Linked List_ is a [_Data Structure_](#data-structures) used to store a collection of elements. It consists of 
a sequence of nodes, where each node contains both the element and a reference (or pointer) to the next node in the 
_List_. The last node in the _List_ has a reference to null, indicating the end of the _List_.

[Click here to see its Spec.](main/SinglyLinkedList/main/include/singly_linked_list.h)

[Click here to see its implementation.](main/SinglyLinkedList/main/src/singly_linked_list.c)

### Doubly Linked List
A _Doubly Linked List_ is a [_Data Structure_](#data-structures) that extends the functionality of a [_Singly Linked List_](#singly-linked-list) 
by providing links or references to both the previous and next nodes in the [_List_](#list). Each node in a 
_Doubly Linked List_ contains three components: the data or element to be stored, a reference to the previous node, 
and a reference to the next node.

[Click here to see its Spec.](main/DoublyLinkedList/main/include/doubly_linked_list.h)

[Click here to see its implementation.](main/DoublyLinkedList/main/src/doubly_linked_list.c)

### Circular Doubly Linked List
A _Circular Doubly Linked List_ is a variation of a [_Doubly Linked List_](#doubly-linked-list) where the last node in 
the [_List_](#list) has a reference to the first node, creating a circular structure. This means that the next node of 
the last node points back to the first node, and the previous node of the first node points to the last node.

[Click here to see its Spec.](main/CircularDoublyLinkedList/main/include/circular_doubly_linked_list.h)

[Click here to see its implementation.](main/CircularDoublyLinkedList/main/src/circular_doubly_linked_list.c)

## Stack
A _Stack_ is a fundamental [_Data Structure_](#data-structures) in computer science that follows the **LIFO (Last-In, First-Out)** principle. 
It models a collection of elements with two primary operations: push and pop.

### Static Stack
A _Static Stack_ is a [_Stack_](#stack) [_Data Structure_](#data-structures) that is implemented using a fixed-size 
[_Array_](#array) or a static memory allocation. Unlike a [_Dynamic Stack_](#dynamic-stack), where the size can grow or 
shrink dynamically as elements are pushed or popped, a _Static Stack_ has a predetermined size that is allocated at the 
time of its creation.

[Click here to see its Spec.](main/StaticStack/main/include/static_stack.h)

[Click here to see its implementation.](main/StaticStack/main/src/static_stack.c)

### Dynamic Stack
A _Dynamic Stack_ is a [_Stack_](#stack) [_Data Structure_](#data-structures) that can grow or shrink in size dynamically 
as elements are pushed or popped. Unlike a [_Static Stack_](#static-stack), which has a fixed size allocated at the time
of creation, a _Dynamic Stack_ can adjust its capacity based on the number of elements it currently holds.

[Click here to see its Spec.](main/DynamicStack/main/include/dynamic_stack.h)

[Click here to see its implementation.](main/DynamicStack/main/src/dynamic_stack.c)

## Queue
A _Queue_ is a [_Data Structure_](#data-structures) that follows the **FIFO (First-In, First-Out)** principle, where 
elements are added at the rear and removed from the front. It allows for efficient insertion and deletion operations.

### Static Queue
A _Static Queue_, if referring to a fixed-size [_Queue_](#queue), would be implemented using a fixed-size array or a 
static memory allocation. The capacity of the _Static Queue_ would be predetermined and remain constant throughout its 
lifetime.

[Click here to see its Spec.](main/StaticQueue/main/include/static_queue.h)

[Click here to see its implementation.](main/StaticQueue/main/src/static_queue.c)

### Dynamic Queue
A _Dynamic Queue_ is a [_Queue_](#queue) [_Data Structure_](#data-structures) that can grow or shrink dynamically as 
elements are enqueued (added) or dequeued (removed). Unlike a [_Static Queue_](#static-queue), which has a fixed size 
allocated at the time of creation, a _Dynamic Queue_ can adjust its capacity based on the number of elements it currently 
holds.

[Click here to see its Spec.](main/DynamicQueue/main/include/dynamic_queue.h)

[Click here to see its implementation.](main/DynamicQueue/main/src/dynamic_queue.c)

## Graph
A _Graph_ is a [_Data Structure_](#data-structures) that represents a collection of interconnected nodes or vertices,
often referred to as "points", and the connections between them, known as "edges." Graphs are used to model relationships
between objects or entities.

### Undirected Weighted Graph
An undirected weighted graph is a type of graph in graph theory that consists of a set of vertices and a set of edges.

The edges between vertices have no direction, which means they do not have a specific starting or ending point. 
If there's an edge between vertex A and vertex B, it implies that you can traverse it from A to B or from B to A with 
the same ease. This property reflects a symmetric relationship between connected vertices.

Each edge in the graph has an associated weight, which is a numerical value. These weights represent some measure or 
value associated with the relationship between the vertices connected by the edge.

#### Adjacency Matrix Version
Here _Undirected Weighted Graph_ were implemented with an adjacency matrix and [_Array_](#array) of [_Vertex_](#vertex),
where the rows and columns correspond to the vertices of the graph, and the values in the matrix represent the 
weights of the edges between those vertices.

[Click here to see its Spec.](main/UndirectedWeightedGraph1/main/include/undirected_weighted_graph_1.h)

[Click here to see its implementation.](main/UndirectedWeightedGraph1/main/src/undirected_weighted_graph_1.c)

#### Adjacency Linked List Version


# Helpers
In this context, Helpers means "more primitives Data Structures", that does not allow dependency from other complex 
[_Data Structure_](#data-structures).

## Exception Handler
The _Exception Handler_ is a special "class" designed to help with exception handling in the development of Data Structures.

[Click here to see its Spec.](resources/helpers/ExceptionHandler/main/include/exception_handler.h)

[Click here to see its implementation.](resources/helpers/ExceptionHandler/main/src/exception_handler.c)

## Node
A _Node_ is an individual element or item in the data structure. Each _Node_ contains both data and references to 
the previous and next nodes.

[Click here to see its Spec.](resources/helpers/Node/main/include/node.h)

[Click here to see its implementation.](resources/helpers/Node/main/src/node.c)

## Vertex
A _Vertex_ is a “point” on a [_Graph_](#graph) that represents an entity or element. Here it was implemented with data and valency 
property (which means how many connections the _Vertex_ has).

[Click here to see its Spec.](resources/helpers/Vertex/main/include/vertex.h)

[Click here to see its implementation.](resources/helpers/Vertex/main/src/vertex.c)

# Build Tool Guide
To abstract some repetitive steps in the process of implementing new _Data Structures_ or _Helpers_, adding dependencies,
running tests, compiling, building the library, among other things, a _Build Tool_ was created using **Makefile** and 
**Shell** scripts.

## Creating
Is possible to create a new [_Data Structure_](#data-structures) or a new [_Helper_](#helpers) directly in CLI instead 
create each directory manually.

### New Data Structure
To create a new [_Data Structure_](#data-structures), in the root of the project you can run one of the commands below:

```shell
make create-ds
```
```shell
make create datastructure
```

and enter the name of new [_Data Structure_](#data-structures).

### New Helper
To create a new [_Helper_](#helpers), in the root of the project you can run one of the commands below:

```shell
make create-h
```
```shell
make create helper
```

and enter the name of new [_Helper_](#helpers).

## Adding Dependency
You can also add local dependencies to a [_Data Structure_](#data-structures) or a [_Helper_](#helpers) already created.

**What does means local dependencies?**
It means that you can add only [_Data Structures_](#data-structures) and [_Helpers_](#helpers) created in this project.

Note that, like [_Helpers_](#helpers) does not allow dependency from complex [_Data Structure_](#data-structures), you 
can add only other [_Helpers_](#helpers) as its dependencies.

### To Data Structure
If you want to add other [_Data Structure_](#data-structures) as dependency:

```shell
make install_ds
```
or
```shell
make install ds
```

If you want to add a [_Helper_](#helpers) as dependency:

```shell
make install_helper
```
or
```shell
make install h
```

### To Helper
If you want to add other [_Helper_](#helpers) as dependency:

```shell
make install_helper
```
or
```shell
make install h
```

### Get Dependencies Already added
To get headers of dependencies already added on a or [_Data Structure_](#data-structures) on a [_Helper_](#helpers), on
its directory run:

```shell
make install 
```


### Access Modifier
Each dependency has an access modifier that rule where it will be added during Adding a new dependency. There are 3 access
modifiers: Public, Protected and Private.

1. Public (pub): The dependency include will be on header of the parent, it means that everyone with access on header can see
   how this dependency is used.
2. Protected (ptd): The dependency include will be on source code of parent, it means that only who can access source code is
   able to see how the dependency is used.
3. Private (pvt): The dependency include will not be put anywhere, just on **.info** file. It means that it is not a direct dependency
   and will be used only during compile time.

### .info File
The .info File is list of the Dependencies of a [_Data Structure_](#data-structures) or [_Helper_](#helpers) during.
It is used to verify if the dependency is already added during adding a new Dependency. The pattern of element of this 
list is: modifier_type_NameOfDependency, or modifier is the [Access Modifier](#access-modifier), type is about being a
[_Data Structure_](#data-structures) (ds) or [_Helper_](#helpers) (hp).

For example:

1. Adding the [_Exception Handler_](#exception-handler) as a public dependency: `pub_hp_ExceptionHandler`
2. Adding the [_Undirected Weighted Graph version 1_](#adjacency-matrix-version) as a protected dependency: `ptd_ds_UndirectedWeightedGraph1`
3. Adding the [_Array_](#array) as a private dependency: `pvt_ds_Array`

## Testing

### Just one Data Structure or Helper
To test any of Listed Data Structures or Helpers, you may navigate to their respective directory and run the following 
command in the terminal:

```shell
make run_tests
```

For example, if I want to run Unit Tests for Array, then:

```shell
cd main/Array && make run_tests
```

### Test Suite
To maintain a high level of quality, there are a lot of unit test for each [_Data Structure_](#data-structures) and 
[_Helper_](#helpers). If one want to run all tests at once, there are 3 modes and one can choose which is better for each
situation.

#### make test
It runs quicly and silent. During execution, it shows only which [_Data Structure_](#data-structures) or
[_Helper_](#Helpers) are executing, time spent of executed [_Data Structure_](#data-structures) and [_Helper_](#Helpers).
At final of execution, it shows how many test was executed, how many tests passes or fail and total time of execution. 

One can execute test suite in this mode by running the following command in the root of project:

```shell
make test
```

#### make test-debug
This mode is used to debug the test suite, and it runs slowly when compared with `make test`.
It shows the same as when execute `make test`, in addiction it shows each test executed (description and result).

One can execute test suite in this mode by running the following command in the root of project:

```shell
make test-debug
```

#### make check
The third is a more restrictive mode and always runs before `make build` or `make pack`, ensuring that if any test fails
the entire build or pack process is interrupted.

One can execute test suite in this mode by running the following command in the root of project:

```shell
make check
```

## Building
The _Build Command_ is used to generate and compile the Library headers `.h` and Static Lib `libds.a`
when you run in the terminal:

```shell
make build
```
or
```shell
make b
```

it runs [check command](#make-check) and if all tests passes, it will create some directories:
* `LIBDS`
* `LIBDS/include`
* `LIBDS/lib`

The headers are in `LIBDS/include` and the Static Lib`libds.a` in `LIBDS/lib`.

## Packing
The _Pack Command_ goes one step further than the [_Build Command_](#building), as its life cycle ends after 
packing the contents of the `LIDBDS` directory as `libds.tar.gz` and deleting the `LIDBDS` directory. Since the 
_Pack Command_ depends on the [_Build Command_](#building), when executed in the terminal:

```shell
make pack
```
or
```shell
make p
```

if any tests fail, the process is interrupted.

# Remarks

## TYPE specific functions
It is said at the beginning of every header of a [_Data Structure_](#data-structures) in this library, but it is worth mentioning here that,
as the implementation followed a concept of generics, to use it with any data type, it is necessary to implement at
least 3 functions:
* **TYPE printing function**: To print data correctly.
   * like: `void (*TYPE_print_function)(void *data)`
   * example:
```c
void int_print_function(void *data) {
    printf("%d", int_convert_function(data));
}
```
* **TYPE convert function**: As some functions returns void*, one must use a function to convert void* to TYPE*.
   * like: `TYPE (*TYPE_convert_function)(void *data)`
   * example:
```c
int int_convert_function(void *data) {
    return *((int *) data);
}
```
* **TYPE comparison function**: To compare correctly data.
   * like: `int (*TYPE_compare_function)(void *data1, void *data2)`
   * example:
```c
int int_compare_function(void *data1, void *data2) {
    int d1 = int_convert_function(data1), d2 = int_convert_function(data2);
    return d2 - d1;
}
```

## Code to test implementation
You can write some code, just to test some features while developing (you may consider write unit tests instead), that
implements the created _Data Structures_. Just write it in the file (`app_X.c`) inside the `/main/apps` directory and in
its [_Data Structure_](#data-structures) directory run:

```shell
make run_apps
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
* Make: 4.2.1
