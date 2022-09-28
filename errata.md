# Errata for *C++20 for Lazy Programmers*

***

On **page 42** [Change word choice in comment]:
 
Change **double space at the end of the line** to **double new line at the end of the line**.

***

On **page 118** [Typo]

Change **sout << ' ';** to **sout << count << ' ';**.

***

On **page 203** [Unusual behavior on some Unix distributions]:
 
The stars are almost-invisible dots ->
The stars are almost-invisible, or invisible, dots

***

On **page 315** [Typo]

int* A = new myArray[size]; -> int* A = new int[size];

***

On **page 400** [Unusual language feature]:
 
Just before Antibugging, add: **It doesn't usually happen, but sometimes the compiler can't figure from the types of the arguments what T is. If that happens, you can specify: mySwap<float> (m, n). **.

***

On **page 499** [More instructions needed]:
 
Append to Exercise 8 **, and update all other functions (constructors, push_front, copy, etc.) as needed to keep the new data members Entry::prev_ and List::rStart_ correct**.

***

On **page 507** [More instructions needed]:
 
Append to Exercise 2: **You may need to write typename before List<T>::iterator (as in: typename List<T>::iterator), and specify T when you call the function (as in reverse<int>) -- see Chapter 20, Function templates.**.
 
Append to Exercise 5: **You may need to write typename before List<T>::iterator (as in: typename List<T>::iterator), and specify T when you call the function (as in reverse<int>) -- see Chapter 20, Function templates.**.
 
***
 
 On **page 643*** [Typo]:

For \u<8 digits>, read \U<8 digits> .

***

On **page xx** [Summary of error]:
 
Details of error here. Highlight key pieces in **bold**.

***
