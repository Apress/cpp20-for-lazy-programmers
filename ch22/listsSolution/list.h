//class List:  a linked list class
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

    List            (List&& other) noexcept { start_ = other.start_; }
    List& operator= (List&& other) noexcept { start_ = other.start_; }

    List& operator= (const List <T>& other) 
    {
        eraseAllElements (); createEmptyList(); copy(other); 
        return *this;
    }

    bool operator== (const List <T>& other) const; // left as exercise

    int  size       () const;
    bool empty      () const { return size() == 0; }

    void push_front (const T& newElement);   // add newElement at front
    void pop_front  ();                      // take one off the front
    const T& front  () const;                // left as exercise

    void print      (std::ostream&) const;   // left as exercise
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

template <typename T>
inline
std::ostream& operator<< (std::ostream& out, const List <T>& foo)
{
    foo.print(out); return out;
}

template <typename T>
void List<T>::eraseAllElements () {     while (!empty()) pop_front();   }

template <typename T>
void List<T>::push_front (const T& newElement)
{
    Entry* newEntry = new Entry; // create an entry
    newEntry->data_ = newElement;// set its data_ field to newElement
    newEntry->next_ = start_;    // set its next_ field to start_

    start_          = newEntry;  // make start_ point to new entry
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

template <typename T>
int List<T>::size() const
{
    int result = 0;

    for (Entry* loc = start_; loc != nullptr; loc = loc->next_)
        ++result;

    return result;
}

template <typename T>
void List<T>::print(std::ostream& out) const
{
    out << '[';

    for (Entry* loc = start_; loc != nullptr; loc = loc->next_)
        out << loc->data_ << ' ';

    out << ']';
}

template <typename T>
const T& List<T>::front() const
{
    if (empty()) throw Underflow(); else return start_->data_;
}

template <typename T>
bool List<T>::operator== (const List& other) const
{
    Entry* myPtr = start_;
    Entry* otherPtr = other.start_;

    for (;
        myPtr && otherPtr;
        myPtr = myPtr->next_, otherPtr = otherPtr->next_)
            if (myPtr->data_ != otherPtr->data_) return false;

    if (myPtr || otherPtr) return false; // one list is longer

    return true;
}

#endif //LIST_H