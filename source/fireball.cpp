//fireball.cpp
//Created By:  Mike Moss
//Description:  Fireball source.
//Date:  2011

//Definitions for "fireball.h"
#include "fireball.h"

//Pi Define
#define PI 3.14159265

//Fireball Class Static Variables
unsigned int Fireball::_sprFireball;

//Fireball Class Static Sprite Load Function(Must be called before created any instances of Fireball)
void Fireball::spriteLoad()
{
    _sprFireball=loadBMP("sprites/fireball.bmp");
}

//Fireball Class Constructor(Default and 2 argument version)
Fireball::Fireball(const double x,const double y,const double direction,const unsigned int timerTime):Object(x,y),
    _sprite(_sprFireball,2,60,30),_timer(100),_destroy(false)
{
    //Set Direction
    setR(direction);

    //Set Timer
    _timer.reset();
    _timer.setCurrent(timerTime);
}

//Fireball Class Member Timer Current Accessor
unsigned int Fireball::getTimerCurrent() const
{
    return _timer.current();
}

//Fireball Class Member Destroy Accessor
bool Fireball::destroy() const
{
    return _destroy;
}

//Fireball Class Member Update Function
void Fireball::update(Dungeon& d,const BitVec& mapVec)
{
    //Update Timer
    _timer.update();

    //Update Sprite
    _sprite.update(0.5);

    //Timer Check
    if(!_timer.state())
    {
        _destroy=true;
    }

    //Move
    addX(std::cos(R()/(180.0/PI))*2.0);
    addY(-std::sin(R()/(180.0/PI))*2.0);

    //Make Sure Position is Within Bounds of Map
    if(X()>=0.0&&X()<mapVec.sizeX()*16.0&&Y()>=0.0&&Y()<mapVec.sizeY()*16.0)
    {
        //Destroy if Hit Wall
        if(mapVec.get(X()/16.0,Y()/16.0)==1)
        {
            //Play Explode Sound
            if(distance(X()/16.0,Y()/16.0,d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
            {
                d.sndHydraExplode.play();
            }

            _destroy=true;
        }

        //Destroy if Hit Hero
        for(unsigned int ii=0;ii<d.sizeHero();++ii)
        {
            if(distance(X(),Y(),d.getHero(ii).X(),d.getHero(ii).Y())<8&&d.getHero(ii).Life()>0)
            {
                //Play Explode Sound
                if(distance(X()/16.0,Y()/16.0,d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                {
                    d.sndHydraExplode.play();
                    d.sndAttack.play();
                }

                //Deal Damage
                d.getHero(ii).setLife(d.getHero(ii).Life()-25);
                d.getHero(ii).setRGBA(1.0,0.0,0.0,-1.0);
                _destroy=true;
                break;
            }
        }
    }
}

//Fireball Class Member Draw Function
void Fireball::draw()
{
    //Draw Sprite
    _sprite.draw(-1,X()+8.0,Y(),1.0,1.0,R()+135.0);
}
