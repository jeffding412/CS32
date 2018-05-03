// testTokenizer.cpp

#include "MyHash.h"
#include "provided.h"
#include <vector>
#include <string>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <streambuf>
#include <cstdlib>
#include <cassert>

using namespace std;

#define DEFINEHASH(f) \
	unsigned int f(const char& i) { return std::hash<char>()(i); }

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

bool matches(const vector<string>& v, const initializer_list<string>& expected)
{
	return v.size() == expected.size()  &&  equal(v.begin(), v.end(), expected.begin());
}

bool matches(const Tokenizer& t, const string& s, const initializer_list<string>& expected)
{
	return matches(t.tokenize(s), expected);
}

void testTokenizer(int n)
{
    switch (n)
    {
			 default: {
	cout << "Bad argument" << endl;
		} break; case  1: {
	Tokenizer t(" ,.!");
	assert(matches(t, "secret", { "secret" }));
		} break; case  2: {
	Tokenizer t(" ,.!");
	assert(matches(t, "!!, .secret", { "secret" }));
		} break; case  3: {
	Tokenizer t(" ,.!");
	assert(matches(t, "secret,. ,,", { "secret" }));
		} break; case  4: {
	Tokenizer t(" ,.!");
	assert(matches(t, ",!SECRET!,", { "SECRET" }));
		} break; case  5: {
	Tokenizer t(",.!");
	assert(matches(t, ",!sec  ret!,", { "sec  ret" }));
		} break; case  6: {
	Tokenizer t(" ");
	assert(matches(t, "secret message ", { "secret", "message" }));
		} break; case  7: {
	Tokenizer t(" 0123456789");
	assert(matches(t, "42 secret 999 message 86", { "secret", "message" }));
		} break; case  8: {
	Tokenizer t(" ,.!-");
	assert(matches(t, "Don't, I say don't, be a half-wit!",
			{ "Don't", "I", "say", "don't", "be", "a", "half", "wit" }));
		} break; case  9: {
	Tokenizer t(" ,.!");
	assert(matches(t, " !!.,.,! !..!", { }));
		} break; case 10: {
	Tokenizer t(" ,.!");
	assert(matches(t, "abc ~`@#$%^&*()_+= abc ", { "abc", "~`@#$%^&*()_+=", "abc" }));
		} break; case 11: {
	Tokenizer t(" ~`@#$%^&*()_+=");
	assert(matches(t, "abc ~`@#$%^&*()_+= abc ", { "abc", "abc" }));
		} break; case 12: {
	Tokenizer t(" ,.!");
	assert(matches(t, "", { }));
		} break; case 13: {
	Tokenizer t(" !!!! !!  !!  ! ! !");
	assert(matches(t, "secret ! !!   message", { "secret",  "message" }));
		} break; case 14: {
	Tokenizer t("");
	assert(matches(t, " secret message ", { " secret message " }));
		} break; case 15: {
	Tokenizer t("x");
	assert(matches(t, "abcxdefxghix", { "abc", "def", "ghi" }));
		}
    }
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testTokenizer(n);
	cout << "Passed" << endl;
}
