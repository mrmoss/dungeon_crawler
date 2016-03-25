//main.cpp
//Created By:  Charlie Carlson & Mike Moss
//Description:  Main for Glut game.
//Date:  2011

//All images copyrighted to Square Enix
//All sounds copyrighted to Square Enix

//C Standard Library
#include <cstdlib>

//Chest Header
#include "chest.h"

//Dungeon Header
#include "dungeon.h"

//Enemy Header
#include "enemy.h"

//Exception Header
#include <stdexcept>

//File Stream Header
#include <fstream>

//Glut2D Header
#include "glut2d.h"

//Hero Header
#include "hero.h"

//Hydra Header
#include "hydra.h"

//Sound Header
#include "sound.h"

//String Stream Header
#include <sstream>

//Text Header
#include "text.h"

//Time Header
#include <time.h>

//Glut2D Function Prototypes
void create();
void timer(Glut2D& w);
void display(Glut2D& w);

//Global Variables
Dungeon* d;
Text* font;
bool mainMenuShow=true;
int mainMenuOption=0;
bool menuSaveShow=false;
int menuSaveOption=0;
bool menuLoadShow=false;
int menuLoadOption=0;
bool menuOpeningShow=false;
bool menuEndShow=false;
bool menuEndDieShow=false;

//Main
int main(int argc,char** argv)
{
    //Catch Errors and Print to File
    try
    {
        //Sound Start
        Sound::Start();

        //Seed Random
        std::srand(time(NULL));

        //Initialize Glut2D
        Glut2D::initialize(argc,argv);

        //Create Glut2D Window
        Glut2D w("Dungeon Crawler",320,240,timer,25,display);

        //Create Game
        create();

        //Play Music
        Sound music("sounds/music.ogg",true,0.5);
        music.play();

        //Start Glut2D
        Glut2D::start();
    }
    catch(std::exception &e)
    {
        std::ofstream ostr("error.log");
        ostr<<e.what();
        ostr.close();
    }

    //End Program
    return 0;
}

//Glut2D Create Function
void create()
{
    //Set Some Glut Stuff
    glutSetCursor(GLUT_CURSOR_NONE);

    //Load Textures for Objects
    Chest::spriteLoad();
    Entity::spriteLoad();
    Enemy::spriteLoad();
    Fireball::spriteLoad();
    Hero::spriteLoad();
    Hydra::spriteLoad();

    //Initialize Dungeon Items
    Dungeon::initializeItems();

    //Initialize Sound
    Dungeon::soundLoad();

    //Font
    font=new Text("sprites/font.bmp",8,8);
}

//Glut2D Timer Function
void timer(Glut2D& w)
{
    //Update Game
    if(mainMenuShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_down))
        {
            ++mainMenuOption;

            if(mainMenuOption>2)
            {
                mainMenuOption=0;
            }
        }

        if(input_check_pressed(kb_up))
        {
            --mainMenuOption;

            if(mainMenuOption<0)
            {
                mainMenuOption=2;
            }
        }

        if(input_check_pressed(kb_space))
        {
            if(mainMenuOption==0)
            {
                mainMenuOption=0;
                mainMenuShow=false;
                menuSaveShow=true;
            }
            else if(mainMenuOption==1)
            {
                mainMenuOption=0;
                mainMenuShow=false;
                menuLoadShow=true;
            }
            else if(mainMenuOption==2)
            {
                exit(0);
            }
            else
            {
                throw std::logic_error("Main Menu - This should never happen!!!");
            }
        }
    }
    else if(menuSaveShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_down))
        {
            ++menuSaveOption;

            if(menuSaveOption>2)
            {
                menuSaveOption=0;
            }
        }

        if(input_check_pressed(kb_up))
        {
            --menuSaveOption;

            if(menuSaveOption<0)
            {
                menuSaveOption=2;
            }
        }

        if(input_check_pressed(kb_space))
        {
            menuSaveShow=false;
            menuOpeningShow=true;
        }
    }
    else if(menuLoadShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_down))
        {
            ++menuLoadOption;

            if(menuLoadOption>2)
            {
                menuLoadOption=0;
            }
        }

        if(input_check_pressed(kb_up))
        {
            --menuLoadOption;

            if(menuLoadOption<0)
            {
                menuLoadOption=2;
            }
        }

        if(input_check_pressed(kb_space))
        {
            std::ostringstream ostr;
            ostr<<"saves/save"<<menuLoadOption<<".sav";

            std::ifstream istr(ostr.str().c_str());
            istr.close();

            menuLoadOption=0;
            menuLoadShow=false;

            if(!istr.fail())
            {
                d=new Dungeon(menuEndShow,menuEndDieShow,false,ostr.str().c_str(),"sprites/tiles.bmp",48,32,16);
            }
            else
            {
                mainMenuShow=true;
            }
        }
    }
    else if(menuOpeningShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_space))
        {
            menuOpeningShow=false;
            std::ostringstream ostr;
            ostr<<"saves/save"<<menuSaveOption<<".sav";

            d=new Dungeon(menuEndShow,menuEndDieShow,true,ostr.str(),"sprites/tiles.bmp",48,32,16);
            menuSaveOption=0;
        }
    }
    else if(menuEndShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_space))
        {
            menuEndShow=false;
            mainMenuShow=true;
        }
    }
    else if(menuEndDieShow)
    {
        w.camera.setX(0.0);
        w.camera.setY(0.0);

        if(input_check_pressed(kb_space))
        {
            menuEndDieShow=false;
            mainMenuShow=true;
        }
    }
    else if(d!=NULL)
    {
        //Dungeon Update
        d->update();

        //Set Camera Position
        if(d->getViewEntity()!=NULL)
        {
            w.camera.setX(d->getViewEntity()->X()-(w.windowWidth()/2));
            w.camera.setY(d->getViewEntity()->Y()-(w.windowHeight()/2));
        }
    }
}

//Glut2D Display Function
void display(Glut2D& w)
{
    //Draw Delta Time
    std::ostringstream ostr;
    ostr<<"Dungeon Crawler ["<<w.DT()<<"]";
    glutSetWindowTitle(ostr.str().c_str());

    //Draw Game
    if(mainMenuShow)
    {
        //Offeset Variables
        double offsetX;
        double offsetY;

        //Draw Title
        offsetX=(w.windowWidth()/2.0)-(font->width()*7.0);
        offsetY=(w.windowHeight()/2.0)-(font->height()*5.0);
        font->draw("DUNGEON CRAWLER",offsetX,offsetY);

        //Draw Menu
        offsetX=(w.windowWidth()/2.0)-(font->width()*4.0);
        offsetY=(w.windowHeight()/2.0)+(font->height()*2.0);
        font->draw("  NEW",offsetX,offsetY);
        font->draw("  LOAD",offsetX,offsetY+font->height());
        font->draw("  QUIT",offsetX,offsetY+font->height()*2.0);
        font->draw(">",offsetX,offsetY+font->height()*mainMenuOption);

        //Draw Info
        offsetX=(font->width());
        offsetY=(w.windowHeight()-(font->height()*3.0));
        font->draw("ALL IMAGES COPYRIGHTED BY SQUARE ENIX.",offsetX,offsetY);
        font->draw("ALL SOUNDS COPYRIGHTED BY SQUARE ENIX.",offsetX,offsetY+font->height());

    }
    else if(menuSaveShow)
    {
        //Offeset Variables
        double offsetX;
        double offsetY;

        //Draw Title
        offsetX=(w.windowWidth()/2.0)-(font->width()*8.0);
        offsetY=(w.windowHeight()/2.0)-(font->height()*5.0);
        font->draw("SELECT A SAVE SLOT",offsetX,offsetY);

        //Draw Menu
        offsetX=(w.windowWidth()/2.0)-(font->width()*4.0);
        offsetY=(w.windowHeight()/2.0)+(font->height()*2.0);
        font->draw("  SAVE 1",offsetX,offsetY);
        font->draw("  SAVE 2",offsetX,offsetY+font->height());
        font->draw("  SAVE 3",offsetX,offsetY+font->height()*2.0);
        font->draw(">",offsetX,offsetY+font->height()*menuSaveOption);
    }
    else if(menuOpeningShow)
    {
        //Offset Variables
        double offsetX=font->width()*4.0;
        double offsetY=font->height()*5.0;

        //Draw Opening Scene
        font->draw("I AM THE GREAT WIZARD ORION!!!",offsetX,offsetY);
        font->draw("I HAVE LOST MY MAGICAL BOOKS!!!",offsetX,offsetY+font->height());
        font->draw("RETRIEVE THEM AND YOU SHALL",offsetX,offsetY+font->height()*2.0);
        font->draw("LIVE A LITTLE LONGER!!!",offsetX,offsetY+font->height()*3.0);
        font->draw("OH YEA, THERE ARE 7...",offsetX,offsetY+font->height()*4.0);
        font->draw("AND TO MOVE USE THE ARROW KEYS...",offsetX,offsetY+font->height()*6.0);
        font->draw("AND USE X TO ATTACK...",offsetX,offsetY+font->height()*7.0);
        font->draw("AND Z TO USE POTIONS IN COMBAT...",offsetX,offsetY+font->height()*8.0);
        font->draw("AND SPACE TO BROWSE THE MENU",offsetX,offsetY+font->height()*9.0);

        //Draw Option
        offsetX=font->width()*13.0;
        offsetY=font->height()*21.0;
        font->draw("> CONTINUE!?",offsetX,offsetY);
    }
    else if(menuLoadShow)
    {
        //Offeset Variables
        double offsetX;
        double offsetY;

        //Draw Title
        offsetX=(w.windowWidth()/2.0)-(font->width()*7.0);
        offsetY=(w.windowHeight()/2.0)-(font->height()*5.0);
        font->draw("LOAD A DUNGEON",offsetX,offsetY);

        //Draw Menu
        offsetX=(w.windowWidth()/2.0)-(font->width()*4.0);
        offsetY=(w.windowHeight()/2.0)+(font->height()*2.0);
        font->draw("  SAVE 1",offsetX,offsetY);
        font->draw("  SAVE 2",offsetX,offsetY+font->height());
        font->draw("  SAVE 3",offsetX,offsetY+font->height()*2.0);
        font->draw(">",offsetX,offsetY+font->height()*menuLoadOption);
    }
    else if(menuEndShow)
    {
        //Offset Variables
        double offsetX=font->width()*5.0;
        double offsetY=font->height()*5.0;

        //Draw Ending Scene
        font->draw("THE GREAT WIZARD ORION IS",offsetX,offsetY);
        font->draw("PLEASED!!!  YOU MAY NOW GO",offsetX,offsetY+font->height());
        font->draw("ON LIVING MORTAL!!!",offsetX,offsetY+font->height()*2.0);
        font->draw("BUT SERIOUSLY THANKS FOR",offsetX,offsetY+font->height()*5.0);
        font->draw("PLAYING...",offsetX,offsetY+font->height()*6.0);

        //Draw Credits
        font->draw("CREDITS",offsetX,offsetY+font->height()*9.0);
        font->draw("CHARLIE CARLSON",offsetX,offsetY+font->height()*10.0);
        font->draw("DUSTIN DODSON",offsetX,offsetY+font->height()*11.0);
        font->draw("MIKE MOSS",offsetX,offsetY+font->height()*12.0);
        font->draw("ZACK WILLIAMS",offsetX,offsetY+font->height()*13.0);

        //Draw Option
        offsetX=font->width()*13.0;
        offsetY=font->height()*21.0;
        font->draw("> CONTINUE!?",offsetX,offsetY);
    }
    else if(menuEndDieShow)
    {
        //Offset Variables
        double offsetX=font->width()*5.0;
        double offsetY=font->height()*5.0;

        //Draw Ending Scene
        font->draw("THE GREAT WIZARD ORION IS",offsetX,offsetY);
        font->draw("NOT PLEASED!!!  YOU MAY NOW NOT",offsetX,offsetY+font->height());
        font->draw("GO ON LIVING MORTAL!!!",offsetX,offsetY+font->height()*2.0);
        font->draw("BUT SERIOUSLY THANKS FOR",offsetX,offsetY+font->height()*5.0);
        font->draw("PLAYING...",offsetX,offsetY+font->height()*6.0);

        //Draw Credits
        font->draw("CREDITS",offsetX,offsetY+font->height()*9.0);
        font->draw("CHARLIE CARLSON",offsetX,offsetY+font->height()*10.0);
        font->draw("DUSTIN DODSON",offsetX,offsetY+font->height()*11.0);
        font->draw("MIKE MOSS",offsetX,offsetY+font->height()*12.0);
        font->draw("ZACK WILLIAMS",offsetX,offsetY+font->height()*13.0);

        //Draw Option
        offsetX=font->width()*13.0;
        offsetY=font->height()*21.0;
        font->draw("> CONTINUE!?",offsetX,offsetY);
    }
    else if(d!=NULL)
    {
        //Dungeon Draw
        d->draw(w.windowWidth(),w.windowHeight(),*font);
    }
}
