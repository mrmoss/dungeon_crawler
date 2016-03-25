//glut2d.h
//Created By:  Mike Moss
//Description:  Glut system for creating and managing all Glut functions in a class, allows for
//               multiple windows, handles key inputs, mouse movement and input, etc...
//Date:  2011

#ifndef GLUT_INSTANCE_2D_H
#define GLUT_INSTANCE_2D_H

//Camera Header
#include "camera2d.h"

//Exception Header
#include <stdexcept>

//Glut Header
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

//String Header
#include <string>

//Vector Header
#include <vector>

//Input Bindings
#define kb_f1           0x0001
#define kb_f2           0x0002
#define kb_f3           0x0003
#define kb_f4           0x0004
#define kb_f5           0x0005
#define kb_f6           0x0006
#define kb_f7           0x0007
#define kb_f8           0x0008
#define kb_f9           0x0009
#define kb_f10          0x000A
#define kb_f11          0x000B
#define kb_f12          0x000C

#define kb_enter        0x100D
#define kb_escape       0x101B
#define kb_space        0x1020

#define kb_0            0x1030
#define kb_1            0x1031
#define kb_2            0x1032
#define kb_3            0x1033
#define kb_4            0x1034

#define kb_5            0x1035
#define kb_6            0x1036
#define kb_7            0x1037
#define kb_8            0x1038
#define kb_9            0x1039

#define kb_a            0x1061
#define kb_b            0x1062
#define kb_c            0x1063
#define kb_d            0x1064
#define kb_e            0x1065
#define kb_f            0x1066
#define kb_g            0x1067
#define kb_h            0x1068
#define kb_i            0x1069
#define kb_j            0x106A
#define kb_k            0x106B
#define kb_l            0x106C
#define kb_m            0x106D
#define kb_n            0x106E
#define kb_o            0x106F
#define kb_p            0x1070
#define kb_q            0x1071
#define kb_r            0x1072
#define kb_s            0x1073
#define kb_t            0x1074
#define kb_u            0x1075
#define kb_v            0x1076
#define kb_w            0x1077
#define kb_x            0x1078
#define kb_y            0x1079
#define kb_z            0x107A

#define kb_left         0x0064
#define kb_up           0x0065
#define kb_right        0x0066
#define kb_down         0x0067
#define kb_pageup       0x0068
#define kb_pagedown     0x0069
#define kb_home         0x006A
#define kb_end          0x006B
#define kb_insert       0x006C

#define mb_left         0x2000
#define mb_middle       0x2001
#define mb_right        0x2002

//Glut2D Class Declaration
class Glut2D
{
    //Global Friend Input Accessors
    friend bool input_check(const int key);
    friend bool input_check_pressed(const int key);

    public:
        //Static OpenGL Mutators
        static void initialize(int argc,char** argv);
        static void start();

        //Constructor(Default and 5 argument version)
        Glut2D(const std::string& windowCaption="Openl GL Window",const int windowWidth=640,const int windowHeight=480,
            void(*timer)(Glut2D&)=NULL,const unsigned int timerTime=25,void(*display)(Glut2D&)=NULL);

        //Destructor
        ~Glut2D();

        //Memeber Window Active Accessor
        bool getActive() const;

        //Member Timer Mutator
        void setTimerTime(const unsigned int timerTime);

        //Member Timer Accessor
        unsigned int getTimerTime() const;

        //Member Window Dimensions Accessors
        unsigned int windowWidth() const;
        unsigned int windowHeight() const;

        //Member Delta Time Accessor
        double DT() const;

        //Member Mouse Position Mutators
        void setMX(const unsigned int mouseX);
        void setMY(const unsigned int mouseY);

        //Member Mouse Position Accessors
        unsigned int MX() const;
        unsigned int MY() const;

        //Memeber Camera2D Object
        Camera2D camera;

    private:
        //Static Variables
        static std::vector<Glut2D*> _instance;
        static bool _keyboardDown[256];
        static bool _keyboardPressed[256];
        static bool _specialDown[256];
        static bool _specialPressed[256];
        static bool _mouseDown[3];
        static bool _mousePressed[3];

        //Invalid Operators(Aka, ones that I am too lazy to make at this time...)
        Glut2D(const Glut2D&);
        Glut2D &operator=(const Glut2D&);

        //Static Glut Functions
        static void reshape(int width,int height);
        static void windowStatus(int state);
        static void timer(int value);
        static void display();
        static void keyboardDown(unsigned char key,int x,int y);
        static void keyboardUp(unsigned char key,int x,int y);
        static void specialDown(int key,int x,int y);
        static void specialUp(int key,int x,int y);
        static void mouse(int button,int state,int x,int y);
        static void mouseEntry(int state);
        static void motion(int x,int y);
        static void clearPressed();

        //Member Variables
        int _windowID;
        int _windowWidth;
        int _windowHeight;
        bool _active;
        void(*_timer)(Glut2D&);
        unsigned int _timerTime;
        void(*_display)(Glut2D&);
        double _dt;
        double _ot;
        unsigned int _mouseX;
        unsigned int _mouseY;
};

//Global Input Accessors
bool input_check(const int key);
bool input_check_pressed(const int key);

#endif
