// time.h: defines class Time
//    -- from _C++20 for Lazy Programmers_

#ifndef TIME_H // If TIME_H is not defined...
#define TIME_H

class Time
{
public:
	Time () : hours_(0), minutes_(0), seconds_(0) {}
private:
	int hours_, minutes_, seconds_;
};

#endif //TIME_H
