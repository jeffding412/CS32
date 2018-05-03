// testTranslator.cpp

#include "MyHash.h"
#include "provided.h"
#include <vector>
#include <string>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cassert>

using namespace std;

#define DEFINEHASH(f) \
	unsigned int f(const string& s);  \
	unsigned int f(const int& s);  \
	unsigned int f(const char& s);

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

void testTranslator(int n)
{
    Translator tr;

    switch (n)
    {
			 default: {
	cout << "Bad argument" << endl;
		} break; case  1: {
	assert(tr.getTranslation("abc") == "???");
		} break; case  2: {
	assert(tr.getTranslation("ABC") == "???");
		} break; case  3: {
	assert(tr.getTranslation("3'+") == "3'+");
		} break; case  4: {
	assert(!tr.pushMapping("abc", "defg"));
		} break; case  5: {
	tr.pushMapping("abc", "defg");
	assert(tr.getTranslation("bab") == "???");
		} break; case  6: {
	assert(!tr.pushMapping("abc", "de'"));
	assert(tr.getTranslation("bab") == "???");
		} break; case  7: {
	assert(!tr.pushMapping("ab'", "def"));
	assert(tr.getTranslation("bab") == "???");
		} break; case  8: {
	assert(!tr.pushMapping("aba", "def"));
	assert(tr.getTranslation("bab") == "???");
		} break; case  9: {
	assert(!tr.pushMapping("abc", "ded"));
	assert(tr.getTranslation("bab") == "???");
		} break; case 10: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("bab") == "ede");
		} break; case 11: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("baby#") == "ede?#");
		} break; case 12: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("bAB") == "eDE");
		} break; case 13: {
	assert(tr.pushMapping("aBC", "DeF"));
	assert(tr.getTranslation("aAbBcC") == "dDeEfF");
		} break; case 14: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("bab") == "ede");
	assert(tr.pushMapping("gab", "xde"));
	assert(tr.getTranslation("bagc") == "edxf");
		} break; case 15: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("bab") == "ede");
	assert(tr.pushMapping("ghi", "jkl"));
	assert(tr.getTranslation("big") == "elj");
		} break; case 16: {
	assert(tr.pushMapping("abc", "def"));
	assert(!tr.pushMapping("gha", "jkl"));
		} break; case 17: {
	assert(tr.pushMapping("abc", "def"));
	assert(!tr.pushMapping("ghi", "jkd"));
		} break; case 18: {
	assert(!tr.popMapping());
	assert(tr.getTranslation("abc") == "???");
		} break; case 19: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("bab") == "ede");
	assert(tr.popMapping());
	assert(tr.getTranslation("bab") == "???");
		} break; case 20: {
	assert(tr.pushMapping("abc", "def"));
	assert(tr.popMapping());
	assert(!tr.popMapping());
		} break; case 21: {
	assert(tr.getTranslation("baby pig") == "???? ???");
	assert(tr.pushMapping("abc", "def"));
	assert(tr.getTranslation("baby pig") == "ede? ???");
	assert(tr.pushMapping("ghi", "jkl"));
	assert(tr.getTranslation("baby pig") == "ede? ?lj");
	assert(tr.popMapping());
	assert(tr.getTranslation("baby pig") == "ede? ???");
	assert(tr.popMapping());
	assert(tr.getTranslation("baby pig") == "???? ???");
		}
    }
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testTranslator(n);
	cout << "Passed" << endl;
}
