//Enemy.cpp
//Created By:  Mike Moss and Zack Willams
//Description:  Enemy source.
//Date:  2011

//Definitions for "enemy.h"
#include "enemy.h"

//Enemy Class Static Variables
unsigned int Enemy::_sprGhost;
unsigned int Enemy::_sprSpecter;
unsigned int Enemy::_sprSlime;
unsigned int Enemy::_sprOoze;
unsigned int Enemy::_sprBat;
unsigned int Enemy::_sprVampire;
unsigned int Enemy::_sprScorpion;
unsigned int Enemy::_sprStinger;
unsigned int Enemy::_sprSkeletonWhiteWalkNorth;
unsigned int Enemy::_sprSkeletonWhiteWalkEast;
unsigned int Enemy::_sprSkeletonWhiteWalkSouth;
unsigned int Enemy::_sprSkeletonWhiteWalkWest;
unsigned int Enemy::_sprSkeletonRedWalkNorth;
unsigned int Enemy::_sprSkeletonRedWalkEast;
unsigned int Enemy::_sprSkeletonRedWalkSouth;
unsigned int Enemy::_sprSkeletonRedWalkWest;
unsigned int Enemy::_sprSkeletonGoldWalkNorth;
unsigned int Enemy::_sprSkeletonGoldWalkEast;
unsigned int Enemy::_sprSkeletonGoldWalkSouth;
unsigned int Enemy::_sprSkeletonGoldWalkWest;
unsigned int Enemy::_sprImpWalkNorth;
unsigned int Enemy::_sprImpWalkEast;
unsigned int Enemy::_sprImpWalkSouth;
unsigned int Enemy::_sprImpWalkWest;
unsigned int Enemy::_sprDemonWalkNorth;
unsigned int Enemy::_sprDemonWalkEast;
unsigned int Enemy::_sprDemonWalkSouth;
unsigned int Enemy::_sprDemonWalkWest;

//Enemy Class Static Sprite Load Function
void Enemy::spriteLoad()
{
    _sprGhost=loadBMP("sprites/ghost.bmp");
    _sprSpecter=loadBMP("sprites/specter.bmp");
    _sprSlime=loadBMP("sprites/slime.bmp");
    _sprOoze=loadBMP("sprites/ooze.bmp");
    _sprBat=loadBMP("sprites/bat.bmp");
    _sprVampire=loadBMP("sprites/vampire.bmp");
    _sprScorpion=loadBMP("sprites/scorpion.bmp");
    _sprStinger=loadBMP("sprites/stinger.bmp");
    _sprSkeletonWhiteWalkNorth=loadBMP("sprites/skeletonWhiteWalkNorth.bmp");
    _sprSkeletonWhiteWalkEast=loadBMP("sprites/skeletonWhiteWalkEast.bmp");
    _sprSkeletonWhiteWalkSouth=loadBMP("sprites/skeletonWhiteWalkSouth.bmp");
    _sprSkeletonWhiteWalkWest=loadBMP("sprites/skeletonWhiteWalkWest.bmp");
    _sprSkeletonRedWalkNorth=loadBMP("sprites/skeletonRedWalkNorth.bmp");
    _sprSkeletonRedWalkEast=loadBMP("sprites/skeletonRedWalkEast.bmp");
    _sprSkeletonRedWalkSouth=loadBMP("sprites/skeletonRedWalkSouth.bmp");
    _sprSkeletonRedWalkWest=loadBMP("sprites/skeletonRedWalkWest.bmp");
    _sprSkeletonGoldWalkNorth=loadBMP("sprites/skeletonGoldWalkNorth.bmp");
    _sprSkeletonGoldWalkEast=loadBMP("sprites/skeletonGoldWalkEast.bmp");
    _sprSkeletonGoldWalkSouth=loadBMP("sprites/skeletonGoldWalkSouth.bmp");
    _sprSkeletonGoldWalkWest=loadBMP("sprites/skeletonGoldWalkWest.bmp");
    _sprImpWalkNorth=loadBMP("sprites/impWalkNorth.bmp");
    _sprImpWalkEast=loadBMP("sprites/impWalkEast.bmp");
    _sprImpWalkSouth=loadBMP("sprites/impWalkSouth.bmp");
    _sprImpWalkWest=loadBMP("sprites/impWalkWest.bmp");
    _sprDemonWalkNorth=loadBMP("sprites/demonWalkNorth.bmp");
    _sprDemonWalkEast=loadBMP("sprites/demonWalkEast.bmp");
    _sprDemonWalkSouth=loadBMP("sprites/demonWalkSouth.bmp");
    _sprDemonWalkWest=loadBMP("sprites/demonWalkWest.bmp");
}

//Enemy Class Constructor(Default and 2 argument version)
Enemy::Enemy(const double x,const double y,const unsigned int type):Entity(x,y),_chase(NULL),_px(_xto),_py(_yto),_attacking(false),
    _sprite(_sprGhost,2,32,16),_patrolling(true),_patrol("s"),_table("t"),_type(type)
{
    if(_type==0)
    {
        _sprite.setTexture(_sprGhost);
        setMight(3);
        setVigor(2);
        setHeart(4);
    }
    else if(_type==1)
    {
        _sprite.setTexture(_sprSpecter);
        setMight(5);
        setVigor(3);
        setHeart(5);
    }
    else if(_type==2)
    {
        _sprite.setTexture(_sprSlime);
        setMight(1);
        setVigor(1);
        setHeart(1);
    }
    else if(_type==3)
    {
        _sprite.setTexture(_sprOoze);
        setMight(2);
        setVigor(1);
        setHeart(3);
    }
    else if(_type==4)
    {
        _sprite.setTexture(_sprBat);
        setMight(1);
        setVigor(3);
        setHeart(1);
    }
    else if(_type==5)
    {
        _sprite.setTexture(_sprVampire);
        setMight(3);
        setVigor(6);
        setHeart(2);
    }
    else if(_type==6)
    {
        _sprite.setTexture(_sprScorpion);
        setMight(3);
        setVigor(1);
        setHeart(3);
    }
    else if(_type==7)
    {
        _sprite.setTexture(_sprStinger);
        setMight(4);
        setVigor(2);
        setHeart(5);
    }
    else if(_type==8)
    {
        _sprite.setTexture(_sprSkeletonWhiteWalkSouth);
        setMight(2);
        setVigor(1);
        setHeart(3);
    }
    else if(_type==9)
    {
        _sprite.setTexture(_sprSkeletonRedWalkSouth);
        setMight(4);
        setVigor(2);
        setHeart(5);
    }
    else if(_type==10)
    {
        _sprite.setTexture(_sprSkeletonGoldWalkSouth);
        setMight(6);
        setVigor(3);
        setHeart(7);
    }
    else if(_type==11)
    {
        _sprite.setTexture(_sprImpWalkSouth);
        setMight(7);
        setVigor(5);
        setHeart(8);
    }
    else if(_type==12)
    {
        _sprite.setTexture(_sprDemonWalkSouth);
        setMight(8);
        setVigor(8);
        setHeart(9);
    }
    else
    {
        throw std::runtime_error("Enemy - Invalid creation type!!!");
    }

    //Set Life to Full
    setLife(LifeMax());

    //Set Time
    _attackTimer=Timer(40/Speed()+1);

    //Patrol Creation
    if(true)
    {
        int patrolLength=8+rand()%8;

        for(int ii=0;ii<patrolLength;++ii)
        {
            //Random Direction
            int dir=rand()%4;

            switch(dir)
            {
                case 0:
                    _patrol+='e';
                    break;
                case 1:
                    _patrol+='n';
                    break;
                case 2:
                    _patrol+='w';
                    break;
                case 3:
                    _patrol+='s';
                    break;
                default:
                    _patrol+='e';
                    break;
            }
        }
    }
}

//Enemy Class Member Patrol X Mutator
void Enemy::setPX(const unsigned int px)
{
    _px=px;
}

//Enemy Class Member Patrol Y Mutator
void Enemy::setPY(const unsigned int py)
{
    _py=py;
}

//Enemy Class Member Patrol X Accessor
unsigned int Enemy::PX() const
{
    return _px;
}

//Enemy Class Member Patrol Y Accessor
unsigned int Enemy::PY() const
{
    return _py;
}

//SUPER FAST ATTACK BUG FIX
//Enemy Class Member Attacking Mutator
void Enemy::setAttacking(const bool attacking,const int currentTime)
{
    //_attacking=attacking;
    _attackTimer=Timer(40/Speed()+1);

    /*if(currentTime>0)
    {
        _attackTimer.setState(false);
    }*/

    //_attackTimer.setTime(currentTime);
}

//Enemy Class Member Attacked Accessor
bool Enemy::Attacked() const
{
    return _attacking;
}

//Enemy Class Member Attack Time Accessor
int Enemy::AttackTime() const
{
    return _attackTimer.current();
}

//Enemy Class Member Direction Mutator
void Enemy::setDirection(unsigned int dir)
{
    if(_type>=8)
    {
        if(dir==0)
        {
            if(_type==8)
            {
                _sprite.setTexture(_sprSkeletonWhiteWalkEast);
            }
            else if(_type==9)
            {
                _sprite.setTexture(_sprSkeletonRedWalkEast);
            }
            else if(_type==10)
            {
                _sprite.setTexture(_sprSkeletonGoldWalkEast);
            }
            else if(_type==11)
            {
                _sprite.setTexture(_sprImpWalkEast);
            }
            else if(_type==12)
            {
                _sprite.setTexture(_sprDemonWalkEast);
            }
        }
        else if(dir==1)
        {
            if(_type==8)
            {
                _sprite.setTexture(_sprSkeletonWhiteWalkNorth);
            }
            else if(_type==9)
            {
                _sprite.setTexture(_sprSkeletonRedWalkNorth);
            }
            else if(_type==10)
            {
                _sprite.setTexture(_sprSkeletonGoldWalkNorth);
            }
            else if(_type==11)
            {
                _sprite.setTexture(_sprImpWalkNorth);
            }
            else if(_type==12)
            {
                _sprite.setTexture(_sprDemonWalkNorth);
            }
        }
        else if(dir==2)
        {
            if(_type==8)
            {
                _sprite.setTexture(_sprSkeletonWhiteWalkWest);
            }
            else if(_type==9)
            {
                _sprite.setTexture(_sprSkeletonRedWalkWest);
            }
            else if(_type==10)
            {
                _sprite.setTexture(_sprSkeletonGoldWalkWest);
            }
            else if(_type==11)
            {
                _sprite.setTexture(_sprImpWalkWest);
            }
            else if(_type==12)
            {
                _sprite.setTexture(_sprDemonWalkWest);
            }
        }
        else if(dir==3)
        {
            if(_type==8)
            {
                _sprite.setTexture(_sprSkeletonWhiteWalkSouth);
            }
            else if(_type==9)
            {
                _sprite.setTexture(_sprSkeletonRedWalkSouth);
            }
            else if(_type==10)
            {
                _sprite.setTexture(_sprSkeletonGoldWalkSouth);
            }
            else if(_type==11)
            {
                _sprite.setTexture(_sprImpWalkSouth);
            }
            else if(_type==12)
            {
                _sprite.setTexture(_sprDemonWalkSouth);
            }
        }
        else
        {
            throw std::runtime_error("Enemy(dir) - Invalid direction!!!");
        }
    }
}

//Enemy Class Member Direction Accessor
unsigned int Enemy::getDirection() const
{
    if(_type<8||_sprite.texture()==_sprSkeletonWhiteWalkEast||_sprite.texture()==_sprSkeletonRedWalkEast||
        _sprite.texture()==_sprSkeletonGoldWalkEast||_sprite.texture()==_sprImpWalkEast||_sprite.texture()==_sprDemonWalkEast)
    {
        return 0;
    }
    else if(_sprite.texture()==_sprSkeletonWhiteWalkNorth||_sprite.texture()==_sprSkeletonRedWalkNorth||
        _sprite.texture()==_sprSkeletonGoldWalkNorth||_sprite.texture()==_sprImpWalkNorth||_sprite.texture()==_sprDemonWalkNorth)
    {
        return 1;
    }
    else if(_sprite.texture()==_sprSkeletonWhiteWalkWest||_sprite.texture()==_sprSkeletonRedWalkWest||
        _sprite.texture()==_sprSkeletonGoldWalkWest||_sprite.texture()==_sprImpWalkWest||_sprite.texture()==_sprDemonWalkWest)
    {
        return 2;
    }
    else if(_sprite.texture()==_sprSkeletonWhiteWalkSouth||_sprite.texture()==_sprSkeletonRedWalkSouth||
        _sprite.texture()==_sprSkeletonGoldWalkSouth||_sprite.texture()==_sprImpWalkSouth||_sprite.texture()==_sprDemonWalkSouth)
    {
        return 3;
    }

    throw std::runtime_error("Enemy(dir) - Invalid direction!!!");
}

//Enemy Class Member Type Accessor
unsigned int Enemy::getType() const
{
    return _type;
}

//Enemy Class Member Patrolling Mutator
void Enemy::setPatrolling(bool patrol)
{
    _patrolling=patrol;
}

//Enemy Class Member Patrolling Accessor
bool Enemy::getPatrolling() const
{
    return _patrolling;
}

//Enemy Class Member Tables Mutator
void Enemy::setTables(const std::string& patrol,const std::string& table)
{
    _patrol=patrol;
    _table=table;
}

//Enemy Class Member Tables Accessor
void Enemy::getTables(std::string& patrol,std::string& table)
{
    patrol=_patrol;
    table=_table;
}

//Enemy Class Member Update Function
void Enemy::update(BitVec& mapVec,BitVec& colVec,Dungeon& d)
{
    //If Dead
    if(_life<=0)
    {
        _colA-=0.05;

        if(_colA<=0.0)
        {
            setDead(true);
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

    //Set Direction
    if(_type>7&&_chase!=NULL&&distance(_chase->XT(),_chase->YT(),XT(),YT())<=1)
    {
        if(getDirection()!=0&&_chase->XT()>XT())
        {
            setDirection(0);
        }
        else if(getDirection()!=2&&_chase->XT()<XT())
        {
            setDirection(2);
        }
        else if(getDirection()!=3&&_chase->YT()>YT())
        {
            setDirection(3);
        }
        else if(getDirection()!=1&&_chase->YT()<YT())
        {
            setDirection(1);
        }
    }

    //Attack
    if(_chase!=NULL&&!Dead()&&!_attacking&&!Moved()&&!_attackTimer.state()&&distance(_chase->XT(),_chase->YT(),XT(),YT())<=1&&
        (XT()==_chase->XT()||YT()==_chase->YT())&&_chase->Life()>0&&Life()>0)
    {
        //Set Attack Variables
        _attacking=true;
        _attackTimer.reset();

        //Play Hit Sound
        if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
        {
            d.sndAttack.play();
        }

        //Attack Hero
        _chase->setLife(_chase->Life()-Damage());
        _chase->setRGBA(1.0,0.0,0.0,-1.0);

        //Check for Death
        if(_chase->Life()<=0)
        {
            //Play Death Sound
            d.sndHeroDie.play();
        }
    }

    //Movement
    if(!Dead()&&!_attacking)
    {
        //Determine Move
        if(_patrolling&&_table.size()<=1)
        {
            _table+=_patrol;
        }
        else if(_chase!=NULL&&_table.size()<=1)
        {
            if(_chase->XT()<XT())
            {
                _table+='w';
            }

            if(_chase->XT()>XT())
            {
                _table+='e';
            }

            if(_chase->YT()<YT())
            {
                _table+='n';
            }

            if(_chase->YT()>YT())
            {
                _table+='s';
            }

            //Stay Outside Player if Ghost
            if(_type<2)
            {
                if(XT()==_chase->XT()&&YT()==_chase->YT())
                {
                    int dir=rand()%4;

                    switch(dir)
                    {
                        case 0:
                            _table+='n';
                            break;
                        case 1:
                            _table+='w';
                            break;
                        case 2:
                            _table+='s';
                            break;
                        case 3:
                            _table+='e';
                            break;
                        default:
                            _table+='e';
                    }
                }
            }
        }

        //Move
        if(!Moved()&&!_attacking&&_table.size()>1)
        {
            char ch=_table[1];
            _table.erase(_table.begin()+1);

            if(ch=='e')
            {
                if(_type>1)
                {
                    if(mapVec.get(XT()+1,YT())==0&&colVec.get(XT()+1,YT())==0)
                    {
                        colVec.set(XT(),YT(),0);
                        addXT(1);
                        colVec.set(XT(),YT(),1);
                    }
                }
                else if(XT()+1<static_cast<int>(mapVec.sizeX()))
                {
                    addXT(1);
                }
            }
            else if(ch=='n')
            {
                if(_type>1)
                {
                    if(mapVec.get(XT(),YT()-1)==0&&colVec.get(XT(),YT()-1)==0)
                    {
                        colVec.set(XT(),YT(),0);
                        addYT(-1);
                        colVec.set(XT(),YT(),1);
                    }
                }
                else if(YT()-1>0)
                {
                    addYT(-1);
                }
            }
            else if(ch=='w')
            {
                if(_type>1)
                {
                    if(mapVec.get(XT()-1,YT())==0&&colVec.get(XT()-1,YT())==0)
                    {
                        colVec.set(XT(),YT(),0);
                        addXT(-1);
                        colVec.set(XT(),YT(),1);
                    }
                }
                else if(XT()-1>0)
                {
                    addXT(-1);
                }
            }
            else if(ch=='s')
            {
                if(_type>1)
                {
                    if(mapVec.get(XT(),YT()+1)==0&&colVec.get(XT(),YT()+1)==0)
                    {
                        colVec.set(XT(),YT(),0);
                        addYT(1);
                        colVec.set(XT(),YT(),1);
                    }
                }
                else if(YT()+1<static_cast<int>(mapVec.sizeY()))
                {
                    addYT(1);
                }
            }
        }

        //If Hero Comes into Range
        bool pass=true;

        for(unsigned int ii=0;ii<d.sizeHero();++ii)
        {
            if(d.getHero(ii).Life()>0&&d.getHero(ii).Won()!=1&&d.getHero(ii).Won()!=2&&distance(d.getHero(ii).XT(),d.getHero(ii).YT(),XT(),YT())<=5)
            {
                //Play Alert Sound
                if(_patrolling)
                {
                    if(distance(d.getViewEntity()->XT(),d.getViewEntity()->YT(),XT(),YT())<20)
                    {
                        if(_type==0||_type==1)
                        {
                            d.sndGhostAlert.play();
                        }
                        else if(_type==2||_type==3)
                        {
                            d.sndSlimeAlert.play();
                        }
                        else if(_type==4||_type==5)
                        {
                            d.sndBatAlert.play();
                        }
                        else if(_type==6||_type==7)
                        {
                            d.sndScorpionAlert.play();
                        }
                        else if(_type>7&&_type<11)
                        {
                            d.sndSkeletonAlert.play();
                        }
                        else if(_type==11||_type==12)
                        {
                            d.sndDemonAlert.play();
                        }
                    }
                }

                _table="s";
                _chase=&d.getHero(ii);

                _patrolling=false;
                pass=false;
                break;
            }
        }

        if(pass)
        {
            _patrolling=true;
            _chase=NULL;
        }
    }

    //Attack Timer Update
    if(Life()>0)
    {
        _attackTimer.update();

        if(_attackTimer.state())
        {
            _attacking=false;
        }
    }

    //Move on Grid
    moveOnGrid();

    //Grid Alignment Fix
    if(!Moved())
    {
        setX(gridize(X())*gridSize());
        setY(gridize(Y())*gridSize());
    }

    //Animations for Single Directional Enemies
    if(_type<8)
    {
        _sprite.update(Speed()*0.15);
    }

    //Attacking Fix
    if(!_attackTimer.state()&&_attacking)
    {
        _attacking=false;
    }
}

//Enemy Class Member Draw Function
void Enemy::draw()
{
    //Determine Alpha Value
    double alpha=0.3;

    if(_type==0||_type==1)
    {
        alpha=0.4;
    }
    else if(_type==2||_type==3)
    {
        alpha=0.3;
    }

    //Draw Sprite
    _sprite.draw(-1,_x+8.0,_y+8.0,_scaleX,_scaleY,_rot,_colA-alpha,_colR,_colG,_colB);

    //Draw Hit Effect
    Sprite hit(Entity::_sprHit,1,16,16);
    hit.draw(0,X()+8.0,Y()+8.0,_scaleX,_scaleY,_rot,1.0-_colG-_colB,1.0,1.0,1.0);
}

//Enemy Class Member Move on Grid Function
void Enemy::moveOnGrid()
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

        //Set Texture if Needed
        if(_type==8)
        {
            _sprite.setTexture(_sprSkeletonWhiteWalkSouth);
        }
        else if(_type==9)
        {
            _sprite.setTexture(_sprSkeletonRedWalkSouth);
        }
        else if(_type==10)
        {
            _sprite.setTexture(_sprSkeletonGoldWalkSouth);
        }
        else if(_type==11)
        {
            _sprite.setTexture(_sprImpWalkSouth);
        }
        else if(_type==12)
        {
            _sprite.setTexture(_sprDemonWalkSouth);
        }
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

        //Set Texture if Needed
        if(_type==8)
        {
            _sprite.setTexture(_sprSkeletonWhiteWalkNorth);
        }
        else if(_type==9)
        {
            _sprite.setTexture(_sprSkeletonRedWalkNorth);
        }
        else if(_type==10)
        {
            _sprite.setTexture(_sprSkeletonGoldWalkNorth);
        }
        else if(_type==11)
        {
            _sprite.setTexture(_sprImpWalkNorth);
        }
        else if(_type==12)
        {
            _sprite.setTexture(_sprDemonWalkNorth);
        }
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

        //Set Texture if Needed
        if(_type==8)
        {
            _sprite.setTexture(_sprSkeletonWhiteWalkEast);
        }
        else if(_type==9)
        {
            _sprite.setTexture(_sprSkeletonRedWalkEast);
        }
        else if(_type==10)
        {
            _sprite.setTexture(_sprSkeletonGoldWalkEast);
        }
        else if(_type==11)
        {
            _sprite.setTexture(_sprImpWalkEast);
        }
        else if(_type==12)
        {
            _sprite.setTexture(_sprDemonWalkEast);
        }
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

        //Set Texture if Needed
        if(_type==8)
        {
            _sprite.setTexture(_sprSkeletonWhiteWalkWest);
        }
        else if(_type==9)
        {
            _sprite.setTexture(_sprSkeletonRedWalkWest);
        }
        else if(_type==10)
        {
            _sprite.setTexture(_sprSkeletonGoldWalkWest);
        }
        else if(_type==11)
        {
            _sprite.setTexture(_sprImpWalkWest);
        }
        else if(_type==12)
        {
            _sprite.setTexture(_sprDemonWalkWest);
        }
    }

    //Update Sprite
    if(_type>7)
    {
        if(move)
        {
            _sprite.update(Speed()*0.15);
        }
        else if(!Moved()&&_sprite.index()>0&&!_attacking)
        {
            _sprite.setIndex(0);
        }
    }

    //Update Moved
    setMoved(move);
}
