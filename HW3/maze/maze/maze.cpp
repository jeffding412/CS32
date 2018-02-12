//
//  maze.cpp
//  maze
//
//  Created by Jeffrey Ding on 2/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec) {   //If the start location is equal to the ending location, then we've solved the maze, so return true.
        return true;
    }
    maze[sr][sc] = 'X';          //Mark the start location as visted.
    
    //For each of the four directions
    if (maze[sr][sc+1] == '.') {                                    //If the location one step East (from the start location) is unvisited,
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) {     //then call pathExists starting from that location (and ending at the same ending location as in the current call). If that returned true, then return true.
            return true;
        }
    }
    if (maze[sr+1][sc] == '.') {                                    //If the location one step South (from the start location) is
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec)) {     //then call pathExists starting from that location (and ending at the same ending location as in the current call). If that returned true, then return true.
            return true;
        }
    }
    if (maze[sr][sc-1] == '.') {                                    //If the location one step West (from the start location) is
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec)) {     //then call pathExists starting from that location (and ending at the same ending location as in the current call). If that returned true, then return true.
            return true;
        }
    }
    if (maze[sr-1][sc] == '.') {                                    //If the location one step North (from the start location) is
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) {     //then call pathExists starting from that location (and ending at the same ending location as in the current call). If that returned true, then return true.
            return true;
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
