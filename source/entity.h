//hydra.h
//Created By:  Mike Moss
//Description:  Object child entity class, used as parent for heros and monsters in Glut game.
//Date:  2011

#ifndef ENTITY_H
#define ENTITY_H

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//Object Header
#include "object.h"

//Entity Class Declaration
class Entity:public Object
{
    public:
        //Static Sprite Load Function
        static void spriteLoad();

        //Constructor
        Entity(const double x=0.0,const double y=0.0,const int might=0,const int vigor=0,const int heart=0,const bool hero=false);

        //Member Moved Mutator
        void setMoved(const bool moved);

        //Member Moved Accessor
        bool Moved() const;

        //Member X To Mutators
        void setXT(const int xto);
        void addXT(const int add);

        //Member X To Accessor
        int XT() const;

        //Member Y To Mutators
        void setYT(const int yto);
        void addYT(const int add);

        //Member Y To Accessor
        int YT() const;

        //Virtual Member Move on Grid Function
        virtual void moveOnGrid()=0;

        //Member Dead Mutator
        void setDead(const bool dead);

        //Member Dead Accessor
        bool Dead() const;

        //Member Might Mutator
        void setMight(const int might);

        //Member Might Accessor
        int Might() const;

        //Member Vigor Mutator
        void setVigor(const int vigor);

        //Member Vigor Accessor
        int Vigor() const;

        //Member Heart Mutator
        void setHeart(const int heart);

        //Member Heart Accessor
        int Heart() const;

        //Member Damage Mutator
        void setDamage(const int damage);

        //Member Damage Accessor
        int Damage() const;

        //Member Speed Mutator
        void setSpeed(const int speed);

        //Member Speed Accessor
        double Speed() const;

        //Member Life Max Mutator
        void setLifeMax(const int lifemax);

        //Member Life Max Accessor
        int LifeMax() const;

        //Member Life Mutator
        void setLife(const int health);

        //Member Life Accessor
        int Life() const;

        //Member RGB Mutator
        void setRGBA(const double red,const double green,const double blue,const double alpha);

        //Member RGB Accessor
        void getRGBA(double& red,double& green,double& blue,double& alpha);

    protected:
        //Static Variables
        static unsigned int _sprHit;

        //Member Variables
        bool _hero;
        bool _dead;
        bool _moved;
        int _xto;
        int _yto;
        int _might;
        int _vigor;
        int _heart;
        int _damage;
        double _speed;
        int _lifeMax;
        int _life;
        double _colR;
        double _colG;
        double _colB;
        double _colA;
};

#endif
