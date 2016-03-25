//item.cpp
//Created By:  Zack Willams
//Description:  Item source.
//Date:  2011

//Definitions for "item.h"
#include "item.h"

//Item Class Constructor(3 argument version)
Item::Item(const std::string name,const std::string description,const std::string effect,const double rarity,const unsigned int index):
    _name(name),_description(description),_effect(effect),_rarity(rarity),_index(index)
{}

//Item Class Member Name Mutator
void Item::setName(const std::string& name)
{
    _name=name;
}

//Item Class Member Name Accessor
std::string Item::getName() const
{
    return _name;
}

//Item Class Member Description Mutator
void Item::setDescription(const std::string& description)
{
    _description=description;
}

//Item Class Member Description Accessor
std::string Item::getDescription() const
{
    return _description;
}

//Item Class Member Effect Mutator
void Item::setEffect(const std::string& effect)
{
    _effect=effect;
}

//Item Class Member Effect Accessor
std::string Item::getEffect() const
{
    return _effect;
}

//Item Class Member Rarity Mutator
void Item::setRarity(const double rarity)
{
    _rarity=rarity;
}

//Item Class Member Rarity Accessor
double Item::getRarity() const
{
    return _rarity;
}

//Item Class Member Index Accessor
unsigned int Item::index() const
{
    return _index;
}

//Item Class Member Operator< Function
bool Item::operator<(const Item& rhs) const
{
    return _name<rhs._name;
}

//Item Class Member Operator== Function
bool Item::operator==(const Item& rhs) const
{
    return (_name==rhs._name&&_description==rhs._description&&_effect==rhs._effect&&_rarity==rhs._rarity);
}

//Item Class Member Use Function
bool Item::use(Hero& user)
{
    bool delAfter=false;
    bool use=true;

    if(_effect.size()<=0)
    {
        throw std::runtime_error("Item(use) - Effect string has a size of 0!!!");
    }

    //Weapon Glitch Fix
    Item* weapon=user.getIWeapon();

    if(_effect[0]!='w'&&weapon!=NULL)
    {
        user.getIWeapon()->interpret(user,true);
        user.setIWeapon(NULL);
    }

    //Add Effects
    if(_effect[0]=='a')
    {
        if(user.getIArmor()!=NULL)
        {
            user.getIArmor()->interpret(user,true);
        }

        if(user.getIArmor()==this)
        {
            user.setIArmor(NULL);
            use=false;
        }
        else
        {
            user.setIArmor(this);
        }
    }
    else if(_effect[0]=='c')
    {
        delAfter=true;
    }
    else if(_effect[0]=='h')
    {
        if(user.getIHelm()!=NULL)
        {
            user.getIHelm()->interpret(user,true);
        }

        if(user.getIHelm()==this)
        {
            user.setIHelm(NULL);
            use=false;
        }
        else
        {
            user.setIHelm(this);
        }
    }
    else if(_effect[0]=='j')
    {
        if(user.getIJewelry()!=NULL)
        {
            user.getIJewelry()->interpret(user,true);
        }

        if(user.getIJewelry()==this)
        {
            user.setIJewelry(NULL);
            use=false;
        }
        else
        {
            user.setIJewelry(this);
        }
    }
    else if(_effect[0]=='w')
    {
        if(user.getIWeapon()!=NULL)
        {
            user.getIWeapon()->interpret(user,true);
        }

        if(user.getIWeapon()==this)
        {
            user.setIWeapon(NULL);
            use=false;
        }
        else
        {
            user.setIWeapon(this);
        }
    }

    if(use)
    {
        interpret(user);
    }


    //Weapon Glitch Fix
    if(_effect[0]!='w'&&weapon!=NULL)
    {
        user.setIWeapon(weapon);
        user.getIWeapon()->interpret(user);
    }

    return delAfter;
}

//Item Class Member Effect Interpret Function
void Item::interpret(Hero& user,bool remove)
{
    int addorsub=1;

    if(remove)
    {
        addorsub=-1;
    }

    unsigned int pos=1;

    if(_effect.size()<=0)
    {
        throw std::runtime_error("Item(interpret) - Effect string has a size of 0!!!");
    }

    while(pos<_effect.size())
    {
        char type;

        if((_effect[pos]>='a'&&_effect[pos]<='z')||(_effect[pos]>='A'&&_effect[pos]<='Z'))
        {
            type=_effect[pos];

            ++pos;

            if(pos>=_effect.size())
            {
                throw std::runtime_error("Item(interpret) - Effect string is not formatted correctly!!!");
            }

            int numSize=0;
            unsigned int pos2=pos;
            int attribute=0;
            bool negative=false;


            if(_effect[pos2]=='-')
            {
                negative=true;
                ++pos2;
            }

            while(_effect[pos2]>47&&_effect[pos2]<58)
            {
                ++numSize;
                ++pos2;
            }

            for(int ii=0;ii<numSize;++ii)
            {
                int num=_effect[pos+negative+ii]-48;

                for(int jj=0;jj<numSize-1-ii;++jj)
                {
                    num*=10;
                }

                attribute+=num;
            }

            if(negative)
            {
                attribute*=-1;
            }

            attribute*=addorsub;

            if(type=='m')
            {
                user.setMight(user.Might()+attribute);
            }
            else if(type=='v')
            {
                user.setVigor(user.Vigor()+attribute);
            }
            else if(type=='h')
            {
                user.setHeart(user.Heart()+attribute);
            }
            else if(type=='l')
            {
                user.setLife(user.Life()+attribute);

                if(attribute<0)
                {
                    user.setRGBA(1.0,0.0,0.0,-1.0);
                }
                else
                {
                    user.setRGBA(0.0,1.0,0.0,-1.0);
                }
            }
            else if(type=='L')
            {
                user.setLifeMax(user.LifeMax()+attribute);
            }
            else if(type=='d')
            {
                user.setDamage(user.Damage()+attribute);
            }
            else if(type=='q')
            {
                //DO NOTHING!!!
            }
            else if(type=='t')
            {
                if(attribute>=0&&attribute<4)
                {
                    user.setWeapon(attribute);
                }
                else
                {
                    user.setWeapon(0);
                }
            }
            else
            {
                throw std::runtime_error("Item(interpret) - Invalid effect type!!!");
            }

            pos+=negative+numSize;
        }
    }
}
