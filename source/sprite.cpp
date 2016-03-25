//sprite.cpp
//Created By:  Mike Moss
//Description:  Sprite source.
//Date:  2011

//Definitions for "sprite.h"
#include "sprite.h"

//Sprite Class Constructor(Default and 4 argument version)
Sprite::Sprite(const unsigned int texture,const unsigned int imageNumber,const unsigned int width,const unsigned int height)
    :_texture(texture),_imageNumber(imageNumber),_width(width),_height(height),_imageIndex(0.0)
{
    //Validity Check
    validCheck();
}

//Sprite Class Assignment Operator
Sprite& Sprite::operator=(const Sprite& rhs)
{
    //Assign Values
    _texture=rhs._texture;
    _imageNumber=rhs._imageNumber;
    _width=rhs._width;
    _height=rhs._height;
    _imageIndex=rhs._imageIndex;

    //Validity Check
    validCheck();

    //Return This
    return *this;
}

//Sprite Class Memeber Texture Mutator
void Sprite::setTexture(const unsigned int texture)
{
    _texture=texture;
}

//Sprite Class Memeber Texture Accessor
unsigned int Sprite::texture() const
{
    return _texture;
}

//Sprite Class Member Image Number Accessor
unsigned int Sprite::imageNumber() const
{
    return _imageNumber;
}

//Sprite Class Memeber Width Accessor
double Sprite::width() const
{
    return _width/_imageNumber;
}

//Sprite Class Memeber Height Accessor
double Sprite::height() const
{
    return _height;
}

//Sprite Class Member Animation Frame Mutator
void Sprite::setIndex(const unsigned int imageIndex)
{
    if(imageIndex<_imageNumber)
    {
        _imageIndex=imageIndex;
    }
}

//Sprite Class Memeber Animation Frame Accessor
unsigned int Sprite::index() const
{
    return static_cast<unsigned int>(_imageIndex);
}

//Sprite Class Memeber Animation Frame Mutator
void Sprite::update(const double time)
{
    //Update Frame Index
    _imageIndex+=time;

    //Convert Image Number to a Double
    double imageNumber=static_cast<double>(_imageNumber);

    //Bounds Checking
    while(_imageIndex<0.0)
    {
        _imageIndex+=imageNumber;
    }

    while(_imageIndex>=imageNumber)
    {
        _imageIndex-=imageNumber;
    }
}

//Sprite Class Memeber Draw Function
void Sprite::draw(const int subImage,const double x,const double y,const double scaleX,const double scaleY,
    const double rot,const double alpha,const double red,const double green,const double blue) const
{
    //Get Size of Image(Origin is in the middle)
    double widthHalf=((_width/_imageNumber)*scaleX)/2.0;
    double heightHalf=(_height*scaleY)/2.0;

    //Get Image Frame Width
    double imageSlice=1.0/_imageNumber;

    //Create Non-Const Variable
    int subImageDraw=subImage;

    //Bounds Checking/Animation Check
    if(subImage>=static_cast<int>(_imageNumber))
    {
        subImageDraw=_imageNumber-1;
    }
    else if(subImage<0)
    {
        subImageDraw=index();
    }

    //Enable Texture
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,_texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    //Convert Degrees to Radians
    double rad=rot*(PI/180.0);

    //Draw Image Frame with Rotation and Alpha Value
    glPushMatrix();
    glBegin(GL_QUADS);
        glColor4f(red,green,blue,alpha);
        glTexCoord2f(imageSlice*subImageDraw+0.001,0.999);
        glVertex2f(x-widthHalf*cos(rad)-heightHalf*sin(rad),
            y+widthHalf*sin(rad)-heightHalf*cos(rad));
        glTexCoord2f(imageSlice*(subImageDraw+1.0)-0.001,0.999);
        glVertex2f(x+widthHalf*cos(rad)-heightHalf*sin(rad),
            y-widthHalf*sin(rad)-heightHalf*cos(rad));
        glTexCoord2f(imageSlice*(subImageDraw+1.0)-0.001,0.001);
        glVertex2f(x+widthHalf*cos(rad)+heightHalf*sin(rad),
            y-widthHalf*sin(rad)+heightHalf*cos(rad));
        glTexCoord2f(imageSlice*subImageDraw+0.001,0.001);
        glVertex2f(x-widthHalf*cos(rad)+heightHalf*sin(rad),
            y+widthHalf*sin(rad)+heightHalf*cos(rad));
    glEnd();
    glPopMatrix();

    //Disable Texture
    glDisable(GL_TEXTURE_2D);
}

//Sprite Class Validity Check Function
void Sprite::validCheck()
{
    //Check Number of Subimages
    if(_imageNumber<1)
    {
        throw std::runtime_error("Sprite - Invalid number of subimages!!!");
    }

    //Check Texture Dimensions
    if(_width<2||_height<2)
    {
        throw std::runtime_error("Sprite - Invalid texture dimensions!!!");
    }
}
