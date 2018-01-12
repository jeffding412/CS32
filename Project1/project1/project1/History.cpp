//
//  History.cpp
//  project1
//
//  Created by Jeffrey Ding on 1/11/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "History.h"

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


