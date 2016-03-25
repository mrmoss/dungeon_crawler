//bitvec.h
//Created By:	Mike Moss and Charlie Carlson
//Description:	2D bit array class, measures number of vectors(X axis) and number of bits(Y axis).
//Date:  2011

#ifndef BITVEC_H
#define	BITVEC_H

//Exception Header
#include <stdexcept>

//BitVec Class Declaration
class BitVec
{
    public:
        //Constructor(Default and 3 argument version)
        BitVec(const unsigned int sizeX=0,const unsigned int sizeY=0,const bool defaultValue=0);

        //Copy Constructor
        BitVec(const BitVec& copy);

        //Equality Operator
        BitVec& operator=(const BitVec& rhs);

        //Destructor
        ~BitVec();

        //Member Bit Size X Accessor
        unsigned int sizeX() const;

        //Member Bit Size Y Accessor
        unsigned int sizeY() const;

        //Member Int Size Accessor
        unsigned int size() const;

        //Member Bit Index Accessor
        bool get(const unsigned int x,const unsigned int y) const;

        //Member Bit Index Mutator
        void set(const unsigned int x,const unsigned int y,const bool value);

        //Member Int Index Accessor
        int getInt(const unsigned int index) const;

        //Member Int Index Mutator
        void setInt(const unsigned int index,const int value);

    private:
        //Member Variables
        int* _bytes;
        unsigned int _sizeX;
        unsigned int _sizeY;

};
#endif
