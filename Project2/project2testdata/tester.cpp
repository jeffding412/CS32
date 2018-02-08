#include "OurType.h"
#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <type_traits>
#include <cassert>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
	return OurType::m_count;
}

inline int nasstcopys()
{
	return OurType::m_asstcopycount;
}

KeyType SOMEKEY = OurType(123);
KeyType DEFAULT = KeyType();
KeyType ARRAY[6] = {
	OurType(10), OurType(20), OurType(30),
	OurType(40), OurType(50), OurType(60)
};

ValueType SOMEVALUE = "junk";
ValueType DEFAULTV = ValueType();
ValueType ARRAYV[6] = {
	"able", "baker", "charlie", "delta", "echo", "foxtrot"
};

struct PairType
{
	PairType() : k(SOMEKEY), v(SOMEVALUE) {}
	KeyType k;
	ValueType v;
};

bool isPermutation(Map& m, const KeyType ka[], const ValueType va[], int n)
{
	if (m.size() != n)
	    return false;
	vector<PairType> a(n);
	for (int i = 0; i < n; i++)
	    m.get(i, a[i].k, a[i].v);
	for (int j = 0; j < n; j++)
	{
		int i;
		for (i = j; i < n; i++)
		{
			if (ka[j] == a[i].k  &&  va[j] == a[i].v)
			{
				PairType t = a[j];
				a[j] = a[i];
				a[i] = t;
				break;
			}
		}
		if (i == n)
			return false;
	}
	return true;
}

bool has(const Map& m, const KeyType& k, const ValueType& v)
{
	ValueType v2 = DEFAULTV;
	m.get(k, v2);
	ValueType v3 = SOMEVALUE;
	m.get(k, v3);
	return v2 == v  &&  v3 == v;
}

bool get2type(bool (Map::*)(const KeyType&, ValueType&) const) { return true; }
bool get2type(bool (Map::*)(const KeyType&, ValueType&)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&)) { return false; }
bool get3type(...) { return false; }

void testone(int n)
{
	Map m;
	switch (n)
	{
				 default: {
	    cout << "Bad argument" << endl;
			} break; case  1: {
	    assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
			} break; case  2: {
	    assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
			} break; case  3: {
	    assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
			} break; case  4: {
	    assert(get2type(&Map::get));
			} break; case  5: {
	    assert(get3type(&Map::get));
			} break; case  6: {
	    assert(m.empty());
			} break; case  7: {
	    assert(m.size() == 0);
			} break; case  8: {
	    assert(!m.update(DEFAULT, SOMEVALUE)  &&  m.size() == 0);
			} break; case  9: {
	    assert(!m.erase(DEFAULT)  &&  m.size() == 0);
			} break; case 10: {
	    assert(!m.contains(DEFAULT));
			} break; case 11: {
	    ValueType v = SOMEVALUE;
	    assert(!m.get(DEFAULT, v)  &&  v == SOMEVALUE);
			} break; case 12: {
	    ValueType v = SOMEVALUE;
	    assert(!m.get(0, DEFAULT, v)  &&  v == SOMEVALUE);
			} break; case 13: {
	    assert(m.insert(SOMEKEY, SOMEVALUE));
			} break; case 14: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    assert(!m.empty());
			} break; case 15: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    assert(m.size() == 1);
			} break; case 16: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    assert(m.contains(SOMEKEY));
			} break; case 17: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    ValueType v = DEFAULTV;
	    assert(m.get(SOMEKEY, v));
			} break; case 18: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    ValueType v = DEFAULTV;
	    m.get(SOMEKEY, v);
	    assert(v == SOMEVALUE);
			} break; case 19: {
	    m.insert(ARRAY[0], SOMEVALUE);
	    ValueType v = DEFAULTV;
	    assert(!m.get(ARRAY[1], v));
			} break; case 20: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    ValueType v = SOMEVALUE;
	    m.get(ARRAY[1], v);
	    assert(v == SOMEVALUE);
			} break; case 21: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    KeyType k = DEFAULT;
	    ValueType v = DEFAULTV;
	    assert(m.get(0, k, v));
			} break; case 22: {
	    m.insert(SOMEKEY, SOMEVALUE);
	    KeyType k = DEFAULT;
	    ValueType v = DEFAULTV;
	    m.get(0, k, v);
	    assert(k == SOMEKEY  &&  v == SOMEVALUE);
			} break; case 23: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.empty()   &&  m.size() == 2);
			} break; case 24: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.contains(ARRAY[0])  &&  m.contains(ARRAY[1]));
			} break; case 25: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
			} break; case 26: {
	    m.insert(ARRAY[0], SOMEVALUE);
	    m.insert(ARRAY[1], SOMEVALUE);
	    assert(has(m, ARRAY[0], SOMEVALUE)  &&  has(m, ARRAY[1], SOMEVALUE));
			} break; case 27: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
			} break; case 28: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[0], ARRAYV[2]);
	    assert(m.size() == 2);
			} break; case 29: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[0], ARRAYV[2]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
			} break; case 30: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(!m.insert(ARRAY[0], ARRAYV[2]));
			} break; case 31: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(!m.insert(ARRAY[0], ARRAYV[0]));
			} break; case 32: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.update(ARRAY[1], SOMEVALUE);
	    assert(m.size() == 3  &&  m.contains(ARRAY[0])  &&
			m.contains(ARRAY[1])  &&  m.contains(ARRAY[2]));
			} break; case 33: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.update(ARRAY[1], SOMEVALUE);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], SOMEVALUE)  &&
						has(m, ARRAY[2], ARRAYV[2]));
			} break; case 34: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    assert(m.update(ARRAY[1], SOMEVALUE));
			} break; case 35: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.update(ARRAY[2], ARRAYV[0]);
	    assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
			has(m, ARRAY[1], ARRAYV[1])  &&  !m.contains(ARRAY[2]));
			} break; case 36: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.update(ARRAY[2], ARRAYV[2])  &&  !m.update(ARRAY[3], ARRAYV[0]));
			} break; case 37: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
	    assert(!m.empty()   &&  m.size() == 2);
			} break; case 38: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
			} break; case 39: {
	    m.insert(ARRAY[0], SOMEVALUE);
	    m.insertOrUpdate(ARRAY[1], SOMEVALUE);
	    assert(has(m, ARRAY[0], SOMEVALUE)  &&  has(m, ARRAY[1], SOMEVALUE));
			} break; case 40: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insertOrUpdate(ARRAY[1], ARRAYV[1]));
			} break; case 41: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
	    assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[2])  &&
						has(m, ARRAY[1], ARRAYV[1]));
			} break; case 42: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
			} break; case 43: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.insertOrUpdate(ARRAY[1], SOMEVALUE);
	    assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
			has(m, ARRAY[1], SOMEVALUE)  &&  has(m, ARRAY[2], ARRAYV[2]));
			} break; case 44: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    assert(m.insertOrUpdate(ARRAY[1], SOMEVALUE));
			} break; case 45: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
	    assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
			has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[0]));
			} break; case 46: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
			} break; case 47: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.erase(ARRAY[1]));
			} break; case 48: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[1]);
	    assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[0], ARRAYV[0])  &&
							!m.contains(ARRAY[1]));
			} break; case 49: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[0]);
	    assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[1], ARRAYV[1])  &&
							!m.contains(ARRAY[0]));
			} break; case 50: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[0]);
	    m.erase(ARRAY[1]);
	    assert(m.size() == 0);
			} break; case 51: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.erase(ARRAY[1]);
	    m.erase(ARRAY[2]);
	    m.insert(ARRAY[3], ARRAYV[3]);
	    assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
			has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[1])  &&
							!m.contains(ARRAY[2]));
			} break; case 52: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.erase(ARRAY[2])  &&  m.size() == 2);
			} break; case 53: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k;
	    ValueType v;
	    assert(!m.get(-1, k, v));
			} break; case 54: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k = SOMEKEY;
	    ValueType v = SOMEVALUE;
	    m.get(-1, k, v);
	    assert(k == SOMEKEY  &&  v == SOMEVALUE);
			} break; case 55: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k;
	    ValueType v;
	    assert(!m.get(2, k, v));
			} break; case 56: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k = SOMEKEY;
	    ValueType v = SOMEVALUE;
	    m.get(2, k, v);
	    assert(k == SOMEKEY  &&  v == SOMEVALUE);
			} break; case 57: {
	    m.insert(DEFAULT, SOMEVALUE);
	    assert(m.size() == 1  &&  has(m, DEFAULT, SOMEVALUE));
			} break; case 58: {
	    m.update(DEFAULT, SOMEVALUE);
	    assert(m.size() == 0  &&  !m.contains(DEFAULT));
			} break; case 59: {
	    m.insertOrUpdate(DEFAULT, SOMEVALUE);
	    assert(m.size() == 1  &&  has(m, DEFAULT, SOMEVALUE));
			} break; case 60: {
	    m.insert(DEFAULT, SOMEVALUE);
	    m.erase(DEFAULT);
	    assert(m.size() == 0  &&  !m.contains(DEFAULT));
			} break; case 61: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(m.size() == 3);
	    }
			} break; case 62: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[2])  &&
			has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[0]));
	    }
			} break; case 63: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(m2.size() == 2);
	    }
			} break; case 64: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(has(m2, ARRAY[0], ARRAYV[0])  &&  has(m2, ARRAY[1], ARRAYV[1])  &&
			!m2.contains(ARRAY[2])  &&  !m2.contains(ARRAY[3]));
	    }
			} break; case 65: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.insert(ARRAY[3], ARRAYV[3]);
	    m.insert(ARRAY[4], ARRAYV[4]);
	    {
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		m2.insert(ARRAY[0], ARRAYV[0]);
		int n = nasstcopys();
		m.swap(m2);
		int n2 = nasstcopys();
		assert(n2 < n+3);
	    }
			} break; case 66: {
	    int before = itemcount();
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		assert(itemcount() > before);
	    }
	    assert(itemcount() == before);
			} break; case 67: {
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.erase(ARRAY[1]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.erase(ARRAY[2]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.erase(ARRAY[0]);
		m2.erase(ARRAY[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
	    }
	    assert(true);  // no corruption so bad that destruction failed
			} break; case 68: {
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		Map m3(m2);
		m3.insert(ARRAY[2], ARRAYV[2]);
		m3.erase(ARRAY[1]);
		m3.insert(ARRAY[3], ARRAYV[3]);
		m3.erase(ARRAY[2]);
		m3.insert(ARRAY[1], ARRAYV[1]);
		m3.erase(ARRAY[0]);
		m3.erase(ARRAY[3]);
		m3.insert(ARRAY[4], ARRAYV[4]);
	    }
	    assert(true);  // no corruption so bad that destruction failed
			} break; case 69: {
	    int before = itemcount();
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		int mid = itemcount();
		Map m3(m2);
		assert(m3.size() == 3);
		assert(itemcount() - mid == mid - before);
	    }
	    assert(itemcount() == before);
			} break; case 70: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
		m2.insert(ARRAY[3], ARRAYV[3]);
		assert(m2.size() == m.size()+1);
	    }
			} break; case 71: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
		m2.insert(ARRAY[3], ARRAYV[3]);
		assert(isPermutation(m2, ARRAY, ARRAYV, 4));
	    }
			} break; case 72: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
		m2.insert(ARRAY[3], ARRAYV[3]);
		assert(isPermutation(m, ARRAY, ARRAYV, 3));
	    }
			} break; case 73: {
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		Map m3;
		m3.insert(ARRAY[3], ARRAYV[3]);
		m3.insert(ARRAY[4], ARRAYV[4]);
		m3 = m2;
		m3.insert(ARRAY[2], ARRAYV[2]);
		m3.erase(ARRAY[1]);
		m3.insert(ARRAY[3], ARRAYV[3]);
		m3.erase(ARRAY[2]);
		m3.insert(ARRAY[1], ARRAYV[1]);
		m3.erase(ARRAY[0]);
	    }
	    assert(true);  // no corruption so bad that destruction failed
			} break; case 74: {
	    int before = itemcount();
	    {
		Map m2;
		Map m3;
		int mid = itemcount();
		m3.insert(ARRAY[0], ARRAYV[0]);
		m3.insert(ARRAY[1], ARRAYV[1]);
		m3 = m2;
		assert(m3.size() == 0);
		assert(itemcount() == mid);
	    }
	    assert(itemcount() == before);
			} break; case 75: {
	    int before = itemcount();
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		int mid = itemcount();
		Map m3;
		m3.insert(ARRAY[4], ARRAYV[4]);
		m3.insert(ARRAY[5], ARRAYV[5]);
		m3 = m2;
		assert(itemcount() - mid == mid - before);
	    }
			} break; case 76: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		m2 = m;
		m2.insert(ARRAY[5], ARRAYV[5]);
		assert(m2.size() == m.size()+1);
	    }
			} break; case 77: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		m2.insert(ARRAY[5], ARRAYV[5]);
		m2 = m;
		m2.insert(ARRAY[2], ARRAYV[2]);
		assert(isPermutation(m2, ARRAY, ARRAYV, 3));
	    }
			} break; case 78: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		m2.insert(ARRAY[4], ARRAYV[4]);
		m2.insert(ARRAY[5], ARRAYV[5]);
		m2 = m;
		m2.insert(ARRAY[2], ARRAYV[2]);
		assert(isPermutation(m, ARRAY, ARRAYV, 2));
	    }
			} break; case 79: {
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		int n2 = itemcount();
		m2 = m2;
		assert(itemcount() == n2);
	    }
	    assert(true);  // no corruption so bad that destruction failed
			} break; case 80: {
	    {
		Map m2;
		m2.insert(ARRAY[0], ARRAYV[0]);
		m2.insert(ARRAY[1], ARRAYV[1]);
		m2.insert(ARRAY[2], ARRAYV[2]);
		m2 = m2;
		m2.insert(ARRAY[3], ARRAYV[3]);
		assert(isPermutation(m2, ARRAY, ARRAYV, 4));
	    }
			} break; case 81: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    Map m3;
	    combine(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 3));
			} break; case 82: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    Map m3;
	    combine(m2, m, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 3));
			} break; case 83: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    Map m3;
	    combine(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 5));
			} break; case 84: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    Map m3;
	    assert(combine(m, m2, m3));
			} break; case 85: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    Map m3;
	    m3.insert(ARRAY[2], ARRAYV[5]);
	    combine(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 5));
			} break; case 86: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    Map m3;
	    m3.insert(ARRAY[2], ARRAYV[5]);
	    assert(combine(m, m2, m3));
			} break; case 87: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    Map m3;
	    combine(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 4));
			} break; case 88: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    Map m3;
	    assert(combine(m, m2, m3));
			} break; case 89: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[3], ARRAYV[3]);
	    Map m2;
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    m2.insert(ARRAY[3], ARRAYV[4]);
	    Map m3;
	    combine(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 3));
			} break; case 90: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[3], ARRAYV[3]);
	    Map m2;
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    m2.insert(ARRAY[3], ARRAYV[4]);
	    Map m3;
	    assert(!combine(m, m2, m3));
			} break; case 91: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    combine(m, m2, m);
	    assert(isPermutation(m, ARRAY, ARRAYV, 5));
			} break; case 92: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    combine(m, m2, m2);
	    assert(isPermutation(m2, ARRAY, ARRAYV, 5));
			} break; case 93: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    Map m3;
	    subtract(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 3));
			} break; case 94: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    Map m3;
	    subtract(m2, m, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 0));
			} break; case 95: {
	    m.insert(ARRAY[3], ARRAYV[3]);
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[4], ARRAYV[4]);
	    m2.insert(ARRAY[2], ARRAYV[5]);
	    m2.insert(ARRAY[5], ARRAYV[5]);
	    m2.insert(ARRAY[3], ARRAYV[3]);
	    Map m3;
	    subtract(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 2));
			} break; case 96: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[1], ARRAYV[1]);
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    Map m3;
	    m3.insert(ARRAY[3], ARRAYV[3]);
	    m3.insert(ARRAY[4], ARRAYV[4]);
	    subtract(m, m2, m3);
	    assert(isPermutation(m3, ARRAY, ARRAYV, 1));
			} break; case 97: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[1], ARRAYV[1]);
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    subtract(m, m2, m);
	    assert(isPermutation(m, ARRAY, ARRAYV, 1));
			} break; case 98: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    Map m2;
	    m2.insert(ARRAY[1], ARRAYV[1]);
	    m2.insert(ARRAY[2], ARRAYV[2]);
	    subtract(m, m2, m2);
	    assert(isPermutation(m2, ARRAY, ARRAYV, 1));
			} break; case 99: {
	    const int NITEMS = 2000;
	    for (int k = 0; k < NITEMS; k++)
		assert(m.insert(OurType(k), SOMEVALUE));
	    assert(m.size() == NITEMS);
			}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}
