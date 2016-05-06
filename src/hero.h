//hero.h
//Created By:  Mike Moss
//Description:  Entity child hero class for Glut game, easily convertable for multiplayer game.
//Date:  2011

#ifndef HERO_H
#define HERO_H

class Dungeon;

//Algorithm Header
#include <algorithm>

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//Dungoen Header
#include "dungeon.h"

//Entity Header
#include "entity.h"

//Glut2D Header
#include "glut2d.h"

//Item Header
#include "item.h"

//Sprite Header
#include "sprite.h"

//String Stream Header
#include <sstream>

//Text Header
#include "text.h"

//Timer Header
#include "timer.h"

//Vector Header
#include <vector>

//Hero Class Decalaration
class Hero:public Entity
{
    public:
        //Static Sprite Load Function(Must be called before created any instances of Hero)
        static void spriteLoad();

        //Constructor(Default and 2 argument version)
        Hero(const double x=0.0,const double y=0.0,const int _might=3,const int _vigor=10,const int _heart=3);

        //Copy Constructor
        Hero(const Hero& copy);

        //Hero Class Vigor Mutator
        void setVigor(const int vigor);

        //Member Won Mutator
        void setWon(const int won);

        //Member Won Accessor
        int Won() const;

        //Member Experience Adder
        void addXP(const int xp);

        //Member Experience Accessor
        int XP() const;

        //Member Ability Points Mutator
        void setAP(const int ap);

        //Member Ability Points Accessor
        int getAP() const;

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

        //Member Weapon Mutator
        void setWeapon(unsigned int weapon);

        //Member Weapon Accessor
        unsigned int getWeapon() const;

        //Member Add Item Function
        void addItem(const Item& item,Dungeon& d);

        //Member Remove Item Function
        void removeItem(const unsigned int index);

        //Member Inventory Accessor
        std::vector<Item> Inventory() const;

        //Member Update Function
        void update(BitVec& mapVec,BitVec& colVec,Dungeon& d);

        //Member Draw Function
        void draw();

        //Member Menu Mutator
        void setMenu(const bool show);

        //Member Draw Menu Function
        void drawMenu(const unsigned int viewWidth,const unsigned int viewHeight,const double x,const double y,const Text& font,const int numBooks);

        //Member Equipted Items Accessors/Mutators
        void setIArmor(Item* armor);
        Item* getIArmor() const;
        void setIHelm(Item* helm);
        Item* getIHelm() const;
        void setIJewelry(Item* jewelry);
        Item* getIJewelry() const;
        void setIWeapon(Item* weapon);
        Item* getIWeapon() const;

    protected:
        //Static Variables
        static unsigned int _sprItems;
        static unsigned int _sprWalkNorth;
        static unsigned int _sprWalkEast;
        static unsigned int _sprWalkSouth;
        static unsigned int _sprWalkWest;
        static unsigned int _sprAttackNorth;
        static unsigned int _sprAttackEast;
        static unsigned int _sprAttackSouth;
        static unsigned int _sprAttackWest;
        static unsigned int _sprAttackNone;
        static unsigned int _sprAttackAxe;
        static unsigned int _sprAttackFlail;
        static unsigned int _sprAttackSword;

        //Member Variables
        int _won;
        int _xp;
        int _ap;
        bool _attacking;
        Timer _attackTimer;
        Sprite _sprite;
        Sprite _spriteWeapon;
        bool _menuShow;
        int _menuPos;
        int _menuPage;
        int _menuInventoryPos;
        std::vector<Item> _inventory;
        Item* _iarmor;
        Item* _ihelm;
        Item* _ijewelry;
        Item* _iweapon;

        //Member Move on Grid Function
        void moveOnGrid();
};

#endif
