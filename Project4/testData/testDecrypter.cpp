// testDecrypter.cpp

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
#include <unistd.h>

using namespace std;

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

void load(Decrypter& d, const string& words)
{
	d.load(prepfile(words));
}

bool matchesUnsorted(vector<string>& v, const initializer_list<string>& expected)
{
	if (v.size() != expected.size())
		return false;
	sort(v.begin(), v.end());
	return equal(v.begin(), v.end(), expected.begin());
}

bool matches(vector<string>& v, const initializer_list<string>& expected)
{
	if (v.size() != expected.size())
		return false;
	sort(v.begin(), v.end());
	return equal(v.begin(), v.end(), expected.begin());
}

void testDecrypter(int n)
{
    Decrypter d;

    switch (n)
    {
			 default: {
	cout << "Bad argument" << endl;
		} break; case  1: {
	assert(!d.load("/this/is/a/nonexistent/file"));
	assert(d.load(prepfile("hello")));
		} break; case  2: {
	load(d, "");
	assert(d.crack("abc").empty());
	load(d, "cat");
	assert(!d.crack("abc").empty());
		} break; case  3: {
	load(d, "cat");
	auto v = d.crack("abc");
	assert(matches(v, { "cat" }));
		} break; case  4: {
	load(d, "cat");
	auto v = d.crack("abc abc");
	assert(matches(v, { "cat cat" }));
		} break; case  5: {
	load(d, "cat");
	auto v = d.crack("abc ABC");
	assert(matches(v, { "cat CAT" }));
		} break; case  6: {
	load(d, "cat");
	auto v = d.crack("[({abc})]-;:,.abc!#$%^&\"9876543210");
	assert(matches(v, { "[({cat})]-;:,.cat!#$%^&\"9876543210" }));
		} break; case  7: {
	load(d, "can/dogs/bark");
	auto v = d.crack("fish can talk");
	assert(matches(v, { "dogs can bark" }));
		} break; case  8: {
	load(d, "don't/cats/dogs/bark");
	auto v = d.crack("fish net's bird");
	assert(matches(v, { "cats don't bark" }));
		} break; case  9: {
	load(d, "cat/rat/dog/bat/pig/cow/elk/gnu/yak/fly/ant/owl");
	auto v = d.crack("xyz");
	assert(matchesUnsorted(v, { "ant", "bat", "cat", "cow", "dog", "elk",
				"fly", "gnu", "owl", "pig", "rat", "yak" }));
		} break; case 10: {
	load(d, "cat/rat/dog/bat/pig/cow/elk/gnu/yak/fly/ant/owl");
	auto v = d.crack("xyz");
	assert(matches(v, { "ant", "bat", "cat", "cow", "dog", "elk",
				"fly", "gnu", "owl", "pig", "rat", "yak" }));
		} break; case 11: {
	load(d, "people/aerate/ether/essay/eater/excel/Expel/ablate/purple");
	auto v = d.crack("SMXSDG sgosdg gfvgx!");
	assert(matchesUnsorted(v, { "ABLATE aerate excel!", "ABLATE aerate expel!",
			"PURPLE people eater!", "PURPLE people ether!" }));
		} break; case 12: {
	load(d, "people/aerate/ether/essay/eater/excel/Expel/ablate/purple");
	auto v = d.crack("SMXSDG sgosdg gfvgx!");
	assert(matchesUnsorted(v, { "ABLATE aerate excel!", "ABLATE aerate expel!",
			"PURPLE people eater!", "PURPLE people ether!" }));
		} break; case 13: {
	load(d, "people/aerate/ether/essay/eater/excel/Expel/ablate/purple");
	assert(d.crack("SMXSDG sgosdg gfvgy!").empty());
	load(d, "cat");
	assert(!d.crack("abc").empty());
		} break; case 14: {
	if ( !d.load("wordlist.txt"))
	{
		cerr << "Cannot open wordlist.txt" << endl;
		exit(1);
	}
	auto v = d.crack("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; "
			"hjg ozgcy tc moox bo moya wg grc vmobck koon grwg "
			"tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. "
			"-Rcmcy Xcmmcn");
	assert(matches(v, { "When one door of happiness closes, another "
			"opens; but often we look so long at the closed door "
			"that we do not see the one which has been opened for "
			"us. -Helen Keller" }));
		} break; case 15: {
	if ( !d.load("wordlist.txt"))
	{
		cerr << "Cannot open wordlist.txt" << endl;
		exit(1);
	}
	auto v = d.crack("Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe "
			"dq jzw jzkpta jzrj qcn ekep'j ec jzrp dq jzw cpwa "
			"qcn eke ec. -Urls Jxrkp");
	assert(matches(v, { "Twenty years frog now you will me gore "
			"disappointed my the thinks that you didn't do than "
			"my the ones you did do. -Garb Twain",
			"Twenty years from now you will be more disappointed "
			"by the things that you didn't do than by the ones "
			"you did do. -Marc Twain",
			"Twenty years from now you will be more disappointed "
			"by the things that you didn't do than by the ones "
			"you did do. -Mark Twain",
			"Twenty years from now you will be more disappointed "
			"by the things that you didn't do than by the ones "
			"you did do. -Marx Twain",
			"Twenty years from now you will be more disappointed "
			"by the thinks that you didn't do than by the ones "
			"you did do. -Marc Twain",
			"Twenty years from now you will be more disappointed "
			"by the thinks that you didn't do than by the ones "
			"you did do. -Marx Twain" }));
		} break; case 16: {
	if ( !d.load("wordlist.txt"))
	{
		cerr << "Cannot open wordlist.txt" << endl;
		exit(1);
	}
	auto v = d.crack("Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq "
			"svquxiy. -Lzjk Nqkkqcy");
	assert(matches(v, { "Those who dare to fail miserably can achieve "
			"greatly. -John Kennedy",
			"Those who dare to pail miserably can achieve "
			"greatly. -John Kennedy" }));
		}
    }
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testDecrypter(n);
	cout << "Passed" << endl;
}
