//item.h
//Created By:  Zack Willams
//Description:  Item class for Glut game, uses table based effect system.
//Date:  2011

#ifndef ITEM_H
#define ITEM_H

//Hero Header
#include "hero.h"

//String Header
#include <string>

//Item Class Declaration
class Item
{
    public:
        //Constructor(3 argument version)
        Item(const std::string name="",const std::string description="",const std::string effect="",const double rarity=0.0,unsigned int index=0);

        //Member Name Mutator
        void setName(const std::string& name);

        //Member Name Accessor
        std::string getName() const;

        //Member Description Mutator
        void setDescription(const std::string& description);

        //Member Description Accessor
        std::string getDescription() const;

        //Member Effect Mutator
        void setEffect(const std::string& effect);

        //Member Effect Accessor
        std::string getEffect() const;

        //Member Rarity Mutator
        void setRarity(const double rarity);

        //Member Rarity Accessor
        double getRarity() const;

        //Member Index Accessor
        unsigned int index() const;

        //Member Operator< Function
        bool operator<(const Item& rhs) const;

        //Member Operator== Function
        bool operator==(const Item& rhs) const;

        //Member Use Function
        bool use(Hero& user);

    private:
        //Member Effect Interpret Function
        void interpret(Hero& user,bool remove=false);

        //Member Variables
        std::string _name;
        std::string _description;
        std::string _effect;
        double _rarity;
        unsigned int _index;
};

#endif
