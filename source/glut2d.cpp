//glut2d.cpp
//Created By:  Mike Moss
//Description:  Glut2D source.
//Date:  2011

//Definitions for "glut2d.h"
#include "glut2d.h"

//Glut2D Class Static Variables
std::vector<Glut2D*> Glut2D::_instance;
bool Glut2D::_keyboardDown[256];
bool Glut2D::_keyboardPressed[256];
bool Glut2D::_specialDown[256];
bool Glut2D::_specialPressed[256];
bool Glut2D::_mouseDown[3];
bool Glut2D::_mousePressed[3];

//Glut2D Class Static Initialization Function(Call before creating any instances of Glut2D)
void Glut2D::initialize(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
}

//Glut2D Class Static Start Function(Call after creating all instances of Glut2D)
void Glut2D::start()
{
    glutMainLoop();
}

//GlutInstace Class Constructor(Default and 5 argument version)
Glut2D::Glut2D(const std::string& windowCaption,const int windowWidth,const int windowHeight,void(*timer)(Glut2D&),
    const unsigned int timerTime,void(*display)(Glut2D&)):camera(),_windowID(-1),_windowWidth(windowWidth),_windowHeight(windowHeight),
    _active(false),_timer(timer),_timerTime(timerTime),_display(display),_dt(0.0),_ot(0.0),_mouseX(0),_mouseY(0)
{
    //Check Timer Function
    if(!_timer)
    {
        throw std::runtime_error("Glut2D - Invalid timer function!!!");
    }

    //Check Display Function
    if(!_display)
    {
        throw std::runtime_error("Glut2D - Invalid display function!!!");
    }

    //Add to Static Vector
    _instance.push_back(this);

    //Set Window Size and Create Window
    glutInitWindowSize(_windowWidth,_windowHeight);
    _windowID=glutCreateWindow(windowCaption.c_str());

    //Input Functions
    glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(mouse);
	glutEntryFunc(mouseEntry);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

    //Window Functions
	glutReshapeFunc(Glut2D::reshape);
	glutWindowStatusFunc(Glut2D::windowStatus);

	//Timer Function
	glutTimerFunc(_timerTime,Glut2D::timer,0);

	//Display Function
	glutDisplayFunc(Glut2D::display);

	//Enable Color Key Transparency
    glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER,0.0);
    glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

//Glut2D Class Destructor
Glut2D::~Glut2D()
{
    //Remove from Static Vector
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(this==_instance[ii])
        {
            glutDestroyWindow(_instance[ii]->_windowID);
            _instance.erase(_instance.begin()+ii);
            return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid instance passed for removal!!!");
}

//Glut2D Class Member Window Active Accessor
bool Glut2D::getActive() const
{
    return _active;
}

//Glut2D Class Member Timer Mutator
void Glut2D::setTimerTime(const unsigned int timerTime)
{
    if(timerTime>0)
    {
        _timerTime=timerTime;
    }
}

//Glut2D Class Member Timer Accessor
unsigned int Glut2D::getTimerTime() const
{
    return _timerTime;
}

//Glut2D Class Member Window Width Accessor
unsigned int Glut2D::windowWidth() const
{
    return _windowWidth;
}

//Glut2D Class Member Window Height Accessor
unsigned int Glut2D::windowHeight() const
{
    return _windowHeight;
}

//Glut2D Class Member Delta Time Accessor
double Glut2D::DT() const
{
    return _dt;
}

//Glut2D Class Member Mouse X Position Mutator
void Glut2D::setMX(const unsigned int mouseX)
{
    _mouseX=mouseX;
    glutWarpPointer(_mouseX,_mouseY);
}

//Glut2D Class Member Mouse Position Y Mutator
void Glut2D::setMY(const unsigned int mouseY)
{
    _mouseY=mouseY;
    glutWarpPointer(_mouseX,_mouseY);
}

//Glut2D Class Member Mouse X Position Accessor
unsigned int Glut2D::MX() const
{
    return _mouseX;
}

//Glut2D Class Member Mouse Position Y Accessor
unsigned int Glut2D::MY() const
{
    return _mouseY;
}

//Glut2D Class Static Reshape Function(Fixes windows when they are resized)
void Glut2D::reshape(int width,int height)
{
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(_instance[ii]->_windowID==glutGetWindow())
        {
            /*//Reshape Window
            glViewport((width-_instance[ii]->_windowWidth)/2,(height-_instance[ii]->_windowHeight)/2,
                _instance[ii]->_windowWidth,_instance[ii]->_windowHeight);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            //Update Projected View
            glOrtho(0,_instance[ii]->_windowWidth,_instance[ii]->_windowHeight,0,0,1);
            return;*/

            //Set Viewport Size
			glViewport(0,0,width,height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			//Get Original Dimensions
			_instance[ii]->_windowWidth=glutGet(GLUT_INIT_WINDOW_WIDTH);
			_instance[ii]->_windowHeight=glutGet(GLUT_INIT_WINDOW_HEIGHT);

			//If Width Dependent
			if(width<=height)
			{
				double scaler=(double)glutGet(GLUT_WINDOW_HEIGHT)/(double)glutGet(GLUT_WINDOW_WIDTH);
				_instance[ii]->_windowHeight=glutGet(GLUT_INIT_WINDOW_WIDTH)*scaler;
			}

			//If Height Dependent
			else
			{
				double scaler=(double)glutGet(GLUT_WINDOW_WIDTH)/(double)glutGet(GLUT_WINDOW_HEIGHT);
				_instance[ii]->_windowWidth=glutGet(GLUT_INIT_WINDOW_HEIGHT)*scaler;
			}

			//Set View
			glOrtho(0,_instance[ii]->_windowWidth,_instance[ii]->_windowHeight,0,0,1);
			return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid window id!!!");
}

//Glut2D Class Static Window Status Function(Updates window state for all instances of Glut2D)
void Glut2D::windowStatus(int state)
{
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(_instance[ii]->_windowID==glutGetWindow())
        {
            if(state==GLUT_FULLY_RETAINED)
            {
                _instance[ii]->_active=true;
            }
            else
            {
                _instance[ii]->_active=false;
            }

            return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid window id!!!");
}

//Glut2D Class Static Timer Function(Calls the timer function of each instance of GlutInstace)
void Glut2D::timer(int value)
{
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(_instance[ii]->_windowID==glutGetWindow())
        {
            //Update Delta Time
            double nt=glutGet(GLUT_ELAPSED_TIME)*0.001;
            _instance[ii]->_dt=nt-_instance[ii]->_ot;
            _instance[ii]->_ot=nt;

            //Execute Timer Function
            _instance[ii]->_timer(*_instance[ii]);

            //Redraw Screen
            glutPostRedisplay();

            //Call Timer in _timerTime Milisecs
            glutTimerFunc(_instance[ii]->_timerTime,timer,0);

            //Clear Pressed Key Bindings and Return
            clearPressed();
            return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid window id!!!");
}

//Glut2D Class Static Display Function(Calls the display function of each instance of GlutInstace)
void Glut2D::display()
{
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(_instance[ii]->_windowID==glutGetWindow())
        {
            //Clear Screen and Get Ready to Draw
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);

            //Orient to Camera
            glTranslatef(-_instance[ii]->camera.X(),-_instance[ii]->camera.Y(),0.0);
            glRotatef(_instance[ii]->camera.R(),0.0,0.0,1.0);

            //Execute Display Function
            _instance[ii]->_display(*_instance[ii]);

            //Swap Buffers and End Draw
            glutSwapBuffers();
            return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid window id!!!");
}

//Glut2D Class Static Keyboard Down Checker
void Glut2D::keyboardDown(unsigned char key,int x,int y)
{
    if(!_keyboardDown[key])
	{
	    _keyboardPressed[key]=true;
	}

	_keyboardDown[key]=true;
}

//Glut2D Class Static Keyboard Up Checker
void Glut2D::keyboardUp(unsigned char key,int x,int y)
{
    _keyboardDown[key]=false;

    //If Lower Case Update Upper Case
    if((_keyboardDown[key]>=97||_keyboardDown[key]<=122)&&key>=32)
    {
        _keyboardDown[key-32]=false;
    }

    //If Upper Case Update Lower Case
    if((_keyboardDown[key]>=65||_keyboardDown[key]<=90)&&key<=223)
    {
        _keyboardDown[key+32]=false;
    }
}

//Glut2D Class Static Special Down Checker
void Glut2D::specialDown(int key,int x,int y)
{
    if (!_specialDown[key])
    {
        _specialPressed[key]=true;
    }

    _specialDown[key]=true;
}

//Glut2D Class Static Special Up Checker
void Glut2D::specialUp(int key,int x,int y)
{
    _specialDown[key]=false;
}

//Glut2D Class Static Mouse Down Checker
void Glut2D::mouse(int button,int state,int x,int y)
{
    if(!_mouseDown[button]&&!state)
    {
        _mousePressed[button]=true;
    }

    _mouseDown[button]=!state;
}

//Glut2D Class Static Mouse Entry Function(What to do when mouse enters window...use is unknown at the moment...)
void Glut2D::mouseEntry(int state)
{}

//Glut2D Class Static Mouse Motion Function(Updates the mouse coordinates for each instance of Glut2D)
void Glut2D::motion(int x,int y)
{
    for(unsigned int ii=0;ii<_instance.size();++ii)
    {
        if(_instance[ii]->_windowID==glutGetWindow())
        {
            _instance[ii]->_mouseX=x;
            _instance[ii]->_mouseY=y;
            return;
        }
    }

    throw std::runtime_error("Glut2D - Invalid window id!!!");
}

//Glut2D Class Static Input Pressed Clear Function(Flushes input pressed keys)
void Glut2D::clearPressed()
{
    for(int ii=0;ii<256;++ii)
	{
	    _keyboardPressed[ii]=false;
	    _specialPressed[ii]=false;
	}

	for(int ii=0;ii<3;++ii)
	{
	    _mousePressed[ii]=false;
	}
}

//Global Friend Input Down Check Function(Returns true while key is down)
bool input_check(const int key)
{
    if(key>=0x2000)
    {
        return Glut2D::_mouseDown[key-0x2000];
    }
    else if(key>0x1000)
    {
        return Glut2D::_keyboardDown[key-0x1000]+Glut2D::_keyboardDown[key-0x1020];
    }
    else
    {
        return Glut2D::_specialDown[key];
    }
}

//Global Friend Input Pressed Check Function(Returns true when key is pressed)
bool input_check_pressed(const int key)
{
    if(key>=0x2000)
    {
        return Glut2D::_mousePressed[key-0x2000];
    }
    else if(key>0x1000)
    {
        return Glut2D::_keyboardPressed[key-0x1000]+Glut2D::_keyboardPressed[key-0x1020];
    }
    else
    {
        return Glut2D::_specialPressed[key];
    }
}
