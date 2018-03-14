#include "provided.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;

class TranslatorImpl
{
public:
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    vector<map<char, char>> m_stack;    //vector (stack) holding a maps of chars to chars
};

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.size() != plaintext.size()) {
        return false;
    }
    
    //transform ciphertext and plaintext to lowercase
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::tolower);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
    
    //iterate through each letter in both parameters
    for (int i = 0; i < ciphertext.size(); i++) {
        if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i])) {
            return false;
        }
        //if a letter is repeated in both, return false
        for (int j = 0; j < i; j++) {
            if (ciphertext[i] == ciphertext[j] || plaintext[i] == plaintext[j]) {
                return false;
            }
        }
    }
    
    map<char, char> currentMap;
    map<char, char>::iterator it;
    //if there is something in the vector, set currentMap to most current map
    if (m_stack.size() != 0) {
        currentMap = m_stack.back();
    }
    
    //iterate through currentMap and check if any character gets repeated
    for (it = currentMap.begin(); it != currentMap.end(); it++) {
        for (int i = 0; i < ciphertext.size(); i++) {
            if (it->first == ciphertext[i] || it->second == plaintext[i]) {
                return false;
            }
        }
    }
    
    //copy currentMap into a newMap (don't want to modify currentMap)
    map<char, char> newMap(currentMap);
    for (int i = 0; i < ciphertext.size(); i++) {
        newMap[ciphertext[i]] = plaintext[i];
    }
    
    m_stack.push_back(newMap);
    
    return true;
}

bool TranslatorImpl::popMapping()
{
    return false;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    return ""; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
