//chest.cpp
//Created By:  Mike Moss
//Description:  Chest source.
//Date:  2011

//Definitions for "chest.h"
#include "chest.h"

//Chest Class Static Variables
unsigned int Chest::_sprChest;

//Chest Class Static Sprite Load Function
void Chest::spriteLoad()
{
    _sprChest=loadBMP("sprites/chest.bmp");
}

//Chest Class Constructor(Default and 2 argument version)
Chest::Chest(const double x,const double y,const bool hasBook):Object(x,y),_sprite(_sprChest,2,32,16),_hasBook(hasBook)
{}

//Chest Class Member Open Accessor
bool Chest::open() const
{
    return static_cast<bool>(_sprite.index());
}

//Chest Class Member Open Mutator
void Chest::setOpen(const bool open,const Dungeon& d,const bool playSound)
{
    _sprite.setIndex(static_cast<unsigned int>(open));

    //Play Chest Opening Sound
    if(playSound)
    {
        if(distance(d.getViewEntity()->XT(),d.getViewEntity()->YT(),X()/16.0,Y()/16.0)<20)
        {
            d.sndChestOpen.play();
        }
    }

    //Play Has Book Sound
    if(_hasBook&&playSound)
    {
        if(distance(d.getViewEntity()->XT(),d.getViewEntity()->YT(),X()/16.0,Y()/16.0)<20)
        {
            d.sndChestBook.play();
        }
    }
}

//Chest Class Member Has Book Accessor
bool Chest::hasBook() const
{
    return _hasBook;
}

//Chest Class Member Draw Function
void Chest::draw()
{
    _sprite.draw(-1,X()+8.0,Y()+8.0,_scaleX,_scaleY,_rot,1.0);
}

