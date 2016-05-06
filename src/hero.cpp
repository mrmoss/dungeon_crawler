//hero.cpp
//Created By:  Mike Moss
//Description:  Hero source.
//Date:  2011

//Definitions for "hero.h"
#include "hero.h"

//Hero Class Defines
#define SCREENINVENTORYSIZE 22

//Hero Class Static Variables
unsigned int Hero::_sprItems;
unsigned int Hero::_sprWalkNorth;
unsigned int Hero::_sprWalkEast;
unsigned int Hero::_sprWalkSouth;
unsigned int Hero::_sprWalkWest;
unsigned int Hero::_sprAttackNorth;
unsigned int Hero::_sprAttackEast;
unsigned int Hero::_sprAttackSouth;
unsigned int Hero::_sprAttackWest;
unsigned int Hero::_sprAttackNone;
unsigned int Hero::_sprAttackAxe;
unsigned int Hero::_sprAttackFlail;
unsigned int Hero::_sprAttackSword;

//Hero Class Static Sprite Load Function
void Hero::spriteLoad()
{
    _sprItems=loadBMP("sprites/items.bmp");
    _sprWalkNorth=loadBMP("sprites/heroWalkNorth.bmp");
    _sprWalkEast=loadBMP("sprites/heroWalkEast.bmp");
    _sprWalkSouth=loadBMP("sprites/heroWalkSouth.bmp");
    _sprWalkWest=loadBMP("sprites/heroWalkWest.bmp");
    _sprAttackNorth=loadBMP("sprites/heroAttackNorth.bmp");
    _sprAttackEast=loadBMP("sprites/heroAttackEast.bmp");
    _sprAttackSouth=loadBMP("sprites/heroAttackSouth.bmp");
    _sprAttackWest=loadBMP("sprites/heroAttackWest.bmp");
    _sprAttackNone=loadBMP("sprites/heroAttackAxe.bmp");
    _sprAttackAxe=loadBMP("sprites/heroAttackAxe.bmp");
    _sprAttackFlail=loadBMP("sprites/heroAttackFlail.bmp");
    _sprAttackSword=loadBMP("sprites/heroAttackSword.bmp");
}

//Hero Class Constructor(Default and 2 argument version)
Hero::Hero(const double x,const double y,const int might,const int vigor,const int heart):Entity(x,y,might,vigor,heart,true),
    _won(false),_xp(0),_ap(3),_attacking(false),_attackTimer(20/Speed()+1),_sprite(_sprWalkSouth,2,32,16),
    _spriteWeapon(_sprAttackNone,4,64,16),_menuShow(false),_menuPos(0),_menuPage(0),_menuInventoryPos(0),
    _iarmor(NULL),_ihelm(NULL),_ijewelry(NULL),_iweapon(NULL)
{
    //Set Life to Full
    setLife(LifeMax());
}

//Hero Class Copy Constructor
Hero::Hero(const Hero& copy):Entity(copy._x,copy._y,copy._might,copy._vigor,copy._heart,true),_won(copy._won),_xp(copy._xp),_ap(copy._ap),
    _attacking(copy._attacking),_attackTimer(copy._attackTimer),_sprite(copy._sprite),_spriteWeapon(copy._spriteWeapon),_menuShow(copy._menuShow),
    _menuPos(copy._menuPos),_menuPage(copy._menuPage),_menuInventoryPos(copy._menuInventoryPos),_inventory(copy._inventory),_iarmor(NULL),
    _ihelm(NULL),_ijewelry(NULL),_iweapon(NULL)
{
    if(copy._iarmor!=NULL)
    {
        for(unsigned int ii=0;ii<_inventory.size();++ii)
        {
            if(*copy._iarmor==_inventory[ii])
            {
                _iarmor=&_inventory[ii];
                break;
            }
        }
    }

    if(copy._ihelm!=NULL)
    {
        for(unsigned int ii=0;ii<_inventory.size();++ii)
        {
            if(*copy._ihelm==_inventory[ii])
            {
                _ihelm=&_inventory[ii];
                break;
            }
        }
    }

    if(copy._ijewelry!=NULL)
    {
        for(unsigned int ii=0;ii<_inventory.size();++ii)
        {
            if(*copy._ijewelry==_inventory[ii])
            {
                _ijewelry=&_inventory[ii];
                break;
            }
        }
    }

    if(copy._iweapon!=NULL)
    {
        for(unsigned int ii=0;ii<_inventory.size();++ii)
        {
            if(*copy._iweapon==_inventory[ii])
            {
                _iweapon=&_inventory[ii];
                break;
            }
        }
    }

    //Set Life
    setLife(copy.Life());
}

//Hero Class Vigor Mutator
void Hero::setVigor(const int vigor)
{
    Entity::setVigor(vigor);
    _attackTimer=Timer(20/Speed()+1);
}

//Hero Class Member Won Mutator (1=winning, 2=won, and anything else means nothing!!!)
void Hero::setWon(const int won)
{
    _won=won;
}

//Hero Class Member Won Accessor
int Hero::Won() const
{
    return _won;
}

//Hero Class Member Experience Adder
void Hero::addXP(const int xp)
{
    _xp+=xp;
}

//Hero Class Member Experience Accessor
int Hero::XP() const
{
    return _xp;
}

//Hero Class Member Ability Points Mutator
void Hero::setAP(const int ap)
{
    _ap=ap;

    if(_ap<0)
    {
        _ap=0;
    }
}

//Hero Class Member Ability Points Accessor
int Hero::getAP() const
{
    return _ap;
}

//Hero Class Member Attacking Mutator
void Hero::setAttacking(const bool attacking,const int currentTime)
{
    _attacking=attacking;
    _attackTimer=Timer(20/Speed()+1);

    //Super Speed Bug Fix
    /*if(currentTime>0)
    {
        _attackTimer.setState(false);
    }*/

    //_attackTimer.setTime(currentTime);
}

//Hero Class Member Attacked Accessor
bool Hero::Attacked() const
{
    return _attacking;
}

//Hero Class Member Attack Time Accessor
int Hero::AttackTime() const
{
    return _attackTimer.current();
}

//Hero Class Member Direction Mutator
void Hero::setDirection(unsigned int dir)
{
    if(dir==0)
    {
        if(!_attacking)
        {
            _sprite.setTexture(_sprWalkEast);
        }
        else
        {
            _sprite.setTexture(_sprAttackEast);
        }
    }
    else if(dir==1)
    {
        if(!_attacking)
        {
            _sprite.setTexture(_sprWalkNorth);
        }
        else
        {
            _sprite.setTexture(_sprAttackNorth);
        }
    }
    else if(dir==2)
    {
        if(!_attacking)
        {
            _sprite.setTexture(_sprWalkWest);
        }
        else
        {
            _sprite.setTexture(_sprAttackWest);
        }
    }
    else if(dir==3)
    {
        if(!_attacking)
        {
            _sprite.setTexture(_sprWalkSouth);
        }
        else
        {
            _sprite.setTexture(_sprAttackSouth);
        }
    }
    else
    {
        throw std::runtime_error("Hero(dir) - Invalid direction!!!");
    }

    _spriteWeapon.setIndex(dir);
}

//Hero Class Member Direction Accessor
unsigned int Hero::getDirection() const
{
    if(_sprite.texture()==_sprWalkEast||_sprite.texture()==_sprAttackEast)
    {
        return 0;
    }
    else if(_sprite.texture()==_sprWalkNorth||_sprite.texture()==_sprAttackNorth)
    {
        return 1;
    }
    else if(_sprite.texture()==_sprWalkWest||_sprite.texture()==_sprAttackWest)
    {
        return 2;
    }
    else if(_sprite.texture()==_sprWalkSouth||_sprite.texture()==_sprAttackSouth)
    {
        return 3;
    }

    throw std::runtime_error("Hero(dir) - Invalid direction!!!");
}

//Hero Class Member Weapon Mutator
void Hero::setWeapon(const unsigned int weapon)
{
    if(weapon==0)
    {
        _spriteWeapon.setTexture(_sprAttackNone);
    }
    else if(weapon==1)
    {
        _spriteWeapon.setTexture(_sprAttackAxe);
    }
    else if(weapon==2)
    {
        _spriteWeapon.setTexture(_sprAttackFlail);
    }
    else if(weapon==3)
    {
        _spriteWeapon.setTexture(_sprAttackSword);
    }
    else
    {
        throw std::runtime_error("Hero(weapon) - Invalid weapon!!!");
    }
}

//Hero Class Member Weapon Accessor
unsigned int Hero::getWeapon() const
{
    if(_spriteWeapon.texture()==_sprAttackNone)
    {
        return 0;
    }
    else if(_spriteWeapon.texture()==_sprAttackAxe)
    {
        return 1;
    }
    else if(_spriteWeapon.texture()==_sprAttackFlail)
    {
        return 2;
    }
    else if(_spriteWeapon.texture()==_sprAttackSword)
    {
        return 3;
    }

    throw std::runtime_error("Hero(weapon) - Invalid weapon!!!");
}


//Hero Class Member Add Item Function(Adds an item to inventory)
void Hero::addItem(const Item& item,Dungeon& d)
{
    //Check for Quest
    if(item.getEffect()[0]=='q')
    {
        d.addBook();
    }

    //Fix Vector Reallocation Bug
    Item armor("notta","","",0.0);
    Item helm("notta","","",0.0);
    Item jewelry("notta","","",0.0);
    Item weapon("notta","","",0.0);

    if(_iarmor!=NULL)
    {
        armor=*_iarmor;
    }

    if(_ihelm!=NULL)
    {
        helm=*_ihelm;
    }

    if(_ijewelry!=NULL)
    {
        jewelry=*_ijewelry;
    }

    if(_iweapon!=NULL)
    {
        weapon=*_iweapon;
    }

    _iarmor=NULL;
    _ihelm=NULL;
    _ijewelry=NULL;
    _iweapon=NULL;

    //Add Item
    _inventory.push_back(item);

    //Sort Items
    std::sort(_inventory.begin(),_inventory.end());

    //Reassign Equipment
    for(unsigned int ii=0;ii<_inventory.size();++ii)
    {
        if(_inventory[ii]==armor)
        {
            _iarmor=&_inventory[ii];
        }
        else if(_inventory[ii]==helm)
        {
            _ihelm=&_inventory[ii];
        }
        else if(_inventory[ii]==jewelry)
        {
            _ijewelry=&_inventory[ii];
        }
        else if(_inventory[ii]==weapon)
        {
            _iweapon=&_inventory[ii];
        }

        if(_iarmor!=NULL&&_ihelm!=NULL&&_ijewelry!=NULL&&_iweapon!=NULL)
        {
            break;
        }
    }
}

//Hero Class Member Remove Item Function(Removes an item to inventory)
void Hero::removeItem(const unsigned int index)
{
    //Check Bounds
    if(index>=_inventory.size())
    {
        throw std::runtime_error("Hero(removeItem) - Index passed was out of bounds!!!");
    }

    //Fix Vector Reallocation Bug
    Item armor("notta","","",0.0);
    Item helm("notta","","",0.0);
    Item jewelry("notta","","",0.0);
    Item weapon("notta","","",0.0);

    if(_iarmor!=NULL)
    {
        armor=*_iarmor;
    }

    if(_ihelm!=NULL)
    {
        helm=*_ihelm;
    }

    if(_ijewelry!=NULL)
    {
        jewelry=*_ijewelry;
    }

    if(_iweapon!=NULL)
    {
        weapon=*_iweapon;
    }

    _iarmor=NULL;
    _ihelm=NULL;
    _ijewelry=NULL;
    _iweapon=NULL;

    //Add Item
    _inventory.erase(_inventory.begin()+index);

    //Reassign Equipment
    for(unsigned int ii=0;ii<_inventory.size();++ii)
    {
        if(_inventory[ii]==armor)
        {
            _iarmor=&_inventory[ii];
        }
        else if(_inventory[ii]==helm)
        {
            _ihelm=&_inventory[ii];
        }
        else if(_inventory[ii]==jewelry)
        {
            _ijewelry=&_inventory[ii];
        }
        else if(_inventory[ii]==weapon)
        {
            _iweapon=&_inventory[ii];
        }

        if(_iarmor!=NULL&&_ihelm!=NULL&&_ijewelry!=NULL&&_iweapon!=NULL)
        {
            break;
        }
    }
}

//Hero Class Member Inventory Accessor
std::vector<Item> Hero::Inventory() const
{
    return _inventory;
}

//Hero Class Member Update Function
void Hero::update(BitVec& mapVec,BitVec& colVec,Dungeon& d)
{
    //Health Bug Fix
    if(_life>_lifeMax)
    {
        _life=_lifeMax;
    }

    //If Won
    if(_won==1)
    {
        _menuShow=false;
        _colR=0.0;
        _colB=1.0;
        _colG=0.0;
        _colA-=0.0125;

        if(_colA<=0)
        {
            _won=2;
        }
    }

    //If Dead
    if(_life<=0)
    {
        _menuShow=false;
        _colR=1.0;
        _colB=0.0;
        _colG=0.0;
        _colA-=0.0125;

        if(_colA<=0.0)
        {
            setDead(true);
        }
    }

    //Add AP when XP is High Enough (Psuedo Leveling)
    while(_xp>=1000)
    {
        ++_ap;
        _xp-=1000;
        setLife(LifeMax());

        //Play Level Sound
        if(true)//distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
        {
            d.sndHeroLevel.play();
        }
    }

    //Colors
    double colRate=0.05;

    if(_colR<1.0)
    {
        _colR+=colRate;
    }

    if(_colG<1.0)
    {
        _colG+=colRate;
    }

    if(_colB<1.0)
    {
        _colB+=colRate;
    }

    //Quick Use Potions
    if(input_check_pressed(kb_z)&&_won!=1&&_won!=2&&Life()>0)
    {
        for(unsigned int ii=0;ii<_inventory.size();++ii)
        {
            if(_inventory[ii].getEffect()[0]=='c')
            {
                //Play Potion Sound
                if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                {
                    d.sndPotion.play();
                }

                _inventory[ii].use(*this);
                removeItem(ii);
                break;
            }
        }
    }

    //Do Game Update
    if(_won!=1&&_won!=2&&Life()>0&&_menuShow)
    {
        //Change Page
        if(input_check_pressed(kb_right))
        {
            ++_menuPage;
            _menuPos=0;
            _menuInventoryPos=0;

            if(_menuPage>2)
            {
                _menuPage=0;
            }
        }

        if(input_check_pressed(kb_left))
        {
            --_menuPage;
            _menuPos=0;
            _menuInventoryPos=0;

            if(_menuPage<0)
            {
                _menuPage=2;
            }
        }

        //Select Menu Option
        if(input_check_pressed(kb_space))
        {
            if(_menuPage==0)
            {
                if(_ap>0)
                {
                    if(_menuPos==0)
                    {
                        Item* weapon=_iweapon;

                        if(_iweapon!=NULL)
                        {
                            _iweapon->use(*this);
                        }

                        setMight(Might()+1);

                        if(weapon!=NULL)
                        {
                            weapon->use(*this);
                        }
                    }
                    else if(_menuPos==1)
                    {
                        setVigor(Vigor()+1);
                    }
                    else if(_menuPos==2)
                    {
                        setHeart(Heart()+1);
                    }

                    --_ap;
                }
            }
            else if(_menuPage==1)
            {
                if(_inventory.size()>0)
                {
                    if(_inventory[_menuPos].use(*this))
                    {
                        //Play Potion Sound
                        if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                        {
                            d.sndPotion.play();
                        }

                        removeItem(_menuPos);

                        if(_menuPos>=static_cast<int>(_inventory.size()))
                        {
                            --_menuPos;

                            if(_menuInventoryPos>0)
                            {
                                --_menuInventoryPos;
                            }
                        }
                    }
                    else if(_inventory[_menuPos].getEffect()[0]!='q')
                    {
                        //Play Equip Sound
                        if(d.getViewEntity()==this)
                        {
                            d.sndHeroEquip.play();
                        }
                    }
                }
            }
            else if(_menuPage==2)
            {
                if(_menuPos==0)
                {
                    d.save();
                    _menuShow=false;
                }
                else if(_menuPos==1)
                {
                    _menuShow=false;
                }
                else if(_menuPos==2)
                {
                    d.destroy();
                }
            }
        }

        //Change Menu Option
        if(input_check_pressed(kb_up))
        {
            --_menuPos;

            if(_menuPage==0)
            {
                if(_menuPos<0)
                {
                    _menuPos=2;
                }
            }
            else if(_menuPage==1)
            {
                if(_inventory.size()<=0)
                {
                    _menuPos=0;
                    _menuInventoryPos=0;
                }
                else
                {
                    if(_menuPos<0)
                    {
                        _menuPos=_inventory.size()-1;

                        if(_inventory.size()>=SCREENINVENTORYSIZE)
                        {
                            _menuInventoryPos=_menuPos-SCREENINVENTORYSIZE+2;
                        }
                    }
                    else if(_menuPos<_menuInventoryPos)
                    {
                        --_menuInventoryPos;
                    }
                }
            }
            else if(_menuPage==2)
            {
                if(_menuPos<0)
                {
                    _menuPos=2;
                }
            }
        }

        if(input_check_pressed(kb_down))
        {
            ++_menuPos;

            if(_menuPage==0)
            {
                if(_menuPos>2)
                {
                    _menuPos=0;
                }
            }
            else if(_menuPage==1)
            {
                if(_menuPos>=static_cast<int>(_inventory.size()))
                {
                    _menuPos=0;
                    _menuInventoryPos=0;
                }

                if(_menuPos>=SCREENINVENTORYSIZE-1+_menuInventoryPos)
                {
                    ++_menuInventoryPos;
                }
            }
            else if(_menuPage==2)
            {
                if(_menuPos>2)
                {
                    _menuPos=0;
                }
            }
        }
    }
    else if(_won!=1&&_won!=2&&Life()>0)
    {
        //Attack
        if(input_check(kb_x)&&!Moved()&&!_attacking&&!_attackTimer.state())
        {
            _attacking=true;
            _attackTimer.reset();
            _sprite.setIndex(0);

            if(_sprite.texture()==_sprWalkNorth)
            {
                bool chest=false;

                for(unsigned int ii=0;ii<d.sizeChest();++ii)
                {
                    if(!d.getChest(ii).open()&&gridize(d.getChest(ii).X())==XT()&&gridize(d.getChest(ii).Y())==YT()-1)
                    {
                        d.getChest(ii).setOpen(true,d);

                        if(d.getChest(ii).hasBook())
                        {
                            addItem(d.Items[0],d);
                        }

                        for(int jj=0;jj<rand()%10;++jj)
                        {
                            addItem(d.Items[1+rand()%(d.Items.size()-1)],d);
                        }
                    }
                }

                if(!chest)
                {
                    //Play Swing Sound
                    if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                    {
                        d.sndSwing.play();
                    }

                    _sprite.setTexture(_sprAttackNorth);
                    _spriteWeapon.setIndex(1);

                    for(unsigned int ii=0;ii<d.sizeEnemy();++ii)
                    {
                        if(!d.getEnemy(ii).Dead()&&d.getEnemy(ii).Life()>0&&d.getEnemy(ii).XT()==XT()&&d.getEnemy(ii).YT()==YT()-1)
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getEnemy(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getEnemy(ii).setLife(d.getEnemy(ii).Life()-Damage());

                            if(d.getEnemy(ii).Life()<=0)
                            {
                                _xp+=rand()%50;
                            }
                        }
                    }

                    for(unsigned int ii=0;ii<d.sizeHydra();++ii)
                    {
                        if(!d.getHydra(ii).Dead()&&(d.getHydra(ii).XT()==XT()||d.getHydra(ii).XT()+1==XT())&&d.getHydra(ii).YT()==YT()-1)
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getHydra(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getHydra(ii).setLife(d.getHydra(ii).Life()-Damage());

                            if(d.getHydra(ii).Life()<=0)
                            {
                                _xp+=rand()%500;
                            }
                        }
                    }
                }
            }
            else if(_sprite.texture()==_sprWalkEast)
            {
                bool chest=false;

                for(unsigned int ii=0;ii<d.sizeChest();++ii)
                {
                    if(!d.getChest(ii).open()&&gridize(d.getChest(ii).X())==XT()+1&&gridize(d.getChest(ii).Y())==YT())
                    {
                        d.getChest(ii).setOpen(true,d);

                        if(d.getChest(ii).hasBook())
                        {
                            addItem(d.Items[0],d);
                        }

                        for(int jj=0;jj<rand()%10;++jj)
                        {
                            addItem(d.Items[1+rand()%(d.Items.size()-1)],d);
                        }
                    }
                }

                if(!chest)
                {
                    //Play Swing Sound
                    if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                    {
                        d.sndSwing.play();
                    }

                    _sprite.setTexture(_sprAttackEast);
                    _spriteWeapon.setIndex(0);

                    for(unsigned int ii=0;ii<d.sizeEnemy();++ii)
                    {
                        if(!d.getEnemy(ii).Dead()&&d.getEnemy(ii).Life()>0&&d.getEnemy(ii).XT()==XT()+1&&d.getEnemy(ii).YT()==YT())
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getEnemy(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getEnemy(ii).setLife(d.getEnemy(ii).Life()-Damage());

                            if(d.getEnemy(ii).Life()<=0)
                            {
                                _xp+=rand()%50;
                            }
                        }
                    }

                    for(unsigned int ii=0;ii<d.sizeHydra();++ii)
                    {
                        if(!d.getHydra(ii).Dead()&&d.getHydra(ii).XT()==XT()+1&&d.getHydra(ii).YT()==YT())
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getHydra(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getHydra(ii).setLife(d.getHydra(ii).Life()-Damage());

                            if(d.getHydra(ii).Life()<=0)
                            {
                                _xp+=rand()%500;
                            }
                        }
                    }
                }
            }
            else if(_sprite.texture()==_sprWalkSouth)
            {
                bool chest=false;

                for(unsigned int ii=0;ii<d.sizeChest();++ii)
                {
                    if(!d.getChest(ii).open()&&gridize(d.getChest(ii).X()==XT())&&gridize(d.getChest(ii).Y())==YT()+1)
                    {
                        d.getChest(ii).setOpen(true,d);

                        if(d.getChest(ii).hasBook())
                        {
                            addItem(d.Items[0],d);
                        }

                        for(int jj=0;jj<rand()%10;++jj)
                        {
                            addItem(d.Items[1+rand()%(d.Items.size()-1)],d);
                        }
                    }
                }

                if(!chest)
                {
                    //Play Swing Sound
                    if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                    {
                        d.sndSwing.play();
                    }

                    _sprite.setTexture(_sprAttackSouth);
                    _spriteWeapon.setIndex(3);

                    for(unsigned int ii=0;ii<d.sizeEnemy();++ii)
                    {
                        if(!d.getEnemy(ii).Dead()&&d.getEnemy(ii).Life()>0&&d.getEnemy(ii).XT()==XT()&&d.getEnemy(ii).YT()==YT()+1)
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getEnemy(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getEnemy(ii).setLife(d.getEnemy(ii).Life()-Damage());

                            if(d.getEnemy(ii).Life()<=0)
                            {
                                _xp+=rand()%50;
                            }
                        }
                    }

                    for(unsigned int ii=0;ii<d.sizeHydra();++ii)
                    {
                        if(!d.getHydra(ii).Dead()&&(d.getHydra(ii).XT()==XT()||d.getHydra(ii).XT()+1==XT())&&d.getHydra(ii).YT()==YT()+1)
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getHydra(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getHydra(ii).setLife(d.getHydra(ii).Life()-Damage());

                            if(d.getHydra(ii).Life()<=0)
                            {
                                _xp+=rand()%500;
                            }
                        }
                    }
                }
            }
            else if(_sprite.texture()==_sprWalkWest)
            {
                bool chest=false;

                for(unsigned int ii=0;ii<d.sizeChest();++ii)
                {
                    if(!d.getChest(ii).open()&&gridize(d.getChest(ii).X())==XT()-1&&gridize(d.getChest(ii).Y())==YT())
                    {
                        d.getChest(ii).setOpen(true,d);

                        if(d.getChest(ii).hasBook())
                        {
                            addItem(d.Items[0],d);
                        }

                        for(int jj=0;jj<rand()%10;++jj)
                        {
                            addItem(d.Items[1+rand()%(d.Items.size()-1)],d);
                        }
                    }
                }

                if(!chest)
                {
                    //Play Swing Sound
                    if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                    {
                        d.sndSwing.play();
                    }

                    _sprite.setTexture(_sprAttackWest);
                    _spriteWeapon.setIndex(2);

                    for(unsigned int ii=0;ii<d.sizeEnemy();++ii)
                    {
                        if(!d.getEnemy(ii).Dead()&&d.getEnemy(ii).Life()>0&&d.getEnemy(ii).XT()==XT()-1&&d.getEnemy(ii).YT()==YT())
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getEnemy(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getEnemy(ii).setLife(d.getEnemy(ii).Life()-Damage());

                            if(d.getEnemy(ii).Life()<=0)
                            {
                                _xp+=rand()%50;
                            }
                        }
                    }

                    for(unsigned int ii=0;ii<d.sizeHydra();++ii)
                    {
                        if(!d.getHydra(ii).Dead()&&d.getHydra(ii).XT()+1==XT()-1&&d.getHydra(ii).YT()==YT())
                        {
                            //Play Attack Sound
                            if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
                            {
                                d.sndAttack.play();
                            }

                            d.getHydra(ii).setRGBA(1.0,0.0,0.0,-1.0);
                            d.getHydra(ii).setLife(d.getHydra(ii).Life()-Damage());

                            if(d.getHydra(ii).Life()<=0)
                            {
                                _xp+=rand()%500;
                            }
                        }
                    }
                }
            }
            else
            {
                throw std::runtime_error("Hero(Update) - This shouldn't of happened!!!");
            }
        }

        //Move Up
        if(input_check(kb_up)&&!Moved()&&!_attacking)
        {
            if(mapVec.get(XT(),YT()-1)==0&&colVec.get(XT(),YT()-1)==0&&!input_check(kb_x))
            {
                colVec.set(XT(),YT(),0);
                addYT(-1);
                colVec.set(XT(),YT(),1);
            }
            else
            {
                _sprite.setTexture(_sprWalkNorth);
            }
        }

        //Move Down
        if(input_check(kb_down)&&!Moved()&&!_attacking)
        {
            if(mapVec.get(XT(),YT()+1)==0&&colVec.get(XT(),YT()+1)==0&&!input_check(kb_x))
            {
                colVec.set(XT(),YT(),0);
                addYT(1);
                colVec.set(XT(),YT(),1);
            }
            else
            {
                _sprite.setTexture(_sprWalkSouth);
            }
        }

        //Move Left
        if(input_check(kb_left)&&!Moved()&&!_attacking)
        {
            if(mapVec.get(XT()-1,YT())==0&&colVec.get(XT()-1,YT())==0&&!input_check(kb_x))
            {
                colVec.set(XT(),YT(),0);
                addXT(-1);
                colVec.set(XT(),YT(),1);
            }
            else
            {
                _sprite.setTexture(_sprWalkWest);
            }
        }

        //Move Right
        if(input_check(kb_right)&&!Moved()&&!_attacking)
        {
            if(mapVec.get(XT()+1,YT())==0&&colVec.get(XT()+1,YT())==0&&!input_check(kb_x))
            {
                colVec.set(XT(),YT(),0);
                addXT(1);
                colVec.set(XT(),YT(),1);
            }
            else
            {
                _sprite.setTexture(_sprWalkEast);
            }
        }

        //Toggle Menu
        if(input_check_pressed(kb_space))
        {
            _menuShow=true;
        }
    }

    //Attacking Animation Handling
    if(_attacking)
    {
        _sprite.update(Speed()/16);

        if(_sprite.index()==_sprite.imageNumber()-1)
        {
            _attacking=false;

            if(_sprite.texture()==_sprAttackNorth)
            {
                _sprite.setTexture(_sprWalkNorth);
            }
            else if(_sprite.texture()==_sprAttackEast)
            {
                _sprite.setTexture(_sprWalkEast);
            }
            else if(_sprite.texture()==_sprAttackSouth)
            {
                _sprite.setTexture(_sprWalkSouth);
            }
            else if(_sprite.texture()==_sprAttackWest)
            {
                _sprite.setTexture(_sprWalkWest);
            }
        }
    }

    //Attack Timer Update
    if(_won!=1&&_won!=2&&Life()>0)
    {
        _attackTimer.update();
    }

    //Move on Grid
    moveOnGrid();

    //Grid Alignment Fix
    if(!Moved())
    {
        setX(gridize(X())*gridSize());
        setY(gridize(Y())*gridSize());
    }
}

//Hero Class Member Draw Function
void Hero::draw()
{
    //Draw Weapon Sprite
    if(_attacking&&_spriteWeapon.texture()!=_sprAttackNone)
    {
        int offset=16.0;

        if(_spriteWeapon.index()==0)
        {
            _spriteWeapon.draw(-1,X()+8.0+offset,Y()+8.0,_scaleX,_scaleY,_rot,_colA);
        }
        else if(_spriteWeapon.index()==1)
        {
            _spriteWeapon.draw(-1,X()+8.0,Y()+8.0-offset,_scaleX,_scaleY,_rot,_colA);
        }
        else if(_spriteWeapon.index()==2)
        {
            _spriteWeapon.draw(-1,X()+8.0-offset,Y()+8.0,_scaleX,_scaleY,_rot,_colA);
        }
        else if(_spriteWeapon.index()==3)
        {
            _spriteWeapon.draw(-1,X()+8.0,Y()+8.0+offset,_scaleX,_scaleY,_rot,_colA);
        }
    }

    //Draw Player Sprite
    _sprite.draw(-1,X()+8.0,Y()+8.0,_scaleX,_scaleY,_rot,_colA,_colR,_colG,_colB);

    //Draw Hit Effect
    if(_won!=1&&_won!=2&&_life>0)
    {
        Sprite hit(Entity::_sprHit,1,16,16);
        hit.draw(0,X()+8.0,Y()+8.0,_scaleX,_scaleY,_rot,1.0-_colG-_colB,1.0,1.0,1.0);
    }
}

//Hero Class Member Menu Mutator
void Hero::setMenu(const bool show)
{
    _menuShow=show;
}

//Hero Class Member Draw Menu Function
void Hero::drawMenu(const unsigned int viewWidth,const unsigned int viewHeight,const double x,const double y,const Text& font,const int numBooks)
{
    //Font Draw
    if(_menuShow)
    {
        double width=viewWidth;
        double height=viewHeight;

        glPushMatrix();
        glBegin(GL_QUADS);
        glColor4f(0.0,0.0,0.0,0.75);
            glVertex2f(x,y);
            glVertex2f(x+width,y);
            glVertex2f(x+width,y+height);
            glVertex2f(x,y+height);
        glEnd();
        glPopMatrix();

        if(_menuPage==0)
        {
            std::ostringstream mightStr;
            mightStr<<"  MIGHT "<<Might();

            std::ostringstream vigorStr;
            vigorStr<<"  VIGOR "<<Vigor();

            std::ostringstream heartStr;
            heartStr<<"  HEART "<<Heart();

            std::ostringstream apStr;
            apStr<<"POINTS: "<<_ap;

            std::ostringstream lifeStr;
            std::ostringstream lifeMaxStr;
            lifeStr<<"LIFE:   "<<Life();
            lifeMaxStr<<LifeMax();

            while(lifeStr.str().size()<lifeMaxStr.str().size())
            {
                lifeStr<<' ';
            }

            lifeStr<<" / "<<LifeMax();

            std::ostringstream damStr;
            damStr<<"DAMAGE: "<<Damage();

            std::ostringstream xpStr;
            xpStr<<"XP:     "<<_xp;

            while(xpStr.str().size()<12)
            {
                xpStr<<' ';
            }

            xpStr<<" / "<<"1000";

            font.draw("STATS",x,y);
            font.draw(mightStr.str(),x,y+font.height()*2.0);
            font.draw(vigorStr.str(),x,y+font.height()*3.0);
            font.draw(heartStr.str(),x,y+font.height()*4.0);
            font.draw(apStr.str(),x,y+font.height()*6.0);
            font.draw(lifeStr.str(),x,y+font.height()*8.0);
            font.draw(damStr.str(),x,y+font.height()*9.0);
            font.draw(xpStr.str(),x,y+font.height()*10.0);
            font.draw(">",x,y+font.height()*(2+_menuPos));
        }
        else if(_menuPage==1)
        {
            //Draw Header
            font.draw("INVENTORY",x,y);

            //Initialize Description and Icon Sprite
            std::string descriptionStr="NONE.";
            int itemInd=-1;

            for(unsigned int ii=_menuInventoryPos;ii<_inventory.size()&&ii<static_cast<unsigned int>(_menuInventoryPos+SCREENINVENTORYSIZE-1);++ii)
            {
                //Figure Out Item Name
                std::ostringstream itemStr;
                itemStr<<"  "<<_inventory[ii].getName();

                //If Item is Highlighted
                if(_menuPos==static_cast<int>(ii))
                {
                    descriptionStr=_inventory[ii].getDescription();
                    itemInd=_inventory[ii].index();
                }

                //If Item is Equipped
                if(&_inventory[ii]==_iarmor||&_inventory[ii]==_ihelm||&_inventory[ii]==_ijewelry||&_inventory[ii]==_iweapon)
                {
                    itemStr<<" E";
                }

                //Draw Item Name
                font.draw(itemStr.str(),x,y+font.height()*(2.0+ii-_menuInventoryPos));
            }

            //Draw Cursor
            font.draw(">",x,y+font.height()*(2+_menuPos-_menuInventoryPos));

            //Draw Description
            font.draw("DESCRIPTION:",x,y+font.height()*(2.0+SCREENINVENTORYSIZE+2));
            font.draw(descriptionStr,x+18.0+font.width(),y+font.height()*(2.0+SCREENINVENTORYSIZE+3));

            //Item Sprite Border
            Sprite itemSpr(_sprItems,26,468,18);
            itemSpr.draw(25,x+13.0,y+font.height()*(2.0+SCREENINVENTORYSIZE+4)+3.0);

            //Draw Item Icon Sprite
            if(itemInd>=0)
            {
                itemSpr.draw(itemInd,x+13.0,y+font.height()*(2.0+SCREENINVENTORYSIZE+4)+3.0);
            }
        }
        else if(_menuPage==2)
        {
            font.draw("OPTIONS",x,y);
            font.draw("  SAVE",x,y+font.height()*2.0);
            font.draw("  CLOSE",x,y+font.height()*3.0);
            font.draw("  QUIT",x,y+font.height()*4.0);
            font.draw(">",x,y+font.height()*(2+_menuPos));
        }
    }
    else
    {
        std::ostringstream bookStr;
        bookStr<<"BOOKS: "<<numBooks;

        std::ostringstream lifeStr;
        std::ostringstream lifeMaxStr;
        lifeStr<<Life();
        lifeMaxStr<<LifeMax();

        while(lifeStr.str().size()<lifeMaxStr.str().size())
        {
            lifeStr<<' ';
        }

        lifeStr<<" / "<<LifeMax();

        font.draw(bookStr.str(),x,y);
        font.draw("LIFE:  "+lifeStr.str(),x,y+font.height());
    }
}

//Hero Class Member Equipted Armor Mutator
void Hero::setIArmor(Item* armor)
{
    _iarmor=armor;
}

//Hero Class Member Equipted Armor Accessor
Item* Hero::getIArmor() const
{
    return _iarmor;
}

//Hero Class Member Equipted Helm Mutator
void Hero::setIHelm(Item* helm)
{
    _ihelm=helm;
}

//Hero Class Member Equipted Helm Accessor
Item* Hero::getIHelm() const
{
    return _ihelm;
}

//Hero Class Member Equipted Jewelry Mutator
void Hero::setIJewelry(Item* jewelry)
{
    _ijewelry=jewelry;
}

//Hero Class Member Equipted Jewelry Accessor
Item* Hero::getIJewelry() const
{
    return _ijewelry;
}

//Hero Class Member Equipted Weapon Mutator
void Hero::setIWeapon(Item* weapon)
{
    _iweapon=weapon;
}

//Hero Class Member Equipted Weapon Accessor
Item* Hero::getIWeapon() const
{
    return _iweapon;
}

//Hero Class Member Move on Grid Function
void Hero::moveOnGrid()
{
    //Check Movement
    bool move=false;

    if(static_cast<int>(Y())<YT()*gridSize())
    {
        //Move South
        move=true;

        if(YT()*gridSize()-Y()<Speed())
        {
            addY(Speed()/4.0);
        }
        else
        {
            addY(Speed());
        }

        //Set Texture
        _sprite.setTexture(_sprWalkSouth);
    }
    else if(static_cast<int>(Y())>YT()*gridSize())
    {
        //Move North
        move=true;

        if(Y()-YT()*gridSize()<Speed())
        {
            addY(-Speed()/4.0);
        }
        else
        {
            addY(-Speed());
        }

        //Set Texture
        _sprite.setTexture(_sprWalkNorth);
    }
    else if(static_cast<int>(X())<XT()*gridSize())
    {
        //Move East
        move=true;

        if(XT()*gridSize()-X()<Speed())
        {
            addX(Speed()/4.0);
        }
        else
        {
            addX(Speed());
        }

        //Set Texture
        _sprite.setTexture(_sprWalkEast);
    }
    else if(static_cast<int>(X())>XT()*gridSize())
    {
        //Move West
        move=true;

        if(X()-XT()*gridSize()<Speed())
        {
            addX(-Speed()/4.0);
        }
        else
        {
            addX(-Speed());
        }

        //Set Texture
        _sprite.setTexture(_sprWalkWest);
    }

    //Update Sprite
    if(move)
    {
        _sprite.update(Speed()*0.15);
    }
    else if(!Moved()&&_sprite.index()>0)
    {
        _sprite.setIndex(0);
    }

    //Update Moved
    setMoved(move);
}
