// CarMap.cpp

#include "Map.h"
#include "CarMap.h"
#include <iostream>
using namespace std;

  // Actually, we did not have to declare and implement the default
  // constructor:  If we declare no constructors whatsoever, the compiler
  // writes a default constructor for us that would do nothing more than
  // default construct the m_carMap data member.

  // We do not have to declare a destructor, copy constructor, or assignment
  // operator, because the compiler-generated ones do the right thing.

CarMap::CarMap()
{}

bool CarMap::addGas(string license, double gallons)
{
    if (gallons < 0)
        return false;
    double g;
    if (!m_carMap.get(license, g))
        return false;
    g += gallons;
    return m_carMap.update(license, g);
}

bool CarMap::useGas(string license, double gallons)
{
    if (gallons < 0)
        return false;
    double g;
    if (!m_carMap.get(license, g))
        return false;
    g -= gallons;
    return g >= 0  &&  m_carMap.update(license, g);
}

void CarMap::print() const
{
    string license;
    double gallons;
    for (int k = 0; k < m_carMap.size(); k++)
    {
        m_carMap.get(k, license, gallons);
        cout << license << ' ' << gallons << endl;
    }
}
