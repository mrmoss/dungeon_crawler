//enemy.h
//Created By:  Mike Moss and Zack Willams
//Description:  Entity child enemy class for Glut game, uses table based movement/attack system.
//Date:  2011

#ifndef ENEMY_H
#define ENEMY_H

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//C Standard Library
#include <cstdlib>

//Entity Header
#include "entity.h"

//Glut2D Header
#include "glut2d.h"

//Hero Class
#include "hero.h"

//Sprite Header
#include "sprite.h"

//String Header
#include <string>

//Timer Header
#include "timer.h"

//Vector Header
#include <vector>

//Enemy Class Declaration
class Enemy:public Entity
{
    public:
        //Static Sprite Load Function(Must be called before created any instances of Enemy)
        static void spriteLoad();

        //Constructor(Default and 2 argument version)
        Enemy(const double x=0.0,const double y=0.0,const unsigned int type=0);

        //Member Patrol Coordinate Mutators
        void setPX(const unsigned int px);
        void setPY(const unsigned int py);

        //Member Patrol Coordinate Accessors
        unsigned int PX() const;
        unsigned int PY() const;

        //Member Attacking Mutator
        void setAttacking(const bool attacking,const int currentTime);

        //Member Attacked Accessor
        bool Attacked() const;

        //Member Attack Time Accessor
        int AttackTime() const;

        //Member Direction Mutator
        void setDirection(unsigned int dir);

        //Member Direction Accessor
        unsigned int getDirection() const;

        //Member Type Accessor
        unsigned int getType() const;

        //Member Patrolling Mutator
        void setPatrolling(bool patrol);

        //Member Patrolling Accessor
        bool getPatrolling() const;

        //Member Tables Mutator
        void setTables(const std::string& patrol,const std::string& table);

        //Member Tables Accessor
        void getTables(std::string& patrol,std::string& table);

        //Member Update Function
        void update(BitVec& mapVec,BitVec& colVec,Dungeon& d);

        //Member Draw Function
        void draw();

    private:
        //Static Variables
        static unsigned int _sprGhost;
        static unsigned int _sprSpecter;
        static unsigned int _sprSlime;
        static unsigned int _sprOoze;
        static unsigned int _sprBat;
        static unsigned int _sprVampire;
        static unsigned int _sprScorpion;
        static unsigned int _sprStinger;
        static unsigned int _sprSkeletonWhiteWalkNorth;
        static unsigned int _sprSkeletonWhiteWalkEast;
        static unsigned int _sprSkeletonWhiteWalkSouth;
        static unsigned int _sprSkeletonWhiteWalkWest;
        static unsigned int _sprSkeletonRedWalkNorth;
        static unsigned int _sprSkeletonRedWalkEast;
        static unsigned int _sprSkeletonRedWalkSouth;
        static unsigned int _sprSkeletonRedWalkWest;
        static unsigned int _sprSkeletonGoldWalkNorth;
        static unsigned int _sprSkeletonGoldWalkEast;
        static unsigned int _sprSkeletonGoldWalkSouth;
        static unsigned int _sprSkeletonGoldWalkWest;
        static unsigned int _sprImpWalkNorth;
        static unsigned int _sprImpWalkEast;
        static unsigned int _sprImpWalkSouth;
        static unsigned int _sprImpWalkWest;
        static unsigned int _sprDemonWalkNorth;
        static unsigned int _sprDemonWalkEast;
        static unsigned int _sprDemonWalkSouth;
        static unsigned int _sprDemonWalkWest;

        //Member Variables
        Hero* _chase;
        unsigned int _px;
        unsigned int _py;
        bool _attacking;
        Timer _attackTimer;
        Sprite _sprite;
        bool _patrolling;
        std::string _patrol;
        std::string _table;
        unsigned int _type;

        //Member Move on Grid Function
        void moveOnGrid();
};

#endif
