// Program that controls a Super-Simple Demo Oven (SSDO) with flags
//      -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <cassert>

class SSDO                  // A Super-Simple Demo Oven
{
public:
    static constexpr int 
        RIGHT = 0b00000011, // This is how to write in binary in C++:
        LEFT  = 0b00001100, //   precede with 0b or 0B
        BAKE  = 0b00010000,
        BROIL = 0b00100000;
                            // Leftmost two bits are unused
 
    static constexpr int
        OFF = 0b00,
        LO  = 0b01,
        MD  = 0b10,
        HI  = 0b11;

    // Right burner bits are at the right -- no offset
    static constexpr int RIGHT_BURNER_OFFSET = 0;

    // But the left burners' are offset two to the left
    static constexpr int LEFT_BURNER_OFFSET = 2;

    static constexpr int FIRE = 0b00111111;

    // ctors and =
    SSDO ()            { flags_ = '\0';   }
    SSDO (const SSDO&)            = delete;
    SSDO& operator= (const SSDO&) = delete;

    // the controls
    void    setBake() { flags_ |=  BAKE;  }
    void  clearBake() { flags_ &= ~BAKE;  }
    void   setBroil() { flags_ |=  BROIL; }
    void clearBroil() { flags_ &= ~BROIL; }

    void   setLeftBurner(unsigned char c)
    {
        flags_ &= ~LEFT;
        flags_ |= (c << LEFT_BURNER_OFFSET);
    }
    void    setRightBurner (unsigned char c)
    { 
        flags_ &= ~RIGHT; 
        flags_ |= (c << RIGHT_BURNER_OFFSET); 
    }
    void clearLeftBurner ()            { setLeftBurner (OFF);}
    void clearRightBurner()            { setRightBurner(OFF);}

    // access functions
    unsigned char flags  () const      { return flags_;       }
    bool isSelfCleaning  () const // bake and broil -> self-cleaning mode
    {
        return (flags() & BAKE) && (flags() & BROIL);
    }
    bool isFireHazard    () const  // they're all on, high!
    {
        return  (flags() & FIRE) == FIRE;
    }
private:
    unsigned char flags_;          // unsigned char has at least 8 bits -- 
                                   //   that's plenty for us here
};

using namespace std;

int main ()
{
    SSDO myOven;

    // Turning the oven completely on; now it's in self-cleaning mode
    myOven.setBake ();
    myOven.setBroil();
    assert(myOven.isSelfCleaning());
    assert(myOven.flags() == 0b00110000);

    // Playing with the right burner, checking the result...
    myOven.setRightBurner   (SSDO::LO);
    myOven.clearRightBurner (); 
    assert ((myOven.flags() & SSDO::RIGHT) == 0); 

    // I probably shouldn't do this...
    myOven.setRightBurner   (SSDO::HI);
    myOven.setLeftBurner    (SSDO::HI);
    if (myOven.isFireHazard()) 
        cout << "Cut the power and call the fire department!\n";

    return 0;
}
