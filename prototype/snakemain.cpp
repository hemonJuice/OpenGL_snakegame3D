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
#include "snake.h"
#include "food.h"
using namespace std;
 

extern int direction;
extern float lookPos[];
extern float camPos[];
extern int FoodX[10];


float lookPos1[] = {lookPos[0],lookPos[1],lookPos[2]};
float camPos1[] = {camPos[0], camPos[1], camPos[2]};

int x = 50;
int y = 50;



void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	gridCons(x,y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    /* Sets projection to perspective */
	gluPerspective(45, 1, 1, 1000);
}

void display(){


	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	//gluLookAt(camPos1[0], camPos1[1], camPos1[2], lookPos1[0], lookPos1[1], lookPos1[2], 0, 1, 0);
    
    glPushMatrix();
	
	drawSnake();
	drawGrid();
    
	drawFood();

	
	glPopMatrix();
	
/*	glPushMatrix();
	drawSnake();

	glPopMatrix();
    
    glPushMatrix();

	drawFood();
	glPopMatrix();*/
    

	glutSwapBuffers();
}


void SpecialKey(GLint key,GLint x,GLint y){
	switch (key){
		case GLUT_KEY_UP:
            direction = 2;
            break;
		case GLUT_KEY_DOWN:
		    direction = -2;
		    break;

		case GLUT_KEY_LEFT:
		    direction = -1;
		    break;
		case GLUT_KEY_RIGHT:
		    direction = 1;
		    break;
	}

}

void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(70,FPS,0);
}

int main (int argc,char** argv){

    //setFood();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
    glutCreateWindow("snake");
    glutDisplayFunc(display);


    cout << FoodX[0] << ' '<< FoodX[1] <<endl;
    glutTimerFunc(0,FPS,0);
    glutSpecialFunc(SpecialKey);
    init();
    glutMainLoop();		

	return 0;
} 