// testWordList.cpp

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

char* prepfile(const string& words)
{
	static int nfiles = 0;
	static char filename[][40] = {
		"zzdatawlXXXXXX", "zzdatawlXXXXXX", "zzdatawlXXXXXX",
		"zzdatawlXXXXXX", "zzdatawlXXXXXX", "zzdatawlXXXXXX",
		"zzdatawlXXXXXX", "zzdatawlXXXXXX", "zzdatawlXXXXXX",
		"zzdatawlXXXXXX"
	};
	if (nfiles == sizeof(filename)/sizeof(filename[0]))
	{
		cerr << "Too many files" << endl;
		exit(1);
	}
	int fd = mkstemp(filename[nfiles]);
	if (nfiles == 0)
		atexit([]{ for (int k = 0; k < nfiles; k++) remove(filename[k]); });
	if (fd == -1)
	{
		cerr << "Cannot create " << filename[nfiles] << endl;
		exit(1);
	}
	close(fd);
	ofstream ofs(filename[nfiles]);
	if (!ofs)
	{
		cerr << "Cannot open " << filename[nfiles] << endl;
		exit(1);
	}
	char lastch = '\n';
	for (auto c : words)
	{
		lastch = (c == '/' ? '\n' : c);
		ofs.put(lastch);
	}
	if (lastch != '\n')
		ofs.put('\n');
	return filename[nfiles++];
}

void load(WordList& wl, const string& words)
{
	wl.loadWordList(prepfile(words));
}

bool matches(vector<string>& v, const initializer_list<string>& expected)
{
	if (v.size() != expected.size())
		return false;
	for (auto& w : v)
		transform(w.begin(), w.end(), w.begin(), [](char c) { return tolower(c); });
	sort(v.begin(), v.end());
	return equal(v.begin(), v.end(), expected.begin());
}

bool fc(const WordList& wl, string cw, string trans, const initializer_list<string>& expected)
{
	auto cands = wl.findCandidates(cw, trans);
	return matches(cands, expected);
}

void testWordList(int n)
{
    WordList wl;

    switch (n)
    {
			 default: {
	cout << "Bad argument" << endl;
		} break; case  1: {
	assert(!wl.loadWordList("/this/is/a/nonexistent/file"));
	assert(wl.loadWordList(prepfile("hello")));
		} break; case  2: {
	load(wl, "");
	assert(!wl.contains(""));
		} break; case  3: {
	load(wl, "cat/half-wit/won't/duck");
	assert(wl.contains("cat")  &&  !wl.contains("half-wit"));
		} break; case  4: {
	load(wl, "cat/half-wit/won't/duck soup");
	assert(wl.contains("cat")  &&  wl.contains("won't"));
		} break; case  5: {
	load(wl, "cat/half-wit/won't/duck soup");
	assert(wl.contains("cat")  &&  !wl.contains("duck")  &&  !wl.contains("soup"));
		} break; case  6: {
	load(wl, "cat/dog");
	assert(wl.contains("cat")  &&  wl.contains("dog")  &&
		!wl.contains("rat")  &&  !wl.contains("eel"));
	load(wl, "rat/eel");
	assert(!wl.contains("cat")  &&  !wl.contains("dog")  &&
		wl.contains("rat")  &&  wl.contains("eel"));
		} break; case  7: {
	load(wl, "cat");
	assert(wl.contains("CaT")  &&  !wl.contains("dog"));
		} break; case  8: {
	load(wl, "CaT");
	assert(wl.contains("cat")  &&  !wl.contains("dog"));
		} break; case  9: {
	load(wl, "cat/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "cat", "????", { }));
		} break; case 10: {
	load(wl, "cat/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "c@t", "???", { }));
		} break; case 11: {
	load(wl, "cat/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "ca?", "???", { }));
		} break; case 12: {
	load(wl, "cat/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "cat", "?@?", { }));
		} break; case 13: {
	load(wl, "cat/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "c't", "?a?", { }));
		} break; case 14: {
	load(wl, "cat/dog");
	assert(fc(wl, "abc", "?A?", { "cat" }));
		} break; case 15: {
	load(wl, "CAT/DOG");
	assert(fc(wl, "ABC", "?a?", { "cat" }));
		} break; case 16: {
	load(wl, "cat/i've");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "a'bc", "????", { }));
		} break; case 17: {
	load(wl, "cat/i've");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "abcd", "?'??", { }));
		} break; case 18: {
	load(wl, "cat/i've/bird");
	assert(fc(wl, "cat", "???", { "cat" }));
	assert(fc(wl, "a'bc", "?'??", { "i've" }));
		} break; case 19: {
	load(wl, "/asters/people/astern");
	assert(fc(wl, "abcdef", "??????", { "astern" }));
		} break; case 20: {
	load(wl, "/asters/people/astern");
	assert(fc(wl, "klmnol", "??????", { "asters" }));
		} break; case 21: {
	load(wl, "/asters/people/astern");
	assert(fc(wl, "rstrus", "??????", { "people" }));
		} break; case 22: {
	load(wl, "/ASTERS/PEOPLE/ASTERN");
	assert(fc(wl, "rstrus", "??????", { "people" }));
		} break; case 23: {
	load(wl, "/asters/people/astern");
	assert(fc(wl, "RSTRUS", "??????", { "people" }));
		} break; case 24: {
	load(wl, "/asters/people/astern");
	assert(fc(wl, "CABCDA", "??????", { "people" }));
	assert(fc(wl, "cabcda", "??????", { "people" }));
		} break; case 25: {
	if ( !wl.loadWordList("../Data/wordlist.txt")  &&
		!wl.loadWordList("Data/wordlist.txt"))
	{
		cerr << "Cannot open [../]Data/wordlist.txt" << endl;
		exit(1);
	}
	assert(fc(wl, "wxywzx", "??????", {
		"aerate", "asians", "balboa", "briber", "esters", "indian",
		"indign", "people", "proper", "tantra", "thatch", "triter"
		} ));
		}
    }
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testWordList(n);
	cout << "Passed" << endl;
}
