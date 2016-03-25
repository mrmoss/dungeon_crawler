//bmp.h
//Created By:  Mike Moss
//Description:  System for loading BMP files into Glut without or with transparency(based on bottom left pixel of file).
//Date:  2011

#ifndef BMP_LOADER_H_INCLUDED
#define BMP_LOADER_H_INCLUDED

//Exception Header
#include <stdexcept>

//File Stream Header
#include <fstream>

//Glut Header
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

//Specific Input Header
#include "specificinput.h"

//Loads a BMP file into a GL Texture
unsigned int loadBMP(const char* filename,const bool transparency=true);

#endif
