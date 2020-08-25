// class List:  a linked list class
//      from _C++20 for Lazy Programmers_

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class List
{
 public:
    class Underflow  {};                    // exception

    List ()                                 { createEmptyList();  }
    List (const List <T>& other) : List ()  { copy(other);        }
    ~List()                                 { eraseAllElements(); }

    //move functions
    List   (List&& other)          noexcept { start_ = other.start_; }
    List& operator= (List&& other) noexcept { start_ = other.start_; }

    List& operator= (const List <T>& other) 
    {
        eraseAllElements (); createEmptyList(); copy(other); 
        return *this;
    }

    bool operator== (const List <T>& other) const; // left as exercise

    int  size      () const;
    bool empty     () const { return size() == 0; }

    void push_front(const T& newElement);   // add newElement at front
    void pop_front ();                      // take one off the front
    const T& front () const;                // left as exercise

    void print     (std::ostream&) const;   // left as exercise
 private:
    struct Entry
    {
        T      data_;
        Entry* next_;
    };

    Entry* start_;                          // points to first element

    void copy(const List <T>& other);       // copies other's entries
                                            //   into this List

    void eraseAllElements ();               // empties the list
    void createEmptyList  ()
    {
        start_ = nullptr;                   // the list is...nothing
    }
};

// I/O

template <typename T>
inline
std::ostream& operator<< (std::ostream& out, const List <T>& foo)
{
    foo.print(out); return out;
}

// Adding and deleting

template <typename T>
void List<T>::eraseAllElements () {  while (!empty()) pop_front();  }

template <typename T>
void List<T>::push_front (const T& newElement)
{
    Entry* newEntry = new Entry; // create an Entry
    newEntry->data_ = newElement;// put newElement in its data_ field
    newEntry->next_ = start_;    // put old version of start_
                                 //  in its next_ field

    start_          = newEntry;  // put address of new Entry 
                                 //  into start_
}

template <typename T>
void List<T>::pop_front()
{
    if (empty()) throw Underflow();

    Entry* temp = start_;   // store location of thing to delete
    start_ = start_->next_; // let start_ = next thing after start_

    delete temp;            // delete the item
}

template <typename T>
void List<T>::copy(const List <T>& other)
{
    Entry* lastEntry = nullptr;   // last thing we added to this list,
                                  //   as we go thru other list
    Entry* otherP = other.start_; // where are we in the other list?

    // while not done with other list... 
    //    copy its next item into this list
    while (otherP)
    {
        // make a new entry with current element from other;
        //  put it at end of our list (so far)
        Entry* newEntry = new Entry;
        newEntry->data_ = otherP->data_;
        newEntry->next_ = nullptr;
        
        // if list is empty, make it start_ with this new entry
        // if not, make its previous Entry recognize new entry 
        //   as what comes next
        if (empty()) start_           = newEntry;
        else         lastEntry->next_ = newEntry;

        lastEntry = newEntry;  // keep pointer for lastEntry updated
        otherP = otherP->next_;// go on to next item in other list
    }
}
#endif //LIST_H