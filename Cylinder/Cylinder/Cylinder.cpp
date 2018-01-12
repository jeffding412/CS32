//
//  Cylinder.cpp
//  Cylinder
//
//  Created by Jeffrey Ding on 1/12/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

class Cylinder
{
public:
    double getVolume()
    {
        const double pi = 3.1415926535;
        double vol = pi * radius * radius * height;
        return vol;
    }
    
    void Initialize(int r, int h)
    {
        radius = r;
        height = h;
    }
    
private:
    int radius;
    int height;
};
