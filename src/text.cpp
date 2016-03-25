//text.cpp
//Created By:  Charlie Carlson
//Description:  Text source.
//Date:  2011

//Definitions for "text.h"
#include "text.h"

//Text Class Constructor(3 argument version)
Text::Text(std::string filename,const unsigned int width,const unsigned int height):_texture(loadBMP(filename.c_str())),_sprite(_texture,59,width*59,8),
_width(width),_height(height)
{}

//Text Class Member Width Accessor
double Text::width() const
{
    return static_cast<double>(_width);
}

//Text Class Member Height Accessor
double Text::height() const
{
    return static_cast<double>(_height);
}

//Text Class Member Draw Function
void Text::draw(const std::string& str,const double x,const double y) const
{
	for(unsigned int ii=0;ii<str.size();++ii)
	{
	    _sprite.draw(str[ii]-32,x+(_width/2)+(_width*ii),y+(_height/2));
	}
}
