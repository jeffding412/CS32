#include <queue>
#include <string>

using namespace std;

const char WALL = 'X';
const char OPEN = '.';
const char SEEN = 'o';

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

void explore(string maze[], stack<Coord>& toDo, int r, int c)
{
        if (maze[r][c] == OPEN)
        {
             toDo.push(Coord(r,c));
             maze[r][c] = SEEN;  // anything non-OPEN will do
        }
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr < 0  ||  sr > nRows  ||  sc < 0  || sc > nCols  ||
        er < 0  ||  er > nRows  ||  ec < 0  || ec > nCols  ||
        maze[sr][sc] != OPEN  ||  maze[er][ec] != OPEN)
       return false;

    queue<Coord> toDo;
    explore(maze, toDo, sr, sc);

    while ( ! toDo.empty() )
    {
        Coord curr = toDo.front();
        toDo.pop();

        const int cr = curr.r();
        const int cc = curr.c();

        if (cr == er  &&  cc == ec)
            return true;

        explore(maze, toDo, cr, cc+1);  // east
        explore(maze, toDo, cr+1, cc);  // south
        explore(maze, toDo, cr, cc-1);  // west
        explore(maze, toDo, cr-1, cc);  // north
    }
    return false;
}
