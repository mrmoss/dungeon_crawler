//fireball.h
//Created By:  Mike Moss
//Description:  Object child class fireball, projectile for hydras.
//Date:  2011

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//Dungeon Header
#include "dungeon.h"

//Glut2D Header
#include "glut2d.h"

//CMath Header
#include <cmath>

//Object Header
#include "object.h"

//Sprite Header
#include "sprite.h"

//Timer Header
#include "timer.h"

#ifndef FIREBALL_H
#define FIREBALL_H

//Fireball Class Decalaration
class Fireball:public Object
{
    public:
        //Static Sprite Load Function(Must be called before created any instances of Fireball)
        static void spriteLoad();

        //Constructor(Default and 2 argument version)
        Fireball(const double x=0.0,const double y=0.0,const double direction=0.0,const unsigned int timerTime=0);

        //Member Timer Current Accessor
        unsigned int getTimerCurrent() const;

        //Member Destroy Accessor
        bool destroy() const;

        //Member Update Function
        void update(Dungeon& d,const BitVec& mapVec);

        //Member Draw Function
        void draw();

    private:
        //Static Variables
        static unsigned int _sprFireball;

        //Member Variables
        Sprite _sprite;
        Timer _timer;
        bool _destroy;
};

#endif
