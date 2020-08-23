//Vector class:  a variable-length array
//      -- from _C++ for Lazy Programmers_

#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    class OutOfRange {};    // exception, for [] operators

    Vector () { contents_ = new int[0]; howMany_ = 0; }
    Vector (const Vector& other) { copy (other);      }
    Vector (Vector&& other) noexcept;                 // move ctor
    ~Vector() { if (contents_) delete [] contents_;   }

    Vector& operator= (const Vector& other);
    Vector& operator= (Vector&&      other) noexcept; // move =

    bool operator==   (const Vector& other) const;
#ifndef __cpp_impl_three_way_comparison   // Old compiler? Gotta make !=
    bool operator!=   (const Vector& other) const
    {
        return !(*this == other);
    }
#endif

    unsigned int size () const { return howMany_;      }

    int  operator[] (unsigned int index) const;
    int& operator[] (unsigned int index);

    void push_back  (int newElement); // add newElement at the back
private:
    int* contents_;
    unsigned int howMany_;

    void copy (const Vector& other);
};

#endif //VECTOR_H
