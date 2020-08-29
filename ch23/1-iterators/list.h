// class List:  a linked list class, now with iterators
//      from _C++20 for Lazy Programmers_

#ifndef LIST_H 
#define LIST_H

#include <iostream>

template <typename T>
class List
{
 public:
    class Underflow  {};                    // exceptions
    class BadPointer {};

    List ()                             { createEmptyList();  }
    List (const List& other) : List ()  { copy(other);        }
    ~List()                             { eraseAllElements(); delete start_; }
                                            // the elements, then the caboose

    List            (List&& other);         // move ctor
    List& operator= (List&& other);         // move =

    List <T>& operator= (const List& other)
    {
        eraseAllElements(); createEmptyList(); copy(other);
        return *this;
    }

    bool operator== (const List& other) const;    
#ifndef __cpp_impl_three_way_comparison           // Old compiler? Make !=
    bool operator!=   (const List& other) const
    {
        return !(*this == other);
    }
#endif

    int  size () const { return size_;       }     
    bool empty() const { return size() == 0; }

    void push_front(const T& newElement);          // add newElement at front
    void pop_front();                              // take one off the front
    const T& front() const
    { 
        if (empty()) throw Underflow(); else return start_->data_; 
    }
        
    void print(std::ostream&) const;
private:
    struct Entry
    {
        Entry() { next_ = nullptr;  }      // a good default
        T      data_;
        Entry* next_;
    };

    int    size_;
    Entry* start_;                         // Points to first element
    Entry* end_;                           // ...and the caboose

    void copy(const List& other);          // copies other's entries
                                           //   into this List

    void eraseAllElements();               // empties the list

    void createEmptyList()
    {
        start_ = end_ = new Entry; size_=0;// the list is...nothing
    }
public:
    class iterator                         // An iterator for List
    {
    public:
        iterator(const iterator& other)  : where_(other.where_) {}
        iterator(Entry* where = nullptr) : where_(where)        {}

        const iterator& operator= (const iterator& other)
        {
            where_ = other.where_;
        }

        bool operator== (const iterator& other) const
        {
            return where_ == other.where_;
        }
#ifndef __cpp_impl_three_way_comparison           // Old compiler? Make !=
        bool operator!= (const iterator& other) const
        {
            return !(*this == other);
        }
#endif

        const iterator& operator++()    // pre-increment, as in ++i
        {
            if (where_->next_ == nullptr) throw BadPointer();
            else where_ = where_->next_;
            return *this;
        }
        iterator operator++ (int)       // post-increment, as in i++
        {
            iterator result = *this; ++(*this); return result;
        }

        T& operator* ()
        {
            if (where_->next_ == nullptr) throw BadPointer();
            return where_->data_;
        }

        T* operator->()  // This really is how you do it.  It works!
        {
            if (where_->next_ == nullptr) throw BadPointer();
            return &(where_->data_);
        }
    private:
        Entry* where_;
    };

    iterator       begin() { return iterator(start_); }
    iterator       end  () { return iterator(end_  ); }
};

template <typename T>
inline
std::ostream& operator<< (std::ostream& out, const List<T>& foo)
{
    foo.print(out); return out;
}

template <typename T>
List<T>::List(List&& other)                   // move ctor
{
        start_ = other.start_; end_ = other.end_;  size_ = other.size_;
        other.createEmptyList();
}

template <typename T>
 List<T>& List<T>::operator= (List&& other)   // move =
{
        eraseAllElements(); delete start_; // erase all, incl. caboose
        start_ = other.start_; end_ = other.end_;  size_ = other.size_;
        other.createEmptyList();
        return *this;
}

template <typename T>
void List<T>::eraseAllElements() { while (!empty()) pop_front(); }

template <typename T>
void List<T>::push_front(const T& newElement)
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
    while (otherP->next_) // while it's not a caboose...
    {
        // Make a new entry with current element from other;
        //  put it at end of our list (so far)
        Entry* newEntry = new Entry;     // sets next_ to nullptr
        newEntry->data_ = otherP->data_; 

        // If list is empty, make it start_ with this new entry
        // If not, make its previous Entry recognize new entry 
        //   as what comes next
        if (empty()) start_ = newEntry;
        else         lastEntry->next_ = newEntry;

        lastEntry = newEntry;  // Keep pointer for lastEntry updated
        otherP = otherP->next_;// Go on to next item in other list       
        ++size_;
    }

    lastEntry->next_ = end_ = new Entry;  // attach caboose
}

template <typename T>
bool List<T>::operator== (const List& other) const
{
    if (size_ != other.size_) return false;// diff sizes => not equal

    Entry* otherp = other.start_;
    Entry* thisp =        start_;
    for (;                                 // while not at end of either
        thisp != end_ && otherp != other.end_;
        thisp = thisp->next_, otherp = otherp->next_)
        if (thisp->data_ != otherp->data_) // diff data? not equal
            return false;

    return true;                           // otherwise, equal
}

template <typename T>
void List<T>::print(std::ostream& out) const
{
    out << '[';
        
    for (Entry* thisp = start_; thisp != end_; thisp = thisp->next_)
        out << thisp->data_ << ' ';
        
    out << ']';
}
#endif //LIST_H
