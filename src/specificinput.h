//specificinput.h
//Created By:  Mike Moss
//Description:  Read specific input from an input stream, such as int, and short.
//Date:  2011

#ifndef SPECIFIC_INPUT_H
#define SPECIFIC_INPUT_H

//Input Stream Header
#include <istream>

//Read Int from Char Array from Input Stream
int readInt(std::istream& istr);

//Read Short from Char Array from Input Stream
short readShort(std::istream& istr);

#endif
