For this homework, we graded mazestack.cpp, mazequeue.cpp, and eval.cpp.

We ran your pathExists function from mazestack.cpp on four mazes, and the version from mazequeue.cpp on the same four mazes. Each of the eight tests was worth 4 points. Here are the mazes:

string maze1[10] = {
"XXXXXXXXXX'",
"X.X..X...X'",
"X.XX.X.XXX'",
"X....X.X.X'",
"XX.X.X...X'",
"XXX..X.X.X'",
"X...X...XX'",
"X.XX..X.XX'",
"X....X...X'",
"XXXXXXXXXX'",
};

string maze2[10] = {
"XXXXXXXXXX'",
"X.X..X...X'",
"XXXX.X.XXX'",
"X....X.X.X'",
"XX.X.X...X'",
"XXX..X.X.X'",
"X...X...XX'",
"X.XX..X.XX'",
"X....X...X'",
"XXXXXXXXXX'",
};

string maze3[10] = {
"XXXXXXXXXX'",
"XX.....XXX'",
"X..XX....X'",
"X...X...XX'",
"X.X.XXX..X'",
"XXXX..X..X'",
"XX....X..X'",
"X.......XX'",
"X..XXXXXXX'",
"XXXXXXXXXX'",
};

string maze4[10] = {
"XXXXXXXXXX'",
"XX.....XXX'",
"X..XX....X'",
"X...X...XX'",
"X.X.XXX..X'",
"XXXX..X..X'",
"XX....X..X'",
"X.X.....XX'",
"X..XXXXXXX'",
"XXXXXXXXXX'",
};

assert(pathExists(maze1, 10, 10, 8, 6, 1, 1));
assert(!pathExists(maze2, 10, 0, 8, 6, 1, 1));
assert(pathExists(maze3, 10, 10, 4, 3, 7, 1));
assert(!pathExists(maze4, 10, 10, 4, 3, 7, 1));
We tried your evaluate function from eval.cpp on 20 cases. The map we tested with mapped t to 3, v to 5, w to 2, and x to -25.

points    infix    evaluate
returns    postfix    result
4    w    0    w    2
4    w+w    0    ww+    4
4    w - v    0    wv-    -3
4    w*t+v    0    wt*v+    11
4    w+t*v    0    wtv*+    17
4    w*(t+v)    0    wtv+*    16
4    v-t-w    0    vt-w-    0
4    w*(x/((w)+t))+t*v    0    wxwt+/*tv*+    5
4    t/(x+v*(w+t))    3    txvwt+*+/
4    w+u+v    2    wu+v+
3    w+U+v    1
3    x//v    1
3    x(v+w)    1
3    w w    1
3     *w    1
3    w+()    1
3    (w+w    1
3    w+(w+w))    1
2    w+@+v    1
2    w+v@x+w    1          
