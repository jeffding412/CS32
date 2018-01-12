//
//  quadratic.h
//  quadratic
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#ifndef quadratic_h
#define quadratic_h

class quadratic
{
public:
    quadratic(int newA, int newB, int newC);
    ~quadratic();
    int evaluate(int x);
    
private:
    int a;
    int b;
    int c;
};

#endif /* quadratic_h */
