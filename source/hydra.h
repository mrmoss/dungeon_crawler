//hydra.h
//Created By:  Mike Moss and Zack Willams
//Description:  Entity child hydra class for Glut game, uses table based movement/attack system.
//Date:  2011

#ifndef HYDRA_H
#define HYDRA_H

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//C Standard Library
#include <cstdlib>

//Dungeon Header
#include "dungeon.h"

//Entity Header
#include "entity.h"

//Fireball Header
#include "fireball.h"

//Glut2D Header
#include "glut2d.h"

//Sprite Header
#include "sprite.h"

//String Header
#include <string>

//Vector Header
#include <vector>

//Hydra Class Declaration
class Hydra:public Entity
{
    public:
        //Static Sprite Load Function(Must be called before created any instances of Hydra)
        static void spriteLoad();

        //Constructor(Default and 3 argument version)
        Hydra(const double x=0.0,const double y=0.0,const unsigned int type=0);

        //Member Type Accessor
        unsigned int getType() const;

        //Member Tables Mutator
        void setTables(const std::string& patrol,const std::string& table);

        //Member Tables Accessor
        void getTables(std::string& patrol,std::string& table);

        //Member Update Function
        void update(BitVec& mapVec,BitVec& colVec,Dungeon& d);

        //Member Draw Function
        void draw(Dungeon& d);

    private:
        //Static Variables
        static unsigned int _sprHydraBody;
        static unsigned int _sprHydraFeet;
        static unsigned int _sprWyrmBody;
        static unsigned int _sprWyrmFeet;

        //Member Variables
        Sprite _body;
        Sprite _feet;
        std::string _patrol;
        std::string _table;

        //Member Move on Grid Function
        void moveOnGrid();
};

#endif
