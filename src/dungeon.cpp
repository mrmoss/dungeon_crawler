//dungeon.cpp
//Created By:  Mike Moss and Charlie Carlson
//Description:  Dungeon source.
//Date:  2011

//Definitions for "dungeon.h"
#include "dungeon.h"

//Algorithm Header
#include <algorithm>

//Random Dungeon Defines
#define padding 5
#define roomSize 10
#define roomExpand 20
#define trailSize 8
#define trailExpand 12
#define roomNum 50

//Hero Item Load Macro
#define heroLoadEquip(a)                                \
if(i##a>=0)                                             \
{                                                       \
    for(unsigned int jj=0;jj<h.Inventory().size();++jj) \
    {                                                   \
        if(h.Inventory()[jj]==Items[i##a])              \
        {                                               \
            h.setI##a(&h.Inventory()[jj]);              \
            break;                                      \
        }                                               \
    }                                                   \
}                                                       \

//Random Dungeon Pos Class
class Pos
{
    public:
        Pos(const int _x,const int _y):x(_x),y(_y)
        {}

        int x;
        int y;
};

//Random Dungeon Comparison Class
bool posCmp(const Pos& lhs,const Pos& rhs)
{
    return ((lhs.x<rhs.x&&lhs.y<=rhs.y)||(lhs.x==rhs.x&&lhs.y<rhs.y));
}

//Random Dungeon Create Room Function
void createRoom(BitVec& map,const Pos& pos,const int size)
{
    if(size<=0)
    {
        throw std::runtime_error("Dungeon(RDG) - Problem creating dungeon!!!");
    }

    int newRoomSize=size-rand()%size;

    for(int yy=(newRoomSize/2);yy>=0;--yy)
    {
        for(int xx=0;xx<=(newRoomSize/2)-yy;++xx)
        {
            map.set(pos.x+xx,pos.y+yy,0);
            map.set(pos.x+xx,pos.y-yy,0);
            map.set(pos.x-xx,pos.y+yy,0);
            map.set(pos.x-xx,pos.y-yy,0);
        }
    }
}

//Random Dungeon Create Trail Function
void createTrail(BitVec& map,const Pos& pos1,const Pos& pos2)
{
    int cx=pos1.x;
    int cy=pos1.y;

    while(!(cx==pos2.x&&cy==pos2.y))
    {
        int newTrailSize=trailSize+(rand()%trailExpand)-(rand()%(trailExpand*2));

        if(newTrailSize<1)
        {
            newTrailSize=1+(rand()%trailExpand);
        }

        createRoom(map,Pos(cx,cy),newTrailSize);

        if(cx<pos2.x)
        {
            ++cx;
        }
        else if(cx>pos2.x)
        {
            --cx;
        }
        else if(cy<pos2.y)
        {
            ++cy;
        }
        else if(cy>pos2.y)
        {
            --cy;
        }
    }
}

//Random Dungeon Function
void randomDungeon(BitVec& map)
{
    //Rooms Vector
    std::vector<Pos> rooms;

    //Size Variables
    int sX=static_cast<unsigned int>(map.sizeX());
    int sY=static_cast<unsigned int>(map.sizeY());

    //Create Big Rooms
    for(int ii=0;ii<roomNum;++ii)
    {
        int rX=padding+(roomSize/2)+rand()%(sX-(padding+(roomSize/2))*2);
        int rY=padding+(roomSize/2)+rand()%(sY-(padding+(roomSize/2))*2);
        int dX=-rand()%roomExpand-rand()%(roomExpand*2);
        int dY=rand()%roomExpand-rand()%(roomExpand*2);

        for(int ii=0;ii<=abs(dX);++ii)
        {
            if(dX<0&&rX-ii>padding+(roomSize/2)+1)
            {
                createRoom(map,Pos(rX-ii,rY),roomSize);
            }
            else if(dX>0&&rX+ii<sX-(padding+((roomSize/2))*2)-1)
            {
                createRoom(map,Pos(rX+ii,rY),roomSize);
            }
        }

        for(int ii=0;ii<=abs(dY);++ii)
        {
            if(dY<0&&rY-ii>padding+(roomSize/2)+1)
            {
                createRoom(map,Pos(rX,rY-ii),roomSize);
            }
            else if(dY>0&&rY+ii<sY-(padding+((roomSize/2))*2)-1)
            {
                createRoom(map,Pos(rX,rY+ii),roomSize);
            }
        }

        rooms.push_back(Pos(rX,rY));
        createRoom(map,Pos(rX,rY),roomSize);
    }

    //Sort Rooms (So the Trails are Created Correctly)
    std::sort(rooms.begin(),rooms.end(),posCmp);

    //Create Trails Between Rooms
    for(unsigned int ii=1;ii<rooms.size();++ii)
    {
        createTrail(map,rooms[ii-1],rooms[ii]);
    }

    //Fix Diagnol Bugs
    for(int yy=2;yy<sY-4;++yy)
    {
        for(int xx=2;xx<sX-2;++xx)
        {
            if(xx<sX-2&&yy<sY-2)
            {
                if(map.get(xx,yy)==0&&map.get(xx+1,yy)==1&&map.get(xx,yy+1)==1&&map.get(xx+1,yy+1)==0)
                {
                    map.set(xx+1,yy,0);
                    map.set(xx,yy+1,0);
                }

                if(map.get(xx,yy)==1&&map.get(xx+1,yy)==0&&map.get(xx,yy+1)==0&&map.get(xx+1,yy+1)==1)
                {
                    map.set(xx,yy,0);
                    map.set(xx+1,yy+1,0);
                }
            }
        }
    }

    //Fix Wall Height Bugs
    for(int yy=2;yy<sY-4;++yy)
    {
        for(int xx=2;xx<sX-2;++xx)
        {
            if(xx<sX-2&&yy<sY-2)
            {
                if(map.get(xx,yy)==0&&map.get(xx+1,yy)==1&&map.get(xx,yy+1)==1&&map.get(xx+1,yy+1)==0)
                {
                    map.set(xx+1,yy,0);
                    map.set(xx,yy+1,0);
                }
                else if(map.get(xx,yy)==1&&map.get(xx+1,yy)==0&&map.get(xx,yy+1)==0&&map.get(xx+1,yy+1)==1)
                {
                    map.set(xx,yy,0);
                    map.set(xx+1,yy+1,0);
                }

                if(map.get(xx,yy)==0&&map.get(xx,yy+1)==1&&map.get(xx,yy+2)==1&&map.get(xx,yy+3)==0)
                {
                    map.set(xx,yy+1,0);
                    map.set(xx,yy+2,0);
                }
                else if(map.get(xx,yy)==0&&map.get(xx,yy+1)==1&&map.get(xx,yy+2)==1&&map.get(xx,yy+3)==1&&map.get(xx,yy+4)==0)
                {
                    map.set(xx,yy+1,0);
                    map.set(xx,yy+2,0);
                    map.set(xx,yy+3,0);
                }
            }
        }
    }
}

//Dungeon Class Static Member Variables
std::vector<Item> Dungeon::Items;
Sound Dungeon::sndChestOpen;
Sound Dungeon::sndChestBook;
Sound Dungeon::sndBatAlert;
Sound Dungeon::sndDemonAlert;
Sound Dungeon::sndGhostAlert;
Sound Dungeon::sndScorpionAlert;
Sound Dungeon::sndSkeletonAlert;
Sound Dungeon::sndSlimeAlert;
Sound Dungeon::sndHydraShoot;
Sound Dungeon::sndHydraExplode;
Sound Dungeon::sndSwing;
Sound Dungeon::sndAttack;
Sound Dungeon::sndHeroLevel;
Sound Dungeon::sndHeroDie;
Sound Dungeon::sndHeroWin;
Sound Dungeon::sndHeroEquip;
Sound Dungeon::sndPotion;

//Dungeon Class Static Item Initialization Function
//ONLY PUT DAMAGE ON WEAPONS!!!  OR BAD THINGS WILL HAPPEN!!!
void Dungeon::initializeItems()
{
    Items.push_back(Item("BOOK OF ORION THE SORCERER","QUEST ITEM.","q",0.0,0));
    Items.push_back(Item("HEALING POTION","HEALS SOME LIFE.","cl10",0.0,1));
    Items.push_back(Item("SUPER HEALING POTION","HEALS A LOT OF LIFE.","cl50",0.0,2));
    Items.push_back(Item("HELM OF MIGHT","HELM IMBUED WITH STRENGTH.","hm1",0.0,12));
    Items.push_back(Item("HELM OF SPEED","HELM IMBUED WITH SPEED.","hv1",0.0,10));
    Items.push_back(Item("HELM OF HEALTH","HELM IMBUED WITH HEALTH.","hh1",0.0,11));
    Items.push_back(Item("IRON SWORD","SWORD MADE OF IRON.","wt3d8",0.0,18));
    Items.push_back(Item("IRON ARMOR","ARMOR MADE OF IRON.","av-1h1L20",0.0,7));
    Items.push_back(Item("IRON FLAIL","FLAIL MADE OF IRON.","wt2d12",0.0,24));
    Items.push_back(Item("IRON AXE","AXE MADE OF IRON.","wt1d12",0.0,21));
    Items.push_back(Item("AMULET OF LESS PAIN","IT'S LIKE ASPRIN!","jL40",0.0,14));
}

//Dungeon Class Static Sound Initialization Function
void Dungeon::soundLoad()
{
    sndChestOpen=Sound("sounds/chest.wav",false,0.7);
    sndChestBook=Sound("sounds/book.wav",false,0.7);
    sndBatAlert=Sound("sounds/bat.wav",false,0.7);
    sndDemonAlert=Sound("sounds/demon.wav",false,0.7);
    sndGhostAlert=Sound("sounds/ghost.wav",false,0.7);
    sndScorpionAlert=Sound("sounds/scorpion.wav",false,0.7);
    sndSkeletonAlert=Sound("sounds/skeleton.wav",false,0.7);
    sndSlimeAlert=Sound("sounds/slime.wav",false,0.7);
    sndHydraShoot=Sound("sounds/fireball.wav",false,0.7);
    sndHydraExplode=Sound("sounds/explode.wav",false,0.7);
    sndSwing=Sound("sounds/swing.wav",false,0.7);
    sndAttack=Sound("sounds/hit.wav",false,0.7);
    sndHeroLevel=Sound("sounds/level.wav",false,1.0);
    sndHeroDie=Sound("sounds/die.wav",false,0.7);
    sndHeroWin=Sound("sounds/win.wav",false,1.0);
    sndHeroEquip=Sound("sounds/equip.wav",false,0.7);
    sndPotion=Sound("sounds/potion.wav",false,0.7);
}

//Dungeon Class Constructor(4 argument version)
Dungeon::Dungeon(bool& winToggle,bool& dieToggle,const bool create,const std::string filename,const std::string tilesetFileName,const unsigned int textureWidth,
    const unsigned int textureHeight,const unsigned int tileSize):_winToggle(&winToggle),_dieToggle(&dieToggle),_destroy(false),_filename(filename),
    _textureID(loadBMP(tilesetFileName.c_str(),false)),_textureWidth(textureWidth),_textureHeight(textureHeight),
    _tileSize(static_cast<double>(tileSize)),_numBooks(0),_viewEntity(NULL)
{
    //Check Texture Dimensions
    if(_textureWidth<2||_textureHeight<2)
    {
        throw std::runtime_error("Dungeon - Invalid texture dimensions!!!");
    }

    //Check Texture Size
    if(_tileSize<2)
    {
        throw std::runtime_error("Dungeon - Invalid size dimensions!!!");
    }

    //Create or Load Map
    if(create)
    {
        //New Map Size
        int mapSizeX=1000;
        int mapSizeY=1000;

        //Vector of the Positions of Chests with Books
        std::vector<Pos> bookPos;

        //Create Map Vector
        _mapVec=BitVec(mapSizeX,mapSizeY,true);

        //Create Collision Vector
        _colVec=BitVec(mapSizeX,mapSizeY,false);

        //Create Random Dungeon
        randomDungeon(_mapVec);

        //Find Place for Player and Place Enemies
        bool found=false;

        for(unsigned int yy=5;yy<_mapVec.sizeY()-5;++yy)
        {
            for(unsigned int xx=5;xx<_mapVec.sizeX()-5;++xx)
            {
                if(_mapVec.get(xx,yy)==0&&_mapVec.get(xx,yy-1)==0&&_mapVec.get(xx,yy-2)==0&&_mapVec.get(xx,yy-3)==0&&_mapVec.get(xx,yy-4)==0&&
                    _colVec.get(xx,yy)==0)
                {
                    if(!found)
                    {
                        Hero h(xx*16.0,yy*16.0,3,3,3);
                        pushHero(h);
                        setViewEntity(_heros[_heros.size()-1]);
                        found=true;
                    }
                    else if(rand()%100>95)
                    {
                        bool pass=true;

                        for(unsigned int ii=0;ii<_heros.size();++ii)
                        {
                            if(distance(_heros[ii].XT(),_heros[ii].YT(),xx,yy)<30)
                            {
                                pass=false;
                                break;
                            }
                        }

                        if(pass)
                        {
                            pushEnemy(Enemy(xx*16.0,yy*16.0,rand()%13));
                        }
                    }
                }
            }
        }

        if(!found)
        {
            throw std::logic_error("Dungeon(CTOR) - This shouldn't have happened!!!");
        }

        //Create Hydras
        while(_hydras.size()<10)
        {
            int x=5+rand()%_mapVec.sizeX()-5;
            int y=5+rand()%_mapVec.sizeY()-5;

            if(_mapVec.get(x,y)==0&&_mapVec.get(x+1,y)==0&&_colVec.get(x,y)==0&&_colVec.get(x+1,y)==0)
            {
                pushHydra(Hydra(x*16.0,y*16.0,rand()%2));
            }
        }

        //Create Chests with Books
        int numBooks=0;

        while(numBooks<7)
        {
            int x=5+rand()%_mapVec.sizeX()-5;
            int y=5+rand()%_mapVec.sizeY()-5;

            if(_mapVec.get(x,y)==0&&_mapVec.get(x,y-1)==1&&_mapVec.get(x,y+1)==0&&_colVec.get(x,y)==0)
            {
                bool pass=true;

                for(unsigned int ii=0;ii<_heros.size();++ii)
                {
                    if(distance(x,y,_heros[ii].XT(),_heros[ii].YT())<10)
                    {
                        pass=false;
                        break;
                    }
                }

                if(pass)
                {
                    pushChest(Chest(x*16.0,y*16.0,true));
                    ++numBooks;
                }
            }
        }

        //Create Chests
        unsigned int numChests=250+rand()%1000;

        while(_chests.size()<numChests)
        {
            int x=5+rand()%_mapVec.sizeX()-5;
            int y=5+rand()%_mapVec.sizeY()-5;

            if(_mapVec.get(x,y)==0&&_mapVec.get(x,y-1)==1&&_mapVec.get(x,y+1)==0&&_colVec.get(x,y)==0)
            {
                pushChest(Chest(x*16.0,y*16.0,false));
            }
        }
    }
    else
    {
        //Load Map From File
        std::ifstream istr(std::string(_filename).c_str());

        //Check Map File
        if(!istr)
        {
            throw std::runtime_error("Dungeon - Map file does not exist!!!");
        }

        //Read in Map File Dimensions
        int mapSizeX;
        int mapSizeY;
        istr>>mapSizeX;
        istr>>mapSizeY;

        //Check Map File Dimensions
        if(mapSizeX<2||mapSizeY<2)
        {
            throw std::runtime_error("Dungeon - Invalid map dimensions!!!");
        }

        //Create Map Vector
        _mapVec=BitVec(mapSizeX,mapSizeY,true);

        //Create Collision Vector
        _colVec=BitVec(mapSizeX,mapSizeY,false);

        //Read in Map File
        int bytes;

        for(unsigned int ii=0;ii<_mapVec.size();++ii)
        {
            istr>>bytes;
            _mapVec.setInt(ii,bytes);
        }

        //Read in Chests
        unsigned int numChests;
        istr>>numChests;

        for(unsigned int ii=0;ii<numChests;++ii)
        {
            double x;
            double y;
            bool open;
            bool hasBook;

            istr>>x;
            istr>>y;
            istr>>open;
            istr>>hasBook;

            Chest c(x,y,hasBook);
            c.setOpen(open,*this,false);
            pushChest(c);
        }

        //Read in Enemies
        unsigned int numEnemies;
        istr>>numEnemies;

        for(unsigned int ii=0;ii<numEnemies;++ii)
        {
            bool dead;
            bool moved;
            bool attacking;
            int currentTime;
            unsigned int type;
            unsigned int dir;
            unsigned int xto;
            unsigned int yto;
            double x;
            double y;
            int life;
            double red;
            double green;
            double blue;
            double alpha;
            unsigned int px;
            unsigned int py;
            bool patrolling;
            std::string patrol;
            std::string table;

            istr>>dead;
            istr>>moved;
            istr>>attacking;
            istr>>currentTime;
            istr>>type;
            istr>>dir;
            istr>>xto;
            istr>>yto;
            istr>>x;
            istr>>y;
            istr>>life;
            istr>>red;
            istr>>green;
            istr>>blue;
            istr>>alpha;
            istr>>px;
            istr>>py;
            istr>>patrolling;
            istr>>patrol;
            istr>>table;

            Enemy e(x,y,type);
            e.setDead(dead);
            e.setMoved(moved);
            e.setAttacking(attacking,0);
            e.setXT(xto);
            e.setYT(yto);
            e.setLife(life);
            e.setDirection(dir);
            e.setRGBA(red,green,blue,alpha);
            e.setPX(px);
            e.setPY(py);
            e.setPatrolling(patrolling);
            e.setTables(patrol,table);

            pushEnemy(e);
        }

        //Read in Fireballs
        unsigned int numFireballs;
        istr>>numFireballs;

        for(unsigned int ii=0;ii<numFireballs;++ii)
        {
            double x;
            double y;
            double r;
            unsigned int current;

            istr>>x;
            istr>>y;
            istr>>r;
            istr>>current;

            pushFireball(Fireball(x,y,r,current));
        }

        //Read in Heros
        unsigned int numHeros;
        istr>>numHeros;

        for(unsigned int ii=0;ii<numHeros;++ii)
        {
            bool dead;
            int xp;
            int ap;
            bool moved;
            bool attacking;
            int currentTime;
            unsigned int weapon;
            unsigned int dir;
            unsigned int xto;
            unsigned int yto;
            double x;
            double y;
            int might;
            int vigor;
            int heart;
            int life;
            double red;
            double green;
            double blue;
            double alpha;
            unsigned int numItems;
            int iArmor;
            int iHelm;
            int iJewelry;
            int iWeapon;

            istr>>dead;
            istr>>xp;
            istr>>ap;
            istr>>moved;
            istr>>attacking;
            istr>>currentTime;
            istr>>weapon;
            istr>>dir;
            istr>>xto;
            istr>>yto;
            istr>>x;
            istr>>y;
            istr>>might;
            istr>>vigor;
            istr>>heart;
            istr>>life;
            istr>>red;
            istr>>green;
            istr>>alpha;
            istr>>blue;
            istr>>numItems;

            Hero h(x,y,might,vigor,heart);
            h.setDead(dead);
            h.addXP(xp);
            h.setAP(ap);
            h.setMoved(moved);
            h.setAttacking(attacking,currentTime);
            h.setXT(xto);
            h.setYT(yto);
            h.setLife(life);
            h.setDirection(dir);
            h.setWeapon(weapon);
            h.setRGBA(red,green,blue,alpha);

            for(unsigned int jj=0;jj<numItems;++jj)
            {
                unsigned int item;
                istr>>item;
                h.addItem(Items[item],*this);
            }

            istr>>iArmor;
            istr>>iHelm;
            istr>>iJewelry;
            istr>>iWeapon;

            heroLoadEquip(Armor);
            heroLoadEquip(Helm);
            heroLoadEquip(Jewelry);
            heroLoadEquip(Weapon);

            pushHero(h);
            setViewEntity(getHero(sizeHero()-1));
        }

        //Read in Hydras
        unsigned int numHydras;
        istr>>numHydras;

        for(unsigned int ii=0;ii<numHydras;++ii)
        {
            bool dead;
            bool moved;
            unsigned int type;
            unsigned int xto;
            unsigned int yto;
            double x;
            double y;
            int life;
            double red;
            double green;
            double blue;
            double alpha;
            std::string patrol;
            std::string table;

            istr>>dead;
            istr>>moved;
            istr>>type;
            istr>>xto;
            istr>>yto;
            istr>>x;
            istr>>y;
            istr>>life;
            istr>>red;
            istr>>green;
            istr>>blue;
            istr>>alpha;
            istr>>patrol;
            istr>>table;

            Hydra h(x,y,type);
            h.setDead(dead);
            h.setMoved(moved);
            h.setXT(xto);
            h.setYT(yto);
            h.setLife(life);
            h.setRGBA(red,green,blue,alpha);
            h.setTables(patrol,table);

            pushHydra(h);
        }

        //Read in Books
        istr>>_numBooks;

        //Close Map File
        istr.close();
    }
}

//Dungeon Class Member Filename Mutator
void Dungeon::setFilename(const std::string filename)
{
    _filename=filename;
}

//Dungeon Class Member Filename Accessor
std::string Dungeon::getFilename() const
{
    return _filename;
}

//Dungeon Class Member View Entity Mutator
void Dungeon::setViewEntity(Entity& viewEntity)
{
    _viewEntity=&viewEntity;
}

//Dungeon Class Member View Object Accessor
Entity* Dungeon::getViewEntity() const
{
    return _viewEntity;
}

//Dungeon Class Member Chest Push Back Function
void Dungeon::pushChest(const Chest& chest)
{
    _chests.push_back(Chest(chest));
    _colVec.set(static_cast<int>(chest.X()/chest.gridSize()),static_cast<int>(chest.Y()/chest.gridSize()),1);
}

//Dungeon Class Member Chest Get Function
Chest& Dungeon::getChest(const unsigned int index)
{
    return _chests[index];
}

//Dungeon Class Member Chest Erase Function
void Dungeon::eraseChest(const unsigned int index)
{
    _colVec.set(static_cast<int>(_chests[index].X())/_chests[index].gridSize(),static_cast<int>(_chests[index].Y())/_chests[index].gridSize(),0);
    _chests.erase(_chests.begin()+index);
}

//Dungeon Class Member Chest Size Accessor
unsigned int Dungeon::sizeChest()
{
    return _chests.size();
}

//Dungeon Class Member Enemy Push Back Function
void Dungeon::pushEnemy(const Enemy& enemy)
{
    _enemies.push_back(Enemy(enemy));

    if(enemy.getType()!=0&&enemy.getType()!=1)
    {
        _colVec.set(enemy.XT(),enemy.YT(),1);
    }
}

//Dungeon Class Member Enemy Get Function
Enemy& Dungeon::getEnemy(const unsigned int index)
{
    return _enemies[index];
}

//Dungeon Class Member Enemy Erase Function
void Dungeon::eraseEnemy(const unsigned int index)
{
    if(_enemies[index].getType()!=0&&_enemies[index].getType()!=1)
    {
        _colVec.set(_enemies[index].XT(),_enemies[index].YT(),0);
    }

    _enemies.erase(_enemies.begin()+index);
}

//Dungeon Class Member Enemy Size Accessor
unsigned int Dungeon::sizeEnemy()
{
    return _enemies.size();
}

//Dungeon Class Member Fireball Push Back Function
void Dungeon::pushFireball(const Fireball& fireball)
{
    _fireballs.push_back(Fireball(fireball));
}

//Dungeon Class Member Fireball Get Function
Fireball& Dungeon::getFireball(const unsigned int index)
{
    return _fireballs[index];
}

//Dungeon Class Member Fireball Erase Function
void Dungeon::eraseFireball(const unsigned int index)
{
    _fireballs.erase(_fireballs.begin()+index);
}

//Dungeon Class Member Fireball Size Accessor
unsigned int Dungeon::sizeFireball()
{
    return _fireballs.size();
}

//Dungeon Class Member Hero Push Back Function
void Dungeon::pushHero(const Hero& hero)
{
    _heros.push_back(Hero(hero));
    _colVec.set(hero.XT(),hero.YT(),true);
}

//Dungeon Class Member Hero Get Function
Hero& Dungeon::getHero(const unsigned int index)
{
    return _heros[index];
}

//Dungeon Class Member Hero Erase Function
void Dungeon::eraseHero(const unsigned int index)
{
    _colVec.set(_heros[index].XT(),_heros[index].YT(),false);
    _heros.erase(_heros.begin()+index);
}

//Dungeon Class Member Hero Size Accessor
unsigned int Dungeon::sizeHero()
{
    return _heros.size();
}

//Dungeon Class Member Hydra Push Back Function
void Dungeon::pushHydra(const Hydra& hydra)
{
    _hydras.push_back(Hydra(hydra));
    _colVec.set(hydra.XT(),hydra.YT(),1);
    _colVec.set(hydra.XT()+1,hydra.YT(),1);
}

//Dungeon Class Member Hydra Get Function
Hydra& Dungeon::getHydra(const unsigned int index)
{
    return _hydras[index];
}

//Dungeon Class Member Hydra Erase Function
void Dungeon::eraseHydra(const unsigned int index)
{
    _colVec.set(_hydras[index].XT(),_hydras[index].YT(),0);
    _colVec.set(_hydras[index].XT()+1,_hydras[index].YT(),0);
    _hydras.erase(_hydras.begin()+index);
}

//Dungeon Class Member Hydra Size Accessor
unsigned int Dungeon::sizeHydra()
{
    return _hydras.size();
}

//Dungeon Class Member Update Function
void Dungeon::update()
{
    //Check Books
    if(_numBooks==7)
    {
        ++_numBooks;
        save();
        sndHeroWin.play();

        for(unsigned int ii=0;ii<_heros.size();++ii)
        {
            if(!_heros[ii].Dead())
            {
                _heros[ii].setWon(1);
            }
        }
    }

    //Update Enemies
    if(_viewEntity!=NULL)
    {
        for(unsigned int ii=0;ii<_enemies.size();++ii)
        {
            if(distance(_viewEntity->XT(),_viewEntity->YT(),_enemies[ii].XT(),_enemies[ii].YT())<60)
            {
                _enemies[ii].update(_mapVec,_colVec,*this);
            }
        }
    }

    //Update Fireballs
    for(unsigned int ii=0;ii<_fireballs.size();++ii)
    {
        _fireballs[ii].update(*this,_mapVec);
    }

    //Update Heros
    for(unsigned int ii=0;ii<_heros.size();++ii)
    {
        _heros[ii].update(_mapVec,_colVec,*this);
    }

    //Update Hydras
    if(_viewEntity!=NULL)
    {
        for(unsigned int ii=0;ii<_hydras.size();++ii)
        {
            if(distance(_viewEntity->XT(),_viewEntity->YT(),_hydras[ii].XT(),_hydras[ii].YT())<60)
            {
                 _hydras[ii].update(_mapVec,_colVec,*this);
            }
        }
    }

    //Cleanup Enemies
    bool enemyCleanedup=false;

    while(!enemyCleanedup)
    {
        enemyCleanedup=true;

        for(unsigned int ii=0;ii<_enemies.size();++ii)
        {
            if(_enemies[ii].Dead())
            {
                eraseEnemy(ii);
                enemyCleanedup=false;
                break;
            }
        }
    }

    //Cleanup Fireballs
    bool fireballCleanedup=false;

    while(!fireballCleanedup)
    {
        fireballCleanedup=true;

        for(unsigned int ii=0;ii<_fireballs.size();++ii)
        {
            if(_fireballs[ii].destroy())
            {
                eraseFireball(ii);
                fireballCleanedup=false;
                break;
            }
        }
    }

    //End Game Scenario
    unsigned int numHerosDead=0;
    unsigned int numHerosWon=0;

    for(unsigned int ii=0;ii<_heros.size();++ii)
    {
        if(_heros[ii].Dead())
        {
            ++numHerosDead;
        }
        else if(_heros[ii].Won()==2)
        {
            ++numHerosWon;
        }
    }

    if(numHerosDead==_heros.size())
    {
        *_dieToggle=true;
    }
    else if(numHerosDead+numHerosWon==_heros.size())
    {
        *_winToggle=true;
    }

    //Cleanup Hydras
    bool hydraCleanedup=false;

    while(!hydraCleanedup)
    {
        hydraCleanedup=true;

        for(unsigned int ii=0;ii<_hydras.size();++ii)
        {
            if(_hydras[ii].Dead())
            {
                eraseHydra(ii);
                hydraCleanedup=false;
                break;
            }
        }
    }
}

//Dungeon Class Member Draw Function
void Dungeon::draw(const unsigned int viewWidth,const unsigned int viewHeight,const Text& font)
{
    //Determine Size of Slice
    double tileSliceX=1.0/(_textureWidth/_tileSize);
    double tileSliceY=1.0/(_textureHeight/_tileSize);

    //Draw Map Part of Current View
    int xMin=0;
    int xMax=0;
    int yMin=0;
    int yMax=0;

    if(_viewEntity!=NULL)
    {
        xMin=(_viewEntity->X()-viewWidth/2)/16;
        xMax=((_viewEntity->X()+viewWidth/2)/16)+1;
        yMin=(_viewEntity->Y()-viewHeight/2)/16;
        yMax=((_viewEntity->Y()+viewHeight/2)/16)+1;
    }

    if(xMin<0)
    {
        xMin=0;
    }

    if(xMax>static_cast<int>(_mapVec.sizeX()))
    {
        xMax=_mapVec.sizeX();
    }

    if(yMin<0)
    {
        yMin=0;
    }

    if(yMax>static_cast<int>(_mapVec.sizeY()))
    {
        yMax=_mapVec.sizeY();
    }

    //Enable Texture
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,_textureID);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    //Draw Quads With Rotation
    glPushMatrix();
    glBegin(GL_QUADS);

        //Figure Out Tile Texture
        for(unsigned int yy=static_cast<unsigned int>(yMin);yy<static_cast<unsigned int>(yMax);++yy)
        {
            for(unsigned int xx=static_cast<unsigned int>(xMin);xx<static_cast<unsigned int>(xMax);++xx)
            {
                int tileX;
                int tileY;

                if(_mapVec.get(xx,yy)==1)
                {
                    if(yy<_mapVec.sizeY()-1&&_mapVec.get(xx,yy+1)==0)
                    {
                        if(yy>0&&_mapVec.get(xx,yy-1)==0)
                        {
                            //Boulder
                            tileX=1;
                            tileY=0;
                        }
                        else
                        {
                            //Lower Wall
                            tileX=1;
                            tileY=1;
                        }
                    }
                    else if(yy<_mapVec.sizeY()-2&&_mapVec.get(xx,yy+2)==0)
                    {
                        //Lower Wall
                        tileX=1;
                        tileY=1;
                    }
                    else
                    {
                        //Wall Top
                        tileX=0;
                        tileY=1;
                    }
                }
                else
                {
                    //Ground
                    tileX=2;
                    tileY=1;
                }

                //Draw Tile
                glColor4f(1.0,1.0,1.0,1.0);
                glTexCoord2f((tileX*tileSliceX)+0.001,(tileY*tileSliceY)+0.001);
                glVertex2f(xx*_tileSize,(yy+1)*_tileSize);
                glTexCoord2f((((tileX+1)*tileSliceX))-0.001,(tileY*tileSliceY)+0.001);
                glVertex2f((xx+1)*_tileSize,(yy+1)*_tileSize);
                glTexCoord2f((((tileX+1)*tileSliceX))-0.001,(((tileY+1)*tileSliceY))-0.001);
                glVertex2f((xx+1)*_tileSize,yy*_tileSize);
                glTexCoord2f((tileX*tileSliceX)+0.001,(((tileY+1)*tileSliceY))-0.001);
                glVertex2f(xx*_tileSize,yy*_tileSize);
            }
        }

    //Done With Quads
    glEnd();
    glPopMatrix();

    //Disable Texture
    glDisable(GL_TEXTURE_2D);

    //Draw Chests
    for(unsigned int ii=0;ii<_chests.size();++ii)
    {
        if(_chests[ii].X()/_chests[ii].gridSize()>=xMin&&_chests[ii].X()/_chests[ii].gridSize()<xMax&&
            _chests[ii].Y()/_chests[ii].gridSize()>=yMin&&_chests[ii].Y()/_chests[ii].gridSize()<yMax)
        {
            _chests[ii].draw();
        }
    }

    //Draw Entities Based on Y
    int depth=yMin;

    while(depth<yMax)
    {
        //Draw Heros
        for(unsigned int ii=0;ii<_heros.size();++ii)
        {
            if(_heros[ii].YT()==depth&&_heros[ii].XT()>=xMin&&_heros[ii].XT()<xMax&&
                _heros[ii].YT()>=yMin&&_heros[ii].YT()<yMax)
            {
                _heros[ii].draw();
            }
        }

        //Draw Hydras
        for(unsigned int ii=0;ii<_hydras.size();++ii)
        {
            if(_hydras[ii].YT()==depth&&_hydras[ii].XT()+1>=xMin&&_hydras[ii].XT()<xMax&&
                _hydras[ii].YT()>=yMin&&_hydras[ii].YT()<yMax)
            {
                _hydras[ii].draw(*this);
            }
        }

        //Draw Enemies
        for(unsigned int ii=0;ii<_enemies.size();++ii)
        {
            if(_enemies[ii].YT()==depth&&_enemies[ii].XT()>=xMin&&_enemies[ii].XT()<xMax&&
                _enemies[ii].YT()>=yMin&&_enemies[ii].YT()<yMax)
            {
                if(_enemies[ii].getType()>1)
                {
                    _enemies[ii].draw();
                }
            }
        }

        ++depth;
    }

    //Draw Ghosts
    for(unsigned int ii=0;ii<_enemies.size();++ii)
    {
        if(_enemies[ii].getType()<2&&_enemies[ii].XT()>=xMin&&_enemies[ii].XT()<xMax&&
            _enemies[ii].YT()>=yMin&&_enemies[ii].YT()<yMax)
        {
            _enemies[ii].draw();
        }
    }

    //Draw Fireballs
    for(unsigned int ii=0;ii<_fireballs.size();++ii)
    {
        _fireballs[ii].draw();
    }

    //Draw Menus
    for(unsigned int ii=0;ii<_heros.size();++ii)
    {
        _heros[ii].drawMenu(viewWidth,viewHeight,_viewEntity->X()-viewWidth/2,_viewEntity->Y()-viewHeight/2,font,_numBooks);
    }

    //Destroy if Need Be
    if(_destroy)
    {
        *_dieToggle=true;
        _chests.clear();
        _enemies.clear();
        _fireballs.clear();
        _heros.clear();
        _hydras.clear();
        delete this;
    }
}

//Dungeon Class Member Add Book Function
void Dungeon::addBook()
{
    ++_numBooks;
}

//Dungeon Class Member Number of Books Accessor
int Dungeon::numBooks() const
{
    return _numBooks;
}

//Dungeon Class Member Save Function
void Dungeon::save()
{
    //Save Dungeon to File
    std::ofstream ostr(_filename.c_str());

        //Record Dungeon Map Dimensions to File
        ostr<<_mapVec.sizeX();
        ostr<<'\n';
        ostr<<_mapVec.sizeY();
        ostr<<'\n';

        //Record Dungeon Map to File
        for(unsigned int ii=0;ii<_mapVec.size();++ii)
        {
            ostr<<_mapVec.getInt(ii)<<'\n';
        }

        //Save Chests
        ostr<<_chests.size()<<'\n';

        for(unsigned int ii=0;ii<_chests.size();++ii)
        {
            ostr<<_chests[ii].X()<<'\n';
            ostr<<_chests[ii].Y()<<'\n';
            ostr<<_chests[ii].open()<<'\n';
            ostr<<_chests[ii].hasBook()<<'\n';
        }

        //Save Enemies
        ostr<<_enemies.size()<<'\n';

        for(unsigned int ii=0;ii<_enemies.size();++ii)
        {
            double red;
            double green;
            double blue;
            double alpha;
            _enemies[ii].getRGBA(red,green,blue,alpha);

            std::string patrol;
            std::string table;
            _enemies[ii].getTables(patrol,table);

            ostr<<_enemies[ii].Dead()<<'\n';
            ostr<<_enemies[ii].Moved()<<'\n';
            ostr<<_enemies[ii].Attacked()<<'\n';
            ostr<<_enemies[ii].AttackTime()<<'\n';
            ostr<<_enemies[ii].getType()<<'\n';
            ostr<<_enemies[ii].getDirection()<<'\n';
            ostr<<_enemies[ii].XT()<<'\n';
            ostr<<_enemies[ii].YT()<<'\n';
            ostr<<_enemies[ii].X()<<'\n';
            ostr<<_enemies[ii].Y()<<'\n';
            ostr<<_enemies[ii].Life()<<'\n';
            ostr<<red<<'\n';
            ostr<<green<<'\n';
            ostr<<blue<<'\n';
            ostr<<alpha<<'\n';
            ostr<<_enemies[ii].PX()<<'\n';
            ostr<<_enemies[ii].PY()<<'\n';
            ostr<<_enemies[ii].getPatrolling()<<'\n';
            ostr<<patrol<<'\n';
            ostr<<table<<'\n';
        }

        //Save Fireballs
        ostr<<_fireballs.size()<<'\n';

        for(unsigned int ii=0;ii<_fireballs.size();++ii)
        {
            ostr<<_fireballs[ii].X()<<'\n';
            ostr<<_fireballs[ii].Y()<<'\n';
            ostr<<_fireballs[ii].R()<<'\n';
            ostr<<_fireballs[ii].getTimerCurrent()<<'\n';
        }

        //Save Heros
        ostr<<_heros.size()<<'\n';

        for(unsigned int ii=0;ii<_heros.size();++ii)
        {
            double red;
            double green;
            double blue;
            double alpha;
            _heros[ii].getRGBA(red,green,blue,alpha);

            ostr<<_heros[ii].Dead()<<'\n';
            ostr<<_heros[ii].XP()<<'\n';
            ostr<<_heros[ii].getAP()<<'\n';
            ostr<<_heros[ii].Moved()<<'\n';
            ostr<<_heros[ii].Attacked()<<'\n';
            ostr<<_heros[ii].AttackTime()<<'\n';
            ostr<<_heros[ii].getWeapon()<<'\n';
            ostr<<_heros[ii].getDirection()<<'\n';
            ostr<<_heros[ii].XT()<<'\n';
            ostr<<_heros[ii].YT()<<'\n';
            ostr<<_heros[ii].X()<<'\n';
            ostr<<_heros[ii].Y()<<'\n';
            ostr<<_heros[ii].Might()<<'\n';
            ostr<<_heros[ii].Vigor()<<'\n';
            ostr<<_heros[ii].Heart()<<'\n';
            ostr<<_heros[ii].Life()<<'\n';
            ostr<<red<<'\n';
            ostr<<green<<'\n';
            ostr<<blue<<'\n';
            ostr<<alpha<<'\n';
            ostr<<_heros[ii].Inventory().size()<<'\n';

            for(unsigned int jj=0;jj<_heros[ii].Inventory().size();++jj)
            {
                for(unsigned int kk=0;kk<Items.size();++kk)
                {
                    if(_heros[ii].Inventory()[jj]==Items[kk])
                    {
                        ostr<<kk<<'\n';
                        break;
                    }
                }
            }

            //Armor
            if(_heros[ii].getIArmor()==NULL)
            {
                ostr<<-1<<'\n';
            }
            else
            {
                for(unsigned int jj=0;jj<Items.size();++jj)
                {
                    if(*_heros[ii].getIArmor()==Items[jj])
                    {
                        ostr<<jj<<'\n';
                        break;
                    }
                }
            }

            //Helm
            if(_heros[ii].getIHelm()==NULL)
            {
                ostr<<-1<<'\n';
            }
            else
            {
                for(unsigned int jj=0;jj<Items.size();++jj)
                {
                    if(*_heros[ii].getIHelm()==Items[jj])
                    {
                        ostr<<jj<<'\n';
                        break;
                    }
                }
            }

            //Jewelry
            if(_heros[ii].getIJewelry()==NULL)
            {
                ostr<<-1<<'\n';
            }
            else
            {
                for(unsigned int jj=0;jj<Items.size();++jj)
                {
                    if(*_heros[ii].getIJewelry()==Items[jj])
                    {
                        ostr<<jj<<'\n';
                        break;
                    }
                }
            }

            //Weapon
            if(_heros[ii].getIWeapon()==NULL)
            {
                ostr<<-1<<'\n';
            }
            else
            {
                for(unsigned int jj=0;jj<Items.size();++jj)
                {
                    if(*_heros[ii].getIWeapon()==Items[jj])
                    {
                        ostr<<jj<<'\n';
                        break;
                    }
                }
            }
        }

        //Save Hydras
        ostr<<_hydras.size()<<'\n';

        for(unsigned int ii=0;ii<_hydras.size();++ii)
        {
            double red;
            double green;
            double blue;
            double alpha;
            _hydras[ii].getRGBA(red,green,blue,alpha);

            std::string patrol;
            std::string table;
            _hydras[ii].getTables(patrol,table);

            if(patrol.size()<=0)
            {
                patrol+='s';
            }

            if(table.size()<=0)
            {
                table+='s';
            }

            ostr<<_hydras[ii].Dead()<<'\n';
            ostr<<_hydras[ii].Moved()<<'\n';
            ostr<<_hydras[ii].getType()<<'\n';
            ostr<<_hydras[ii].XT()<<'\n';
            ostr<<_hydras[ii].YT()<<'\n';
            ostr<<_hydras[ii].X()<<'\n';
            ostr<<_hydras[ii].Y()<<'\n';
            ostr<<_hydras[ii].Life()<<'\n';
            ostr<<red<<'\n';
            ostr<<green<<'\n';
            ostr<<blue<<'\n';
            ostr<<alpha<<'\n';
            ostr<<patrol<<'\n';
            ostr<<table<<'\n';
        }

        //Number of Books
        ostr<<_numBooks<<'\n';

    //Close File
    ostr.close();
}

//Dungeon Class Member Destroy Function
void Dungeon::destroy()
{
    _destroy=true;
}
