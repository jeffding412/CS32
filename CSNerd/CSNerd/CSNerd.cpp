//
//  CSNerd.cpp
//  CSNerd
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "CSNerd.h"
#include <iostream>
#include <string>
using namespace std;

CSNerd::CSNerd(std::string name)
{
    m_myBook = nullptr;
    m_myName = name;
}

CSNerd & CSNerd::operator = (const CSNerd &anotherCSNerd)
{
    if (this != &anotherCSNerd) {
        delete this->m_myBook;
        this->m_myBook = new Book;
        this->m_myBook->title = anotherCSNerd.m_myBook->title;
        this->m_myBook->author = anotherCSNerd.m_myBook->author;
        this->m_myName = anotherCSNerd.m_myName;
    }
    return *this;
}

void CSNerd::giveBook(std::string t, std::string a)
{
    m_myBook = new Book;
    m_myBook->title = t;
    m_myBook->author = a;
}

void CSNerd::printBook()
{
    cout << "CS Nerd: " << m_myName << endl;
    cout << "Book title: " << m_myBook->title << endl;
    cout << "Book author: " << m_myBook->author << endl;
}

CSNerd::~CSNerd()
{
    delete m_myBook;
}
