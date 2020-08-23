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
    List (const List& other) : List ()      { copy(other);        }
    ~List()                                 { eraseAllElements(); }

    //move functions
    List            (List&& other) noexcept;
    List& operator= (List&& other) noexcept;

    List& operator= (const List& other) 
    {
        eraseAllElements (); createEmptyList(); copy(other); 
        return *this;
    }

    bool operator== (const List& other) const; 
#ifndef __cpp_impl_three_way_comparison           // Old compiler? Make !=
    bool operator!=   (const List& other) const
    {
        return !(*this == other);
    }
#endif

    int  size () const { return size_; }
    bool empty() const { return size() == 0; }

    void push_front (const T& newElement);   // add newElement at front
    void pop_front  ();                      // take one off the front
    const T& front  () const
    {
        if (empty()) throw Underflow(); else return start_->data_;
    }

    void print      (std::ostream&) const;
 private:
    struct Entry
    {
        Entry() { next_ = nullptr; }      // a good default
        T      data_;
        Entry* next_;
    };

    int    size_;
    Entry* start_;                          // points to first element

    void copy(const List& other);           // copies other's entries
                                            //   into this List

    void eraseAllElements ();               // empties the list
    void createEmptyList  ()
    {
        start_ = nullptr; size_ = 0;        // the list is...nothing
    }
};

// I/O

template <typename T>
inline
std::ostream& operator<< (std::ostream& out, const List <T>& foo)
{
    foo.print(out); return out;
}

template <typename T>
void List<T>::print(std::ostream& out) const
{
    out << '[';

    for (Entry* loc = start_; loc != nullptr; loc = loc->next_)
        out << loc->data_ << ' ';

    out << ']';
}

// Move functions

template <typename T>
List<T>::List (List&& other) noexcept
{
    start_ = other.start_; size_ = other.size_;
    other.createEmptyList();
}

template <typename T>
List<T>& List<T>::operator= (List&& other) noexcept
{
    eraseAllElements();                      // Clear out old list
    start_ = other.start_;                   // Take in new list
    size_ = other.size_;

    other.createEmptyList();                 // Make other list empty

    return *this;
}

// Adding and deleting

template <typename T>
void List<T>::eraseAllElements () {     while (!empty()) pop_front();   }

template <typename T>
void List<T>::push_front (const T& newElement)
{
    Entry* newEntry = new Entry; // create an Entry
    newEntry->data_ = newElement;// put newElement in its data_ field
    newEntry->next_ = start_;    // put old version of start_
                                 //  in its next_ field

    start_          = newEntry;  // put address of new Entry 
                                 //  into start_
    ++size_;
}

template <typename T>
void List<T>::pop_front()
{
    if (empty()) throw Underflow();

    Entry* temp = start_;   // store location of thing to delete
    start_ = start_->next_; // let start_ = next thing after start_

    delete temp;            // delete the item
    --size_;
}

template <typename T>
void List<T>::copy(const List& other)
{
    size_ = 0;                    // start with 0 entries

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

        ++size_;
    }
}

// Comparisons

template <typename T>
bool List<T>::operator== (const List& other) const
{
    if (size_ != other.size_) return false;// diff sizes => not equal

    Entry* myPtr = start_;
    Entry* otherPtr = other.start_;

    for (;
        myPtr && otherPtr;
        myPtr = myPtr->next_, otherPtr = otherPtr->next_)
        if (myPtr->data_ != otherPtr->data_) return false;

    if (myPtr || otherPtr) return false;   // one list is longer

    return true;                           // otherwise, equal
}
#endif //LIST_H