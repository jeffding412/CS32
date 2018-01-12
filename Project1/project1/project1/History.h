//
//  History.h
//  project1
//
//  Created by Jeffrey Ding on 1/11/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    int historyGrid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
