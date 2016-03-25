//text.h
//Created By:  Charlie Carlson
//Description:  Text class for Glut game.
//Date:  2011

#ifndef TEXT_H
#define TEXT_H

//BMP Loader Header
#include "bmp.h"

//Sprite Header
#include "sprite.h"

//String Header
#include <string>

//Text Class Declaration
class Text
{
    public:
        //Constructor(3 argument version)
        Text(std::string filename,const unsigned int width,const unsigned int height);

        //Member Width Accessor
        double width() const;

        //Member Height Accessor
        double height() const;

        //Member Draw Function
        void draw(const std::string& str,const double x,const double y) const;

    private:
        //Member Varibles
        unsigned int _texture;
        Sprite _sprite;
        unsigned int _width;
        unsigned int _height;
};

#endif
