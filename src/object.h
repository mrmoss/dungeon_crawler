//object.h
//Created By:  Mike Moss
//Description:  Parent object system for Glut system, each object has a position, rotation, scale, etc...
//Date:  2011

#ifndef OBJECT_H
#define OBJECT_H

//Glut2D Header
#include "glut2d.h"

//Object Class Declaration
class Object
{
    public:
        //Constructor(Default and 4 argument version)
        Object(const double x=0.0,const double y=0.0);

        //Member Position Mutators
        void setX(const double x);
        void setY(const double y);
        void addX(const double add);
        void addY(const double add);

        //Member Position Accessors
        double X() const;
        double Y() const;

        //Member Rotation Mutator
        void setR(const double rot);
        void addR(const double r);

        //Member Rotation Accessor
        double R() const;

        //Member Scale Mutators
        void setScaleX(const double scaleX);
        void setScaleY(const double scaleY);

        //Member Scale Accessors
        double getScaleX() const;
        double getScaleY() const;

        //Member Grid Size Accessor
        int gridSize() const;

    protected:
        //Member Variables
        double _x;
        double _y;
        double _rot;
        double _scaleX;
        double _scaleY;

        //Member Convert to Grid(Converts a coordinate to a grid coordinate)
        int gridize(const double num);
};

#endif
