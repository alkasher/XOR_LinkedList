# Memory Efficient Linked List
Implementation of a XOR doubly linked list.
Node of this List ``` Element<T> ``` stores data and difference between two pointers. Pointer:  ```Element<T>* diff ``` = ```Element<T>* next - Element<T>* prev```(this pointers van be found in realization of Linked List).
Linked List has:
1) different constructors, including copy constructor
2) push_back function - one can push back ``` Element<T> ``` or ``` T info ```
3) insert to the specified location ``` insert(int index, t info) ```:

   + In the beginning, the new node is the head -> ``` insert(0, info) ``` 
   + In the end, the new node is the tail -> ``` insert(list.size(), info) ```
   + Between the head and tail, _0 <= index <= list.size()_ -> ``` insert(index, info) ```
4) remove in the specified location ``` remove(int index) ```

Exceptions that may occur during the operation are handled.
