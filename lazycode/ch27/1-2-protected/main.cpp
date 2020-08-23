// Program to illustrate "protected" with phones
//       -- from _C++20 for Lazy Programmers_

#include <cassert>

class Phone
{
public:
    void       call    () { /*do some stuff, and then */ incNumCalls(); }
    static int numCalls() { return numCalls_; }
    
protected:
    void incNumCalls   () { ++numCalls_;      }
    
private:
    inline static int numCalls_ = 0;
};

class MobilePhone : protected Phone
{
public:
    // void call() { /* do stuff w cell towers, and */ incNumCalls(); }
    void secureCall() 
    { 
        /* do cell tower stuff */ 
        makeSecure ();
        incNumCalls(); 
    }
    
    void makeSecure() {} // however that's done
};

class SatellitePhone : public MobilePhone
{
public:
    void secureCall() 
    { 
        makeSecure ();      
        /* do satellite stuff */
        incNumCalls(); 
    }
    
    // makeSecure is inherited from MobilePhone
};

int main ()
{
    Phone P;            P.call();
    MobilePhone MP;    MP.secureCall();
    SatellitePhone SP; SP.secureCall();

    assert (Phone::numCalls() == 3); // If this assertion succeeds, 
                                     //    incNumCalls got called 3 times -- good!

    return 0;
}
