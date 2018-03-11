//
//  Tokenizer.cpp
//  Cracked
//
//  Created by Zhengfu Ding on 3/11/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    vector<char> m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    //pushes each char separator into a vector of chars
    for (int i = 0; i < separators.size(); i++) {
        m_separators.push_back(separators[i]);
    }
}

//returns a vector of strings without the separators
vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string> tokens;      //vector of strings
    int startIndex = 0;
    int numCharsInString = 0;
    //iterate through string s
    for (int i = 0; i < s.size(); i++) {
        //iterate through the vector of chars
        for (int j = 0; j < m_separators.size(); j++) {
            //if the current character is a seperator
            if (s[i] == m_separators[j]) {
                //if the string isn't empty, push the substring into tokens
                if (numCharsInString != 0) {
                    tokens.push_back(s.substr(startIndex, numCharsInString));
                }
                startIndex = i + 1;
                numCharsInString = -1;
                break;
            }
        }
        numCharsInString++;
    }
    return tokens;  // This compiles, but may not be correct
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}

