#ifndef TIMER_H
#define TIMER_H

class Timer
{
    public:
        Timer(const unsigned int time=0);
        void reset();
        void update();
        void setTime(const unsigned int time);
        void setCurrent(const int current);
        int current() const;
        void setState(const bool state);
        bool state() const;

    private:
        int _current;
        int _max;
        int _state;
};

#endif
