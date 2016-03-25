//entity.cpp
//Created By:  Mike Moss
//Description:  Entity source.
//Date:  2011

//Definitions for "entity.h"
#include "entity.h"

//Entity Class Static Variables
unsigned int Entity::_sprHit;

//Entity Class Static Sprite Load Function
void Entity::spriteLoad()
{
    _sprHit=loadBMP("sprites/hit.bmp");
}

//Entity Class Constructor(Default and 2 argument version)
Entity::Entity(const double x,const double y,const int might,const int vigor,const int heart,const bool hero):Object(x,y),_hero(hero),
    _dead(false),_moved(false),_xto(gridize(_x)),_yto(gridize(_y)),_colR(1.0),_colG(1.0),_colB(1.0),_colA(1.0)
{
    //Update Other Stats
    setMight(might);
    setVigor(vigor);
    setHeart(heart);
    setLife(LifeMax());
}

//Entity Class Member Dead Mutator
void Entity::setDead(const bool dead)
{
    _dead=dead;
}

//Entity Class Member Dead Accessor
bool Entity::Dead() const
{
    return _dead;
}

//Entity Class Member Moved Mutator
void Entity::setMoved(const bool moved)
{
    _moved=moved;
}

//Entity Class Member Moved Accessor
bool Entity::Moved() const
{
    return _moved;
}

//Entity Class Member X To Mutator
void Entity::setXT(const int xto)
{
    _xto=xto;
}

//Entity Class Member X To Add Mutator
void Entity::addXT(const int add)
{
    _xto+=add;
}

//Entity Class Member X To Accessor
int Entity::XT() const
{
    return _xto;
}

//Entity Class Member Y To Mutator
void Entity::setYT(const int yto)
{
    _yto=yto;
}

//Entity Class Member Y To Add Mutator
void Entity::addYT(const int add)
{
    _yto+=add;
}

//Entity Class Member Y To Accessor
int Entity::YT() const
{
    return _yto;
}

//Entity Class Member Might Mutator
void Entity::setMight(const int might)
{
    _might=might;
    _damage=(_might*(2+(_might/3))/5)+1;
}

//Entity Class Member Might Accessor
int Entity::Might() const
{
    return _might;
}

//Entity Class Member Vigor Mutator
void Entity::setVigor(const int vigor)
{
    int offset=1;
    _vigor=vigor;
    _speed=((_vigor+offset)*0.25)+((10-_vigor+offset)*0.01);
}

//Entity Class Member Vigor Accessor
int Entity::Vigor() const
{
    return _vigor;
}

//Entity Class Member Heart Mutator
void Entity::setHeart(const int heart)
{
    _heart=heart;
    _lifeMax=_heart*(2+(_heart/3));

    if(_hero)
    {
        _lifeMax+=50;
    }
    else
    {
        _lifeMax+=10;
    }

    //_life=_lifeMax;
}

//Entity Class Member Heart Accessor
int Entity::Heart() const
{
    return _heart;
}

//Entity Class Member Damage Mutator
void Entity::setDamage(const int damage)
{
    _damage=damage;
}

//Entity Class Member Damage Accessor
int Entity::Damage() const
{
    return _damage;
}

//Entity Class Member Speed Mutator
void Entity::setSpeed(const int speed)
{
    _speed=speed;
}

//Entity Class Member Speed Accessor
double Entity::Speed() const
{
    int offset=1;

    if(_speed>((10+offset)*0.25)+((10-10+offset)*0.01))
    {
        return ((10+offset)*0.25)+((10-10+offset)*0.01);
    }

    return _speed;
}

//Entity Class Member Life Max Mutator
void Entity::setLifeMax(const int lifemax)
{
    _lifeMax=lifemax;
}

//Entity Class Member Life Max Accessor
int Entity::LifeMax() const
{
    return _lifeMax;
}

//Entity Class Member Life Mutator
void Entity::setLife(const int life)
{
    _life=life;

    if(_life<0)
    {
        _life=0;
    }
    else if(_life>_lifeMax)
    {
        _life=_lifeMax;
    }
}

//Entity Class Member Life Accessor
int Entity::Life() const
{
    return _life;
}

//Entity Class Member RGB Mutator
void Entity::setRGBA(const double red,const double green,const double blue,const double alpha)
{
    _colR=red;
    _colG=green;
    _colB=blue;

    if(alpha>=0.0)
    {
        _colA=alpha;
    }
}

//Entity Class Member RGB Accessor
void Entity::getRGBA(double& red,double& green,double& blue,double& alpha)
{
    red=_colR;
    green=_colG;
    blue=_colB;
    alpha=_colA;
}
