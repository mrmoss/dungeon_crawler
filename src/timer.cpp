#include "timer.h"

Timer::Timer(const unsigned int time):_current(0),_max(static_cast<int>(time)),_state(false)
{}

void Timer::reset()
{
    _current=0;
    _state=true;
}

void Timer::update()
{
    if(_state)
    {
        ++_current;

        if(_current>=_max)
        {
            _state=false;
            _current=0;
        }
    }
}

void Timer::setTime(const unsigned int time)
{
    _max=static_cast<int>(time);
    _current=0;
    _state=false;
}

void Timer::setCurrent(const int current)
{
    _current=current;
}

int Timer::current() const
{
    return _current;
}

void Timer::setState(const bool state)
{
    _state=state;

    if(!_state)
    {
        _current=0;
    }
}

bool Timer::state() const
{
    return _state;
}
