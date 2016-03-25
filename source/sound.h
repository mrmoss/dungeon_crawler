//sound.h
//Created By:  Mike Moss
//Description:  Sound class for Glut game.
//Date:  2011

#ifndef SOUND_H
#define SOUND_H

//Bass Header
#include "bass.h"

//Exception Header
#include <stdexcept>

//String Header
#include <string>

//Sound Class Declaration
class Sound
{
    public:
        //Static Bass System Start Function
        static bool Start();

        //Static Bass System Stop Function
        static void Stop();

        //Constructor(Default and 2 argument version)
        Sound(const std::string& filename="",const bool loop=false,const double volume=1.0);

        //Copy Constructor
        Sound(const Sound& copy);

        //Assignment Operator
        Sound& operator=(const Sound& rhs);

        //Destructor
        ~Sound();

        //Member Volume Mutator
        void setVolume(const double volume);

        //Member Volume Accessor
        double getVolume() const;

        //Member Play Function
        void play();

        //Member Stop Function
        void stop();

    private:
        //Member Variables
        std::string _filename;
        bool _loop;
        HSAMPLE _sample;
        double _volume;
};

#endif
