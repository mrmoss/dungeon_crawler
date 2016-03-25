//sprite.h
//Created By:  Mike Moss
//Description:  Sprite system, handles animated strip-type sprites.
//Date:  2011

#ifndef SPRITE_H
#define SPRITE_H

//Exception Header
#include <stdexcept>

//Game Math Header
#include "gamemath.h"

//OpenGL Header
#include <GL/gl.h>

//Sprite Class Decalaration
class Sprite
{
    public:
        //Constructor(Default and 4 argument version)
        Sprite(const unsigned int texture=0,const unsigned int imageNumber=1,const unsigned int width=2,const unsigned int height=2);

        //Assignment Operator
        Sprite& operator=(const Sprite& rhs);

        //Member Texture Mutator
        void setTexture(const unsigned int texture);

        //Member Texture Accessor
        unsigned int texture() const;

        //Member Image Number Accessor
        unsigned int imageNumber() const;

        //Member Dimensions Accessors
        double width() const;
        double height() const;

        //Member Animation Frame Mutator
        void setIndex(const unsigned int imageIndex);

        //Member Animation Frame Accessor
        unsigned int index() const;

        //Member Animation Frame Mutator
        void update(const double time);

        //Member Draw Function
        void draw(const int subImage,const double x,const double y,const double scaleX=1.0,const double scaleY=1.0,
            const double rot=0.0,const double alpha=1.0,const double red=1.0,const double green=1.0,const double blue=1.0) const;

        //Member Variables
        unsigned int _texture;
        unsigned int _imageNumber;
        unsigned int _width;
        unsigned int _height;
        double _imageIndex;

    private:
        //Validity Check Function
        void validCheck();
};

#endif
