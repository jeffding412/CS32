#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList m_word_list;
    Translator m_translator;
    string chooseWord(vector<string> words);
    bool checkValid(string possiblePhrase);
    bool stillIncomplete(string possiblePhrase);
};

bool DecrypterImpl::stillIncomplete(string possiblePhrase)
{
    for (int i = 0; i < possiblePhrase.size(); i++) {
        if (possiblePhrase[i] == '?') {
            return true;
        }
    }
    return false;
}

string DecrypterImpl::chooseWord(vector<string> words)
{
    //vector that holds translations of the words
    vector<string> translatedWords;
    for (int i = 0; i < words.size(); i++) {
        translatedWords.push_back(m_translator.getTranslation(words[i]));
    }
    
    vector<int> numUnknown;
    
    //counts how many unknown letters are in each word
    for (int i = 0; i < translatedWords.size(); i++) {
        int count = 0;
        for (int x = 0; x < translatedWords[i].size(); x++) {
            if (translatedWords[i][x] == '?') {
                count++;
            }
        }
        numUnknown.push_back(count);
    }
    
    //int that holds which index has the most unknown letters
    int desiredIndex = 0;
    for (int i = 1; i < words.size(); i++) {
        if (numUnknown[desiredIndex] < numUnknown[i]) {
            desiredIndex = i;
        }
    }
    
    //returns word with the most unknown letters
    return words[desiredIndex];
}

bool DecrypterImpl::checkValid(string possiblePhrase)
{
    Tokenizer t(" ,.!");
    vector<string> translatedWords = t.tokenize(possiblePhrase);
    
    bool noQuestions;
    for (int i = 0; i < translatedWords.size(); i++) {
        noQuestions = true;
        for (int x = 0; x < translatedWords[i].size(); x++) {
            if (translatedWords[i][x] == '?') {
                noQuestions = false;
                break;
            }
        }
        if (noQuestions && !m_word_list.contains(translatedWords[i])) {
            return false;
        }
    }
    
    return true;
}

bool DecrypterImpl::load(string filename)
{
    return m_word_list.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string> possibleMessages;
    Tokenizer t(" ,.!");
    vector<string> ciphertextFragments = t.tokenize(ciphertext);
    
    string mostUnknownCipherFragement = chooseWord(ciphertextFragments);
    string partialTranslation = m_translator.getTranslation(mostUnknownCipherFragement);
    
    vector<string> possibleMatches = m_word_list.findCandidates(mostUnknownCipherFragement, partialTranslation);
    
    if (possibleMatches.size() == 0) {
        m_translator.popMapping();
        return possibleMatches;
    }
    
    string possiblePhrase;
    for (int i = 0; i < possibleMatches.size(); i++) {
        if (!m_translator.pushMapping(mostUnknownCipherFragement, possibleMatches[i])) {
            continue;
        }
//        cerr << mostUnknownCipherFragement << endl;
//        cerr << possibleMatches[i] << endl;
        
        possiblePhrase = m_translator.getTranslation(ciphertext);
        
//        cerr << possiblePhrase << endl;
        if (!checkValid(possiblePhrase)) {
            m_translator.popMapping();
            continue;
        }
        if (stillIncomplete(possiblePhrase)) {
            possibleMessages = crack(ciphertext);
        }
        else {
            possibleMessages.push_back(possiblePhrase);
            m_translator.popMapping();
        }
    }
    
    return possibleMessages;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
