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
    MyHash<string, vector<string>> m_hashTable; //maps a string letter pattern to a vector of strings with the same letter pattern
};

//returns a letter pattern for passed in string
string WordListImpl::createLetterPattern(string wordToChange) const
{
    //empty string to store letter pattern
    string newLetterPattern = "";
    int currentLetter = 97; //sets current character to a
    bool sameLetter = false;
    //iterate through size of wordToChange
    for (int i = 0; i < wordToChange.size(); i++) {
        //iterate through previous letters
        for (int j = 0; j < i; j++) {
            //if same letter, add previous used letter into newLetterPattern
            if (wordToChange[i] == wordToChange[j]) {
                newLetterPattern += newLetterPattern[j];
                sameLetter = true;
                break;
            }
        }
        //if not previously used, add new character into newLetterPattern
        if (!sameLetter) {
            newLetterPattern += (char) currentLetter;
            currentLetter++;
        }
        sameLetter = false;
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
                //find the corresponding vector to letter pattern
                vector<string> *tempVector = m_hashTable.find(createLetterPattern(currentWord));
                if (tempVector == nullptr) {
                    //create vector of strings, push currentWord into it, and put newVector into the hash
                    vector<string> newVector;
                    newVector.push_back(currentWord);
                    m_hashTable.associate(createLetterPattern(currentWord), newVector);
                }
                else {
                    //push currentWord into the corresponding vector
                    tempVector->push_back(currentWord);
                }
            }
            legalWord = true;
        }
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    //change word to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    
    //find corresponding vector to letter pattern
    const vector<string> *tempVector = m_hashTable.find(createLetterPattern(word));
    
    if (tempVector == nullptr) {
        return false;
    }
    
    for (int i = 0; i < tempVector->size(); i++) {
        //if specific word is found, return true
        if ((*tempVector)[i] == word) {
            return true;
        }
    }
    
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    //vector of strings of candidates
    vector<string> samePatternWords;
    
    if (cipherWord.size() != currTranslation.size()) {
        return samePatternWords;
    }
    
    //transforms both parameters into lowercase
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
    
    string cipherPattern = createLetterPattern(cipherWord);
    const vector<string> *tempVector = m_hashTable.find(cipherPattern);
    
    if (tempVector != nullptr) {
        //iterate through the tempVector
        for (int i = 0; i < tempVector->size(); i++) {
            string newWord = (*tempVector)[i];
            bool match = true;
            //iterate through newWord
            for (int x = 0; x < newWord.size(); x++) {
                //if it doesn't match the currTranslation rules, set match to false
                if (currTranslation[x] != '?') {
                    if (newWord[x] != currTranslation[x]) {
                        match = false;
                    }
                }
            }
            if (match) {
                samePatternWords.push_back(newWord);
            }
            match = true;
        }
    }
    
    return samePatternWords;
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

