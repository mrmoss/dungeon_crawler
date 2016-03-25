//dungeon.h
//Created By:  Mike Moss and Charlie Carlson
//Description:  Dungeon loader for Glut game.  Loads a map(bit based) with heros, monsters, items, etc...
//Date:  2011

#ifndef TILESET_H
#define TILESET_H

//Class Declarations
class Item;
class Chest;
class Enemy;
class Fireball;
class Hero;
class Hydra;

//Bit Vector Header
#include "bitvec.h"

//BMP Loader Header
#include "bmp.h"

//Chest Header
#include "chest.h"

//Enemy Header
#include "enemy.h"

//File Stream Header
#include <fstream>

//Fireball Header
#include "fireball.h"

//Game Math Header
#include "gamemath.h"

//Hero Header
#include "hero.h"

//Hydra Header
#include "hydra.h"

//Item Header
#include "item.h"

//Sound Header
#include "sound.h"

//String Header
#include <string>

//Text Header
#include "text.h"

//Vector Header
#include <vector>

//Dungeon Class Declaration
class Dungeon
{
    public:
        //Static Member Variables
        static std::vector<Item> Items;
        static Sound sndChestOpen;
        static Sound sndChestBook;
        static Sound sndBatAlert;
        static Sound sndDemonAlert;
        static Sound sndGhostAlert;
        static Sound sndScorpionAlert;
        static Sound sndSkeletonAlert;
        static Sound sndSlimeAlert;
        static Sound sndHydraShoot;
        static Sound sndHydraExplode;
        static Sound sndSwing;
        static Sound sndAttack;
        static Sound sndHeroLevel;
        static Sound sndHeroDie;
        static Sound sndHeroWin;
        static Sound sndHeroEquip;
        static Sound sndPotion;

        //Static Item Initialization Function
        static void initializeItems();

        //Static Sound Initialization Function
        static void soundLoad();

        //Constructor(4 argument version)
        Dungeon(bool& winToggle,bool& dieToggle,const bool create,const std::string filename,const std::string tilesetFileName,const unsigned int textureWidth,
            const unsigned int textureHeight,const unsigned int tileSize);

        //Member Filename Mutator
        void setFilename(const std::string filename);

        //Member Filename Accessor
        std::string getFilename() const;

        //Member View Entity Mutator
        void setViewEntity(Entity& viewEntity);

        //Member View Object Accessor
        Entity* getViewEntity() const;

        //Member Chest Push Back Function
        void pushChest(const Chest& chest);

        //Member Chest Get Function
        Chest& getChest(const unsigned int index);

        //Member Chest Erase Function
        void eraseChest(const unsigned int index);

        //Member Chest Size Accessor
        unsigned int sizeChest();

        //Member Enemy Push Back Function
        void pushEnemy(const Enemy& enemy);

        //Member Enemy Get Function
        Enemy& getEnemy(const unsigned int index);

        //Member Enemy Erase Function
        void eraseEnemy(const unsigned int index);

        //Member Enemy Size Accessor
        unsigned int sizeEnemy();

        //Member Fireball Push Back Function
        void pushFireball(const Fireball& fireball);

        //Member Fireball Get Function
        Fireball& getFireball(const unsigned int index);

        //Member Fireball Erase Function
        void eraseFireball(const unsigned int index);

        //Member Fireball Size Accessor
        unsigned int sizeFireball();

        //Member Hero Push Back Function
        void pushHero(const Hero& hero);

        //Member Hero Get Function
        Hero& getHero(const unsigned int index);

        //Member Hero Erase Function
        void eraseHero(const unsigned int index);

        //Member Hero Size Accessor
        unsigned int sizeHero();

        //Member Hydra Push Back Function
        void pushHydra(const Hydra& hydra);

        //Member Hydra Get Function
        Hydra& getHydra(const unsigned int index);

        //Member Hydra Erase Function
        void eraseHydra(const unsigned int index);

        //Member Hydra Size Accessor
        unsigned int sizeHydra();

        //Member Update Function
        void update();

        //Member Draw Function
        void draw(const unsigned int viewWidth,const unsigned int viewHeight,const Text& font);

        //Member Add Book Function
        void addBook();

        //Member Book Accessor
        int numBooks() const;

        //Member Save Function
        void save();

        //Member Destroy Function
        void destroy();

    private:
        //Member Variables
        bool* _winToggle;
        bool* _dieToggle;
        bool _destroy;
        std::string _filename;
        unsigned int _textureID;
        double _textureWidth;
        double _textureHeight;
        double _tileSize;
        int _numBooks;
        Entity* _viewEntity;
        BitVec _mapVec;
        BitVec _colVec;
        std::vector<Chest> _chests;
        std::vector<Enemy> _enemies;
        std::vector<Fireball> _fireballs;
        std::vector<Hero> _heros;
        std::vector<Hydra> _hydras;
};

#endif
