//object.cpp
//Created By:  Mike Moss
//Description:  Object source.
//Date:  2011

//Definitions for "object.h"
#include "object.h"

//Object Class Constructor(Default and 2 argument version)
Object::Object(const double x,const double y):_x(gridize(x)*gridSize()),
    _y(gridize(y)*gridSize()),_rot(0.0),_scaleX(1.0),_scaleY(1.0)
{}

//Object Class Member Position X Mutator
void Object::setX(const double x)
{
    _x=x;
}

//Object Class Member Position Y Mutator
void Object::setY(const double y)
{
    _y=y;
}

//Object Class Member Position X Add Mutator
void Object::addX(const double add)
{
    _x+=add;
}

//Object Class Member Position X Add Mutator
void Object::addY(const double add)
{
    _y+=add;
}

//Object Class Member Position X Accessor
double Object::X() const
{
    return _x;
}

//Object Class Member Position Y Accessor
double Object::Y() const
{
    return _y;
}

//Object Class Member Rotation Mutator
void Object::setR(const double rot)
{
    _rot=rot;

    while(_rot<0.0)
    {
        _rot+=360.0;
    }

    while(_rot>=360.0)
    {
        _rot-=360.0;
    }
}

//Object Class Member Rotation Add Mutator
void Object::addR(const double add)
{
    _rot+=add;

    while(_rot<0.0)
    {
        _rot+=360.0;
    }

    while(_rot>=360.0)
    {
        _rot-=360.0;
    }
}

//Object Class Member Rotation Accessor
double Object::R() const
{
    return _rot;
}

//Object Class Member Scale X Mutator
void Object::setScaleX(const double scaleX)
{
    _scaleX=scaleX;
}

//Object Class Member Scale Y Mutator
void Object::setScaleY(const double scaleY)
{
    _scaleY=scaleY;
}

//Object Class Member Scale X Accessor
double Object::getScaleX() const
{
    return _scaleX;
}

//Object Class Member Scale Y Accessor
double Object::getScaleY() const
{
    return _scaleY;
}

//Object Class Member Grid Size Accessor
int Object::gridSize() const
{
    return 16;
}

//Object Class Member Convert to Grid(Converts a coordinate to a grid coordinate)
int Object::gridize(const double num)
{
    return static_cast<int>(num/gridSize());
}
