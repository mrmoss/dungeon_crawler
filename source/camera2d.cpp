//camera2d.cpp
//Created By:  Mike Moss
//Description:  Camera2D source.
//Date:  2011

//Definitions for "camera2d.h"
#include "camera2d.h"

//Camera2D Class Constructor(Default and 2 argument version)
Camera2D::Camera2D(const double x,const double y):_x(x),_y(y),_rot(0.0)
{}

//Camera2D Class Member Position X Mutator
void Camera2D::setX(const double x)
{
    _x=x;
}

//Camera2D Class Member Position Y Mutator
void Camera2D::setY(const double y)
{
    _y=y;
}

//Camera2D Class Member Position X Add Mutator
void Camera2D::addX(const double add)
{
    _x+=add;
}

//Camera2D Class Member Position Y Add Mutator
void Camera2D::addY(const double add)
{
    _y+=add;
}

//Camera2D Class Member Position X Accessor
double Camera2D::X() const
{
    return _x;
}

//Camera2D Class Member Position Y Accessor
double Camera2D::Y() const
{
    return _y;
}

//Camera2D Class Member Rotation Mutator
void Camera2D::setR(const double rot)
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

//Camera2D Class Member Rotation Add Mutator
void Camera2D::addR(const double add)
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

//Camera2D Class Member Rotation Accessor
double Camera2D::R() const
{
    return _rot;
}
