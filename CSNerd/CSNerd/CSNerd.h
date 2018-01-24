//
//  CSNerd.h
//  CSNerd
//
//  Created by Jeffrey Ding on 1/24/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef CSNerd_h
#define CSNerd_h

#include <string>

class CSNerd
{
public:
    CSNerd(std::string name);
    CSNerd & operator = (const CSNerd &anotherCSNerd);
    void giveBook(std::string t, std::string a);
    void printBook();
    ~CSNerd();
private:
    struct Book
    {
        std::string title;
        std::string author;
    };
    
    Book *m_myBook;
    std::string m_myName;
};

#endif /* CSNerd_h */
