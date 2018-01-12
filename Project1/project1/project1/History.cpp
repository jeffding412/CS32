//
//  History.cpp
//  project1
//
//  Created by Jeffrey Ding on 1/11/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            historyGrid[row][col] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r < 1 || c < 1 || r >= MAXROWS || c >= MAXCOLS) {
        return false;
    }
    
    historyGrid[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            if (historyGrid[row][col] == 0) {
                cout << '.';
            }
            else if (historyGrid[row][col] > 25) {
                cout << 'Z';
            }
            else {
                cout << char(historyGrid[row][col] + 64);
            }
        }
        cout << endl;
    }
    cout << endl;
}
