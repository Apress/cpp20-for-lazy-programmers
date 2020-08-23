//Program that uses lambda functions to order cities by different criteria
//       -- from _C++20 for Lazy Programmers_

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "globalLoc.h" // provides user-defined literal operators _deg and _mi,
                       //  struct GlobalLoc, latitude, longitude, and
                       //  a distance function that works on a globe

using namespace std;  

class City
{
public:
    City (const std::string& n, int pop, const GlobalLoc& loc) :
        name_ (n), population_ (pop), location_ (loc)
    {
    }
    City            (const City&) = default;
    City& operator= (const City&) = default;
    const std::string& name    () const { return name_;       }
    int   population           () const { return population_; }
    const GlobalLoc&   location() const { return location_;   }
private:
    std::string  name_;
    int          population_;
    GlobalLoc    location_;
};

inline 
double distance (const City& xCity, const City& yCity)
{
    return distance (xCity.location(), yCity.location());
}

//// Functions for use without lambdas:
//bool lessThanByName (const City& a, const City& b)
//{
//    return a.name()       < b.name();
//}
//
//bool lessThanByPop (const City& a, const City& b)
//{
//    return a.population() < b.population();
//}

#ifdef __cpp_lib_ranges
int main()
{     
    // Some prominent party spots
    vector<City> cities =
    {
        {"London",         10'313'000, { 51_deg,  -5_deg}},
        {"Hamburg",         1'739'000, { 53_deg,  10_deg}},
        {"Paris",          10'843'000, { 49_deg,   2_deg}},
        {"Rome",            3'718'000, { 42_deg,  12_deg}},
        {"Rio de Janiero", 12'902'000, {-22_deg, -43_deg}},
        {"Hong Kong",       7'314'000, { 20_deg, 114_deg}},
        {"Tokyo",          38'001'000, { 36_deg, 140_deg}}
    };

    // Without lambdas:
    //ranges::sort (cities, lessThanByName);
    //ranges::sort (cities, lessThanByPop);

        // Print those cities in different orderings:
        
    cout << "Some major cities, in alpha order :      ";
    ranges::sort (cities, 
         [](const City& a, const City& b) 
         { 
             return a.name() < b.name(); 
         });
    for (const auto& i : cities) cout << i.name() << " / ";
    cout << endl;

    
    cout << "Ordered by population:                   "; 
    ranges::sort (cities, 
          [](const City& a, const City& b) 
          {
             return a.population() < b.population();
          });
    for (const auto& i : cities) cout << i.name() << " / "; 
    cout << endl;

    
    cout << "Ordered by how far they are from LA:     ";
    const City LA ("Los Angeles", 3'900'000, { 34_deg, -118_deg });

    // & would work here too -- but &LA is a little more secure
    ranges::sort (cities,
          [&LA](const City& a, const City& b)
          {
              return distance (LA, a) < distance (LA, b);
          });
    for (const auto& i : cities) cout << i.name() << " / "; 
    cout << endl;

    return 0;
}
#else
int main()
{
    // Some prominent party spots
    vector<City> cities =
    {
        {"London",         10'313'000, { 51_deg,  -5_deg}},
        {"Hamburg",         1'739'000, { 53_deg,  10_deg}},
        {"Paris",          10'843'000, { 49_deg,   2_deg}},
        {"Rome",            3'718'000, { 42_deg,  12_deg}},
        {"Rio de Janiero", 12'902'000, {-22_deg, -43_deg}},
        {"Hong Kong",       7'314'000, { 20_deg, 114_deg}},
        {"Tokyo",          38'001'000, { 36_deg, 140_deg}}
    };

    // Without lambdas:
    // sort (cities.begin(), cities.end(), lessThanByName);
    // sort (cities.begin(), cities.end(), lessThanByPop);

        // Print those cities in different orderings:

    cout << "Some major cities, in alpha order :      ";
    sort (cities.begin(), cities.end(),
        [](const City& a, const City& b)
    {
        return a.name() < b.name();
    });
    for (const auto& i : cities) cout << i.name() << " / ";
    cout << endl;


    cout << "Ordered by population:                   ";
    sort (cities.begin(), cities.end(),
        [](const City& a, const City& b)
    {
        return a.population() < b.population();
    });
    for (const auto& i : cities) cout << i.name() << " / ";
    cout << endl;


    cout << "Ordered by how far they are from LA:     ";
    const City LA ("Los Angeles", 3'900'000, { 34_deg, -118_deg });

    // & would work here too -- but &LA is a little more secure
    sort (cities.begin(), cities.end(),
        [&LA](const City& a, const City& b)
    {
        return distance(LA, a) < distance(LA, b);
    });
    for (const auto& i : cities) cout << i.name() << " / ";
    cout << endl;

    return 0;
}
#endif //#ifdef __cpp_lib_ranges

