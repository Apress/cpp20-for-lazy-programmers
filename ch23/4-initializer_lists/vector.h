//Vector class:  a variable-length array
//      -- from _C++ for Lazy Programmers_

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list> // for std::initializer_list

template <typename T>
class Vector
{
public:
    class OutOfRange {};    // exception, for [] operators

    Vector() { contents_ = new T[0]; howMany_ = 0; }
    Vector(const Vector& other) { copy(other); }
    Vector(Vector&&      other) noexcept;     // move ctor
    Vector(const std::initializer_list<T>& other);
    ~Vector() { if (contents_) delete[] contents_; }

    Vector& operator= (const Vector& other);
    Vector& operator= (Vector&& other) noexcept;  // move =

    bool operator==   (const Vector& other) const;
#ifndef __cpp_impl_three_way_comparison   // Old compiler? Gotta make !=
    bool operator!=   (const Vector& other) const
    {
        return !(*this == other);
    }
#endif

    unsigned int size() const { return howMany_; }

    const T& operator[] (unsigned int index) const;
    T& operator[] (unsigned int index);

    void push_back(const T& newElement); // add newElement at back
private:
    T* contents_;
    unsigned int howMany_;

    void copy(const Vector& other);
};

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& other) :
    Vector()
{
	// Either loop works; the second version's shorter and easier
	
    // for (auto i = other.begin(); i != other.end(); ++i)
    //     push_back(*i);
	
    for (auto i : other) push_back(i);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept              // move ctor
{
    contents_ = other.contents_; howMany_ = other.howMany_;
    other.contents_ = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector&& other) noexcept // move =
{
    if (contents_) delete[] contents_;
    contents_ = other.contents_; howMany_ = other.howMany_;
    other.contents_ = nullptr;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& other)
{
    if (this == &other) return *this; // don't assign to self --you'll trash contents
    if (contents_) delete[] contents_; copy(other);
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector& other) const
{
    if (size() != other.size()) return false; // diff sizes=>different

    bool noDifferences = true;

    // quit if you find a difference or run out of elements
    for (unsigned int i = 0; i < size() && noDifferences; ++i)
        if ((*this)[i] != other[i]) noDifferences = false;

    return noDifferences;
}

template <typename T>
const T& Vector<T>::operator[] (unsigned int index) const
{
    if (index >= size()) throw OutOfRange(); // don't allow out-of-range access
    else return contents_[index];
}

template <typename T>
T& Vector<T>::operator[] (unsigned int index)
{
    if (index >= size()) throw OutOfRange(); // don't allow out-of-range access
    else return contents_[index];
}

// add newElement at the back
template <typename T>
void Vector<T>::push_back(const T& newElement)
{
    T* newContents = new T[howMany_ + 1];     // make room for 1 more... 

    for (unsigned int i = 0; i < size(); ++i) // copy existing elements
                                              //  into new array... 
        newContents[i] = contents_[i];

    newContents[howMany_] = newElement;       // add the new element... 

    ++howMany_;                               // remember we have one more... 

    delete[] contents_;                       // throw out old contents_
    contents_ = newContents;                  //  and keep new version
}

template <typename T>
void Vector<T>::copy(const Vector& other)
{
    // set howMany to other's size; allocate that much memory
    contents_ = new int[howMany_ = other.size()];

    // then copy the elements over
    for (unsigned int i = 0; i < size(); ++i)
        contents_[i] = other[i];
}

#endif //VECTOR_H

