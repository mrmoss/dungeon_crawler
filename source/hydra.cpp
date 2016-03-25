//hydra.cpp
//Created By:  Mike Moss and Zack Willams
//Description:  Hydra source.
//Date:  2011

//Definitions for "hydra.h"
#include "hydra.h"

//Hydra Class Static Variables
unsigned int Hydra::_sprHydraBody;
unsigned int Hydra::_sprHydraFeet;
unsigned int Hydra::_sprWyrmBody;
unsigned int Hydra::_sprWyrmFeet;

//Hydra Class Static Sprite Load Function
void Hydra::spriteLoad()
{
    _sprHydraBody=loadBMP("sprites/hydraBody.bmp");
    _sprHydraFeet=loadBMP("sprites/hydraFeet.bmp");
    _sprWyrmBody=loadBMP("sprites/wyrmBody.bmp");
    _sprWyrmFeet=loadBMP("sprites/wyrmFeet.bmp");
}

//Hydra Class Constructor(Default and 3 argument version)
Hydra::Hydra(const double x,const double y,const unsigned int type):Entity(x,y,6,1,15),_patrol("s"),_table("s")
{
    //Set Life to Full
    setLife(LifeMax());

    //Create One of Two "Hydras"
    if(type==0)
    {
        _body=Sprite(_sprHydraBody,4,128,32);
        _feet=Sprite(_sprHydraFeet,4,128,32);
    }
    else if(type==1)
    {
        _body=Sprite(_sprWyrmBody,4,128,32);
        _feet=Sprite(_sprWyrmFeet,4,128,32);
    }
    else
    {
        throw std::runtime_error("Hydra - Invalid creation type!!!");
    }
}

//Hydra Class Member Type Accessor
unsigned int Hydra::getType() const
{
    if(_body.texture()==_sprWyrmBody)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Hydra Class Member Tables Mutator
void Hydra::setTables(const std::string& patrol,const std::string& table)
{
    _patrol=patrol;
    _table=table;
}

//Hydra Class Member Tables Accessor
void Hydra::getTables(std::string& patrol,std::string& table)
{
    patrol=_patrol;
    table=_table;
}

//Hydra Class Member Update Function
void Hydra::update(BitVec& mapVec,BitVec& colVec,Dungeon& d)
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

    //Update Body Sprite
    _body.update(0.1);

    //Shoot Fireballs
    if(rand()%40==5)
    {
        int head=rand()%2;

        if(head==0)
        {
            head=8.0;
        }
        else if(head==1)
        {
            head=24.0;
        }

        //Play Fireball Shooting Sound
        if(distance(XT(),YT(),d.getViewEntity()->XT(),d.getViewEntity()->YT())<20)
        {
            d.sndHydraShoot.play();
        }

        d.pushFireball(Fireball(X()+head,Y()+12.0,225+rand()%90,0));
    }

    //Random Movement
    if(_table.size()<=1)
    {
        int dir=rand()%4;

        switch(dir)
        {
            case 0:
                _table+='e';
                break;
            case 1:
                _table+='n';
                break;
            case 2:
                _table+='w';
                break;
            case 3:
                _table+='s';
                break;
            default:
                _table+='e';
                break;
        }
    }

    //Move
    if(!Dead()&&!Moved()&&_table.size()>1)
    {
        char ch=_table[1];
        _table.erase(_table.begin()+1);

        if(ch=='e')
        {
            if(mapVec.get(XT()+2,YT())==0&&colVec.get(XT()+2,YT())==0)
            {
                colVec.set(XT(),YT(),0);
                colVec.set(XT()+1,YT(),0);
                addXT(1);
                colVec.set(XT(),YT(),1);
                colVec.set(XT()+1,YT(),1);
            }
        }
        else if(ch=='n')
        {
            if(mapVec.get(XT(),YT()-1)==0&&colVec.get(XT(),YT()-1)==0&&mapVec.get(XT()+1,YT()-1)==0&&colVec.get(XT()+1,YT()-1)==0)
            {
                colVec.set(XT(),YT(),0);
                colVec.set(XT()+1,YT(),0);
                addYT(-1);
                colVec.set(XT(),YT(),1);
                colVec.set(XT()+1,YT(),1);
            }
        }
        else if(ch=='w')
        {
            if(mapVec.get(XT()-1,YT())==0&&colVec.get(XT()-1,YT())==0)
            {
                colVec.set(XT(),YT(),0);
                colVec.set(XT()+1,YT(),0);
                addXT(-1);
                colVec.set(XT(),YT(),1);
                colVec.set(XT()+1,YT(),1);
            }
        }
        else if(ch=='s')
        {
            if(mapVec.get(XT(),YT()+1)==0&&colVec.get(XT(),YT()+1)==0&&mapVec.get(XT()+1,YT()+1)==0&&colVec.get(XT()+1,YT()+1)==0)
            {
                colVec.set(XT(),YT(),0);
                colVec.set(XT()+1,YT(),0);
                addYT(1);
                colVec.set(XT(),YT(),1);
                colVec.set(XT()+1,YT(),1);
            }
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
}

//Hydra Class Member Draw Function
void Hydra::draw(Dungeon& d)
{
    //Draw Body and Feet
    _body.draw(-1,X()+16.0,Y(),_scaleX,_scaleY,_rot,_colA,_colR,_colG,_colB);
    _feet.draw(-1,X()+16.0,Y(),_scaleX,_scaleY,_rot,_colA,_colR,_colG,_colB);

    //Draw Hit Effect
    if(1.0-_colG-_colB>0.0)
    {
        Sprite hit(Entity::_sprHit,1,16,16);
        int dis=3;
        unsigned int closestIndex=0;
        double hitSide=0.0;

        for(unsigned int ii=0;ii<d.sizeHero();++ii)
        {
            int curDis=distance(XT(),YT(),d.getHero(ii).XT(),d.getHero(ii).YT());

            if(curDis<dis)
            {
                dis=curDis;
                closestIndex=ii;
            }
        }

        if(d.getHero(closestIndex).XT()>XT())
        {
            hitSide=16.0;
        }

        hit.draw(0,X()+8.0+hitSide,Y()+8.0,_scaleX,_scaleY,_rot,1.0-_colG-_colB,1.0,1.0,1.0);

    }
}

//Hydra Class Member Move on Grid Function
void Hydra::moveOnGrid()
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
    }

    //Update Sprite
    if(move)
    {
        _feet.update(Speed()*0.15);
    }
    else if(!Moved()&&_feet.index()>0)
    {
        _feet.setIndex(0);
    }

    //Update Moved
    setMoved(move);
}
