#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "grid.h"
using namespace std;

extern float lookPos[3];
extern float camPos[3];

int gridX;

int gridZ;

void gridCons(int x, int z){
	gridX = x;
	gridZ = z;
}

void oneGrid(int x,int y,int z){
	glLineWidth(1.0);
	glColor3f(1,1,1);
	//gluLookAt(camPos1[0], camPos1[1], camPos1[2], lookPos1[0], lookPos1[1], lookPos1[2], 0, 1, 0);
	glBegin(GL_LINE_LOOP);

	glVertex3i(x,y,z);
	glVertex3i(x + 1,y,z);
	glVertex3i(x + 1,y,z + 1);
    glVertex3i(x,y,z + 1);

    glEnd();
}

void drawGrid(){
	for(int i = 0; i < gridX; i++){
		for(int j = 0; j < gridZ; j++){
			oneGrid(i,0,j);
		}
	}
}