//chest.h
//Created By:  Mike Moss
//Description:  Entity child chest class for Glut game.
//Date:  2011

#ifndef CHEST_H
#define CHEST_H

//Class Declarations
class Dungeon;

//BMP Loader Header
#include "bmp.h"

//Dungeon Header
#include "dungeon.h"

//Glut2D Header
#include "glut2d.h"

//Object Header
#include "object.h"

//Sprite Header
#include "sprite.h"

//Chest Class Decalaration
class Chest:public Object
{
    public:
        //Static Sprite Load Function(Must be called before created any instances of Chest)
        static void spriteLoad();

        //Constructor(Default and 2 argument version)
        Chest(const double x=0.0,const double y=0.0,const bool hasBook=false);

        //Member Open Accessor
        bool open() const;

        //Member Open Mutator
        void setOpen(const bool open,const Dungeon& d,const bool playSound=true);

        //Member Has Book Accessor
        bool hasBook() const;

        //Member Draw Function
        void draw();

    private:
        //Static Variables
        static unsigned int _sprChest;

        //Member Variables
        Sprite _sprite;
        bool _hasBook;
};

#endif
