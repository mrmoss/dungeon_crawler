//specificinput.cpp
//Created By:  Mike Moss
//Description:  Specific input source.
//Date:  2011

//Definitions for "specificinput.h"
#include "specificinput.h"

//Read Int from Char Array from Input Stream
int readInt(std::istream& istr)
{
    //Read in Chars
    char byte[4];
    istr.read(byte,4);

    //Shift Bits and Return Int
    return static_cast<int>((static_cast<unsigned char>(byte[3])<<24)|(static_cast<unsigned char>(byte[2])<<16)|
        (static_cast<unsigned char>(byte[1])<<8)|static_cast<unsigned char>(byte[0]));
}

//Read Short from Char Array from Input Stream
short readShort(std::istream& istr)
{
    //Read in Chars
    char byte[2];
    istr.read(byte,2);

    //Shift Bits and Return Short
    return static_cast<short>((static_cast<unsigned char>(byte[1])<<8)|static_cast<unsigned char>(byte[0]));
}
