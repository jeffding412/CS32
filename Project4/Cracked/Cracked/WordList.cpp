//
//  WordList.cpp
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#include "provided.h"
#include "MyHash.h"
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    string createLetterPattern(string wordToChange) const;
    MyHash<string, string> m_hashTable;
};

string WordListImpl::createLetterPattern(string wordToChange) const
{
    string newLetterPattern = "";
    int currentLetter = 97;
    bool sameLetter = false;
    for (int i = 0; i < wordToChange.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (wordToChange[i] == wordToChange[j]) {
                newLetterPattern += newLetterPattern[j];
                sameLetter = true;
                break;
            }
        }
        if (!sameLetter) {
            newLetterPattern += (char) currentLetter;
            currentLetter++;
        }
        sameLetter = true;
    }
    return newLetterPattern;
}

bool WordListImpl::loadWordList(string filename)
{
    m_hashTable.reset();
    ifstream infile(filename);      // infile is a name of our choosing
    if (!infile)                    // Did opening the file fail?
    {
        return false;
    }
    string currentWord;
    bool legalWord = true;
    while (getline(infile, currentWord)) {
        if (currentWord.size() > 0) {
            // using transform() function and ::tolower in STL
            transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
            for (int i = 0; i < currentWord.size(); i++) {
                if (isalpha(currentWord[i]) || currentWord[i] == '\'') {
                    continue;
                }
                else {
                    legalWord = false;
                    break;
                }
            }
            if (legalWord) {
                m_hashTable.associate(currentWord, currentWord);
            }
            legalWord = true;
        }
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    
    if (m_hashTable.find(word) == nullptr) {
        return false;
    }
    
    return true;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> samePatternWords;
    
    if (cipherWord.size() != currTranslation.size()) {
        return samePatternWords;
    }
    
    transform(cipherWord.begin(), cipherWord.end(), cipherWord.begin(), ::tolower);
    transform(currTranslation.begin(), currTranslation.end(), currTranslation.begin(), ::tolower);
    
    for (int i = 0; i < cipherWord.size(); i++) {
        if (isalpha(cipherWord[i]) || cipherWord[i] == '\'') {
            continue;
        }
        return samePatternWords;
    }
    
    for (int i = 0; i < currTranslation.size(); i++) {
        if (isalpha(currTranslation[i]) || currTranslation[i] == '\'' || currTranslation[i] == '?') {
            continue;
        }
        return samePatternWords;
    }
    
    
    
    
    return samePatternWords;  // This compiles, but may not be correct
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}

