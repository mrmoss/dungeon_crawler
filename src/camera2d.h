//camera2d.h
//Created By:  Mike Moss
//Description:  2D camera class, mainly for use with Glut but is generic enough to work with most other systems.
//Date:  2011

#ifndef CAMERA2D_H
#define CAMERA2D_H

//Camera2D Class Declaration
class Camera2D
{
    public:
        //Constructor(Default and 2 argument version)
        Camera2D(const double x=0.0,const double y=0.0);

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
        void addR(const double add);

        //Member Rotation Accessor
        double R() const;

    private:
        //Member Variables
        double _x;
        double _y;
        double _rot;
};

#endif
