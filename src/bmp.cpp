//bmp.cpp
//Created By:  Mike Moss
//Description:  BMP source.
//Date:  2011

//Definitions for "bmp.h"
#include "bmp.h"

//Loads a BMP file into a GL Texture
unsigned int loadBMP(const char* fileName,const bool transparency)
{
	//Open BMP File
	std::ifstream istr(fileName,std::ifstream::binary);

	if(!istr)
    {
        throw std::runtime_error("BMP Loader - File does not exist!!!");
    }

    //Check if File is a BMP
	char buffer[2];
	istr.read(buffer,2);

	if(buffer[0]!='B'||buffer[1]!='M')
	{
	    throw std::runtime_error("BMP Loader - File is not a BMP!!!");
	}

    //Skip Some Reserved Stuff
	istr.ignore(8);

	//Read File Offset to Pixel Array
	int dataOffset=readInt(istr);

	//Read DIB Header
	int dataHeaderSize=readInt(istr);

	//Image Width/Height Declaration
	int imageWidth;
	int imageHeight;

    //Error Checking
	if(dataHeaderSize==40)
	{
        imageWidth=readInt(istr);
        imageHeight=readInt(istr);
        istr.ignore(2);

        if(readShort(istr)!=24)
        {
            throw std::runtime_error("BMP Loader - File must be 24 bit!!!");
        }

        if(readShort(istr)!=0)
        {
            throw std::runtime_error("BMP Loader - File cannot be compressed!!!");
        }
	}
	else if(dataHeaderSize==108)
	{
        throw std::runtime_error("BMP Loader - Cannot load V4 format!!!");
	}
	else if(dataHeaderSize==124)
	{
        throw std::runtime_error("BMP Loader - Cannot load V5 format!!!");
	}
	else
	{
        throw std::runtime_error("BMP Loader - Unknown BMP format!!!");
	}

    //Read Pixel Array Size
	int bytesPerRow=((imageWidth*3+3)/4)*4-(imageWidth*3%4);
	int size=bytesPerRow*imageHeight;

	//Read Pixel Array
	char* pixelsRGB=new char[size];
	istr.seekg(dataOffset,std::ios_base::beg);
	istr.read(pixelsRGB,size);

    //Color Key Transparency Variables
	int ra;
	int ga;
	int ba;

	//Allocate Array for Pixel Data
	char* pixelsRGBA=new char[imageWidth*imageHeight*4];

	//Change Pixel Data from RGB to RGBA
	for(int yy=0;yy<imageHeight;++yy)
	{
		for(int xx=0;xx<imageWidth;++xx)
		{
            //RGB Value of Pixel
            int r=pixelsRGB[bytesPerRow*yy+3*xx+(2-0)];
            int g=pixelsRGB[bytesPerRow*yy+3*xx+(2-1)];
            int b=pixelsRGB[bytesPerRow*yy+3*xx+(2-2)];

            //Get Color Key Value(Bottom Left Corner)
            if(xx==0&&yy==0)
            {
                ra=r;
                ga=g;
                ba=b;
            }

            //Assign RGB Pixel Part
            pixelsRGBA[4*(imageWidth*yy+xx)+0]=r;
            pixelsRGBA[4*(imageWidth*yy+xx)+1]=g;
            pixelsRGBA[4*(imageWidth*yy+xx)+2]=b;

            //Assign Alpha Pixel Part(Based on Color Key)
			if(transparency&&r==ra&&g==ga&&b==ba)
			{
                pixelsRGBA[4*(imageWidth*yy+xx)+3]=0;
			}
			else
			{
			    pixelsRGBA[4*(imageWidth*yy+xx)+3]=255;
			}
		}
    }

	//Close File
	istr.close();

    //Build GL Texture
	unsigned int textureID;
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imageWidth,imageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pixelsRGBA);

    //Clean Up Memory
    delete[] pixelsRGB;
    delete[] pixelsRGBA;

    //Return GL Texture
	return textureID;
}
