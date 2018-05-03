// testMyHash.cpp

#include "MyHash.h"
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <streambuf>
#include <cstdlib>
#include <cassert>

using namespace std;

class Integer
{
  public:
    Integer(int i = 0) : val(i) {}
    operator int() const { return val; }
  private:
    int val;
};

#define DEFINEHASH(f) \
	unsigned int f(const Integer& i) { return std::hash<int>()(i); }

DEFINEHASH(hash)
DEFINEHASH(hash1)
DEFINEHASH(hashGet)
DEFINEHASH(hashWrapper)
DEFINEHASH(hash_)
DEFINEHASH(hashd)
DEFINEHASH(hasher)
DEFINEHASH(hashing)
DEFINEHASH(hashit)
DEFINEHASH(m_hash)
DEFINEHASH(mhash)
DEFINEHASH(myHash)
DEFINEHASH(stuhash)
DEFINEHASH(xhash)

using MH = MyHash<Integer, int>;

unordered_set<void*> addrs;
bool recordaddrs = false;

void* operator new(size_t n)
{
	void* p = malloc(n);
	if (recordaddrs)
	{
		recordaddrs = false;
		addrs.insert(p);
		recordaddrs = true;
	}
	return p;
}

void operator delete(void* p) noexcept // remove "noexcept" for older compilers
{
	if (recordaddrs)
	{
		recordaddrs = false;
		unordered_set<void*>::iterator it = addrs.find(p);
		if (it != addrs.end())
			addrs.erase(it);
		recordaddrs = true;
	}
	free(p);
}

bool isNear(double x, double y)
{
	return abs(x - y) < 1e-5;
}

void testMyHash(int n)
{
    union AlignedStorage
    {
	double alignment;
	char bytes[sizeof(MH)];
    };

    AlignedStorage storage;
    fill_n(storage.bytes, sizeof(MH), 0);
    MH& m = reinterpret_cast<MH&>(storage.bytes);
    new (storage.bytes) MH;
    Integer dummy = -999;
    int v = 666;

    switch (n)
    {
			 default: {
	cout << "Bad argument" << endl;
		} break; case  1: {
	// test if no crash from destructor of empty MyHash
		} break; case  2: {
	// test if no crash from destructor of empty MyHash
	{
		AlignedStorage storage2;
		fill_n(storage2.bytes, sizeof(MH), '\xAB');
		new (storage2.bytes) MH;
		MH& m2 = reinterpret_cast<MH&>(storage2.bytes);
		m2.MH::~MH();
	}
		} break; case  3: {
	// test if no crash from reset of empty MyHash
	m.reset();
		} break; case  4: {
	// test if no crash from reset of empty MyHash
	{
		AlignedStorage storage2;
		fill_n(storage2.bytes, sizeof(MH), '\xAB');
		new (storage2.bytes) MH;
		MH& m2 = reinterpret_cast<MH&>(storage2.bytes);
		m2.reset();
		m2.MH::~MH();
	}
		} break; case  5: {
	assert(m.getNumItems() == 0);
		} break; case  6: {
	assert(m.getLoadFactor() == 0);
		} break; case  7: {
	assert(m.find(0) == nullptr);
		} break; case  8: {
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	assert(m.getNumItems() == 3);
		} break; case  9: {
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	assert(isNear(m.getLoadFactor(), 3.0/100));
		} break; case 10: {
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	int* p;
	for (int i : { 68, 29, 42 })
	{
		p = m.find(i);
		assert(p != nullptr  &&  *p == -i);
	}
	for (int i : { 0, -42 })
		assert(m.find(i) == nullptr);
		} break; case 11: {
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	m.associate(68, -10068);
	m.associate(42, -10042);
	m.associate(29, -10029);
	assert(m.getNumItems() == 3);
		} break; case 12: {
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	m.associate(68, -10068);
	m.associate(42, -10042);
	m.associate(29, -10029);
	int* p;
	for (int i : { 68, 29, 42 })
	{
		p = m.find(i);
		assert(p != nullptr  &&  *p == -10000-i);
	}
		} break; case 13: {
	int x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, -x);
		x += 1789;
	}
	assert(m.getNumItems() == 1000);
	int* p;
	x = 1642 + 1000 * 1789;
	for (int k = 0; k < 1000; k++)
	{
		x -= 1789;
		p = m.find(x);
		assert(p != nullptr  &&  *p == -x);
	}
	for (x = 1642+1; x < 1642+1789; x++)
		assert(m.find(x) == nullptr);
		} break; case 14: {
	int x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, -x);
		x += 1789;
	}
	double lf = m.getLoadFactor();
	assert(lf >= 0.5/2  &&  lf <= 0.5);
		} break; case 15: {
	int x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, -x);
		x += 1789;
	}
	assert(isNear(m.getLoadFactor(), 1000.0/3200));
		} break; case 16: {
	int x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, -x);
		x += 1789;
	}
	assert(m.getNumItems() == 1000);
	m.reset();
	assert(m.getNumItems() == 0);
	assert(m.getLoadFactor() == 0);
	x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		assert(m.find(x) == nullptr);
		x += 1789;
	}
		} break; case 17: {
	int x = 1642;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, -x);
		x += 1789;
	}
	m.reset();
	m.associate(42, -42);
	m.associate(68, -68);
	m.associate(29, -29);
	assert(isNear(m.getLoadFactor(), 3.0/100));
		} break; case 18: {
	MH m2(1.5);
	int x = 1642;
	for (int k = 0; k < 149; k++)
	{
		m2.associate(x, -x);
		x += 1789;
	}
	assert(isNear(m2.getLoadFactor(), 149.0/100));
	for (int k = 149; k < 151; k++)
	{
		m2.associate(x, -x);
		x += 1789;
	}
	assert(isNear(m2.getLoadFactor(), 151.0/200));
		} break; case 19: {
	MH m2(2.5);
	int x = 1642;
	for (int k = 0; k < 199; k++)
	{
		m2.associate(x, -x);
		x += 1789;
	}
	assert(isNear(m2.getLoadFactor(), 199.0/100));
	for (int k = 199; k < 201; k++)
	{
		m2.associate(x, -x);
		x += 1789;
	}
	assert(isNear(m2.getLoadFactor(), 201.0/200));
		} break; case 20: {
	int n = addrs.size();
	recordaddrs = true;
	{
		MH m2;
		m2.associate(42, -42);
		assert(addrs.size() > n);
	}
	recordaddrs = false;
	assert(addrs.size() == n);
		} break; case 21: {
	int n = addrs.size();
	recordaddrs = true;
	{
		MH m2;
		m2.associate(42, -42);
		m2.reset();
	}
	recordaddrs = false;
	assert(addrs.size() == n);
		} break; case 22: {
	int n = addrs.size();
	recordaddrs = true;
	{
		MH m2;
		int x = 1642;
		for (int k = 0; k < 199; k++)
		{
			m2.associate(x, -x);
			x += 1789;
		}
		assert(addrs.size() > n);
	}
	recordaddrs = false;
	assert(addrs.size() == n);
		}
    }
    m.MH::~MH();
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testMyHash(n);
	cout << "Passed" << endl;
}
