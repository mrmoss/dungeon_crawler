//sound.cpp
//Created By:  Mike Moss
//Description:  Source for sound.h.
//Date:  2011

//Definitions for "sound.h"
#include "sound.h"

//Sound Class Static Bass System Start Function
bool Sound::Start()
{
    //return BASS_Init(-1,44100,BASS_DEVICE_DEFAULT,NULL,NULL);
    return true;
}

//Sound Class Static Bass System Stop Function
void Sound::Stop()
{
    //BASS_Free();
}

//Sound Class Constructor(Default and 2 argument version)
Sound::Sound(const std::string& filename,const bool loop,const double volume):_filename(filename),
    _loop(loop),/*_sample(BASS_SampleLoad(false,_filename.c_str(),0,0,65535,_loop*BASS_SAMPLE_LOOP)),*/_volume(volume)
{
    //CANT USE WHEN STATIC
    //Check If Sound System Was Started
    /*if(BASS_ErrorGetCode()==BASS_ERROR_INIT)
    {
        throw std::runtime_error("Sound(ctor) - You must call Sound::Start() first!!!");
    }*/

    //CANT USE WHEN STATIC
    //Check If Sound Loaded
    /*if(BASS_ErrorGetCode()==BASS_ERROR_HANDLE)
    {
        throw std::runtime_error("Sound(ctor) - Invalid filename!!!");
    }*/

    //Check Volume
    if(_volume<0.0)
    {
        _volume=0.0;
    }
    else if(_volume>1.0)
    {
        _volume=1.0;
    }
}

//Sound Class Copy Constructor
Sound::Sound(const Sound& copy):_filename(copy._filename),_loop(copy._loop),_volume(copy._volume)
{
    //BASS_SampleFree(_sample);
    //_sample=BASS_SampleLoad(false,_filename.c_str(),0,0,65535,_loop*BASS_SAMPLE_LOOP);
}

//Sound Class Assignment Operator
Sound& Sound::operator=(const Sound& rhs)
{
    if(this!=&rhs)
    {
        //BASS_SampleFree(_sample);
        _filename=rhs._filename;
        _loop=rhs._loop;
        //_sample=BASS_SampleLoad(false,_filename.c_str(),0,0,65535,_loop*BASS_SAMPLE_LOOP);
        _volume=rhs._volume;
    }

    return *this;
}

//Sound Class Destructor
Sound::~Sound()
{
    //BASS_SampleFree(_sample);
}

//Sound Class Member Volume Mutator
void Sound::setVolume(const double volume)
{
    //Set Volume
    _volume=volume;

    //Check Volume
    if(_volume<0.0)
    {
        _volume=0.0;
    }
    else if(_volume>1.0)
    {
        _volume=1.0;
    }
}

//Sound Class Member Volume Accessor
double Sound::getVolume() const
{
    return _volume;
}

//Sound Class Member Play Function
void Sound::play()
{
    //HCHANNEL channel=BASS_SampleGetChannel(_sample,false);
    //BASS_ChannelSetAttribute(channel,BASS_ATTRIB_VOL,_volume);
    //BASS_ChannelPlay(channel,true);
}

//Sound Class Member Stop Function
void Sound::stop()
{
    //BASS_SampleStop(_sample);
}
