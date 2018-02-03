//
//  mazequeue.cpp
//  mazequeue
//
//  Created by Jeffrey Ding on 2/1/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

//Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

//Represents an (r,c) coordinate pair
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;        //Create a Coord queue
    coordQueue.push(Coord(sr, sc)); //Push the starting coordinate (sr,sc) into the coordinate queue
    maze[sr][sc] = 'X';             //update maze[sr][sc] to indicate that the algorithm has encountered it
    
    //While the stack is not empty
    while (!coordQueue.empty()) {
        Coord temp = coordQueue.front();  //Pop the front coordinate off the queue. This gives you the current (r,c) location that your algorithm is exploring.
        coordQueue.pop();
        
        //If the current (r,c) coordinate is equal to the ending coordinate, then we've solved the maze so return true!
        if (temp.r() == er && temp.c() == ec) {
            return true;
        }
        
        //Check each place you can move from the current cell as follows:
        if (maze[temp.r()][temp.c()+1] == '.') {            //If you can move EAST and haven't encountered that cell yet,
            coordQueue.push(Coord(temp.r(), temp.c()+1));   //then push the coordinate (r,c+1) into the queue
            maze[temp.r()][temp.c()+1] = 'X';               //update maze[r][c+1] to indicate the algorithm has encountered it.
        }
        if (maze[temp.r()+1][temp.c()] == '.') {            //If you can move SOUTH and haven't encountered that cell yet,
            coordQueue.push(Coord(temp.r()+1, temp.c()));   //then push the coordinate (r+1,c) into the queue and update
            maze[temp.r()+1][temp.c()] = 'X';               //maze[r+1][c] to indicate the algorithm has encountered it.
        }
        if (maze[temp.r()][temp.c()-1] == '.') {            //If you can move WEST and haven't encountered that cell yet,
            coordQueue.push(Coord(temp.r(), temp.c()-1));   //then push the coordinate (r,c-1) into the queue and update
            maze[temp.r()][temp.c()-1] = 'X';               //maze[r][c-1] to indicate the algorithm has encountered it.
        }
        if (maze[temp.r()-1][temp.c()] == '.') {            //If you can move NORTH and haven't encountered that cell yet,
            coordQueue.push(Coord(temp.r()-1, temp.c()));   //then push the coordinate (r-1,c) into the queue and update
            maze[temp.r()-1][temp.c()] = 'X';               //maze[r-1][c] to indicate the algorithm has encountered it.
        }
    }
    
    return false;   //there was no solution, so return false
}
