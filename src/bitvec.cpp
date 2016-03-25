//bitvec.cpp
//Created By:	Mike Moss and Charlie Carlson
//Description:	BitVec source.
//Date:  2011

//Definitions for "bitvec.h"
#include "bitvec.h"

//Define Number of Bits in an Int
#define NUMBITS (sizeof(int)*8)

//BitVec Class Constructor(Default and 3 argument version)
BitVec::BitVec(const unsigned int sizeX,const unsigned int sizeY,const bool defaultValue):_sizeX(sizeX),_sizeY(sizeY)
{
    //Calculate Number of Bytes
    unsigned int totalBits=_sizeX*_sizeY;
    unsigned int totalBytes=(totalBits/NUMBITS)+static_cast<bool>(totalBits%NUMBITS);

    //Allocate Memory
    _bytes=new int[totalBytes];

    //Assign Default Values
    for(unsigned int ii=0;ii<totalBytes;++ii)
    {
        if(defaultValue)
        {
            _bytes[ii]=~0;
        }
        else
        {
            _bytes[ii]=0;
        }
    }
}

//BitVec Class Copy Constructor
BitVec::BitVec(const BitVec& copy):_sizeX(copy._sizeX),_sizeY(copy._sizeY)
{
    //Calculate Number of Bytes
    unsigned int totalBits=_sizeX*_sizeY;
    unsigned int totalBytes=(totalBits/NUMBITS)+static_cast<bool>(totalBits%NUMBITS);

    //Allocate Memory
    _bytes=new int[totalBytes];

    //Copy Data
    for(unsigned int ii=0;ii<totalBytes;++ii)
    {
        _bytes[ii]=copy._bytes[ii];
    }
}

//BitVec Class Equality Operator
BitVec& BitVec::operator=(const BitVec& rhs)
{
    //Self Assignment Check
    if(this==&rhs)
    {
        return *this;
    }

    //Delete Current Data
    delete[] _bytes;

    //Assign New Sizes
    _sizeX=rhs._sizeX;
    _sizeY=rhs._sizeY;

    //Calculate Number of Bytes
    unsigned int totalBits=_sizeX*_sizeY;
    unsigned int totalBytes=(totalBits/NUMBITS)+static_cast<bool>(totalBits%NUMBITS);

    //Allocate Memory
    _bytes=new int[totalBytes];

    //Copy Data
    for(unsigned int ii=0;ii<totalBytes;++ii)
    {
        _bytes[ii]=rhs._bytes[ii];
    }

    return *this;
}

//Destructor
BitVec::~BitVec()
{
    delete[] _bytes;
}

//BitVec Class Member Bit Size X Accessor
unsigned int BitVec::sizeX() const
{
    return _sizeX;
}

//BitVec Class Member Bit Size Y Accessor
unsigned int BitVec::sizeY() const
{
    return _sizeY;
}

//BitVec Class Member Size Accessor
unsigned int BitVec::size() const
{
    //Calculate Number of Bytes
    unsigned int totalBits=_sizeX*_sizeY;
    return (totalBits/NUMBITS)+static_cast<bool>(totalBits%NUMBITS);
}

//BitVec Class Member Bit Index Accessor
bool BitVec::get(const unsigned int x,const unsigned int y) const
{
    if(x>=_sizeX||y>=_sizeY)
    {
        throw std::runtime_error("BitVec(get) - Index passed was out of bounds!!!");
    }

    int bit=(_sizeX*y)+x;
    return (_bytes[bit/NUMBITS]&(1<<(bit%NUMBITS)));
}

//BitVec Class Member Bit Index Mutator
void BitVec::set(const unsigned int x,const unsigned int y,const bool value)
{
    if(x>=_sizeX||y>=_sizeY)
    {
        throw std::runtime_error("BitVec(set) - Index passed was out of bounds!!!");
    }

    int bit=(_sizeX*y)+x;

    if(value)
    {
        _bytes[bit/NUMBITS]|=(1<<(bit%NUMBITS));
    }
    else
    {
        _bytes[bit/NUMBITS]&=(~(1<<(bit%NUMBITS)));
    }
}

//BitVec Class Member Int Index Accessor
int BitVec::getInt(const unsigned int index) const
{
    if(index>=size())
    {
        throw std::runtime_error("BitVec(getInt) - Index passed was out of bounds!!!");
    }

    return _bytes[index];
}

//BitVec Class Member Int Index Mutator
void BitVec::setInt(const unsigned int index,const int value)
{
    if(index>=size())
    {
        throw std::runtime_error("BitVec(setInt) - Index passed was out of bounds!!!");
    }

    _bytes[index]=value;
}
