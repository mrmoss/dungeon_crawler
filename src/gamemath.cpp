//gamemath.cpp
//Created By:  Mike Moss
//Description:  Gamemath source.
//Date:  2011

//Definitions for "gamemath.h"
#include "gamemath.h"

//Distance Function
int distance(const double x1,const double y1,const double x2,const double y2)
{
    return std::abs(std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}
