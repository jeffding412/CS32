#include "provided.h"
#include <string>
#include <map>
#include <cctype>
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
    
    string protoCipher = "";
    string protoPlain = "";
    
    bool repeat = false;
    for (int i = 0; i < ciphertext.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (ciphertext[i] == ciphertext[j]) {
                if (plaintext[i] == plaintext[j]) {
                    repeat = true;
                }
            }
        }
        if (!repeat) {
            protoCipher += ciphertext[i];
            protoPlain += plaintext[i];
        }
        repeat = false;
    }
    
    //iterate through each letter in both parameters
    for (int i = 0; i < protoCipher.size(); i++) {
        if (!isalpha(protoCipher[i]) || !isalpha(protoPlain[i])) {
            return false;
        }
        //if a letter is repeated in both, return false
        for (int j = 0; j < i; j++) {
            if (protoCipher[i] == protoCipher[j] || protoPlain[i] == protoPlain[j]) {
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
        for (int i = 0; i < protoCipher.size(); i++) {
            if (it->first == protoCipher[i] || it->second == protoPlain[i]) {
                return false;
            }
        }
    }
    
    //copy currentMap into a newMap (don't want to modify currentMap)
    map<char, char> newMap(currentMap);
    for (int i = 0; i < protoCipher.size(); i++) {
        newMap[protoCipher[i]] = protoPlain[i];
    }
    
    m_stack.push_back(newMap);
    
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_stack.empty()) {
        return false;
    }
    
    m_stack.pop_back();
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string localCipherText = ciphertext;
    string translatedString = "";
    
    //store which indices were uppercase
    bool upperCaseIndex[localCipherText.size()];
    for (int i = 0; i < localCipherText.size(); i++) {
        if (isupper(localCipherText[i])) {
            upperCaseIndex[i] = true;
        }
        else {
            upperCaseIndex[i] = false;
        }
    }
    
    //changes localCipherText to lowercase
    transform(localCipherText.begin(), localCipherText.end(), localCipherText.begin(), ::tolower);
    
    map<char, char> currentMap;
    map<char, char>::iterator it;
    //if there is something in the vector, set currentMap to most current map
    if (m_stack.size() != 0) {
        currentMap = m_stack.back();
    }
    
    //iterate through localCipherText
    for (int i = 0; i < localCipherText.size(); i++) {
        //If the ciphertext character is not a letter, that character appears, unchanged.
        if (!isalpha(localCipherText[i])) {
            translatedString += localCipherText[i];
            continue;
        }
        //find the letter necessary
        it = currentMap.find(localCipherText[i]);
        //If the ciphertext character is a letter with an unknown translation in the current mapping, a ? appears.
        if (it == currentMap.end()) {
            translatedString += '?';
        }
        //If the ciphertext character is a letter that maps to a plaintext letter in the current mapping, then that plaintext letter appears, in the same case as in the ciphertext string.
        else {
            if (upperCaseIndex[i]) {
                translatedString += toupper(it->second);
            }
            else {
                translatedString += it->second;
            }
        }
    }
    
    return translatedString; // This compiles, but may not be correct
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
