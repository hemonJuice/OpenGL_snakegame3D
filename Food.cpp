#ifndef FOOD_H
#define FOOD_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "Food.h"
#include <math.h>
//#include<random>
#include <stdlib.h>
using namespace std;

#include <time.h> 
#include <iostream>



float ang = 0;
float distance1(float x, float y){
	return sqrt(x*x + y*y);
}


Food::Food(){
	Init();
}


Food::~Food(){
}

void Food::Deal(float x, float z){
	int num = 0;
	std::vector<SinglFood>::iterator ptr;
	for (ptr = m_food.begin(); ptr != m_food.end(); ptr++){
		float dis = distance1((*ptr).mposx -x,(*ptr).mposz -z);
		
		if (dis < 0.1){
			m_food.erase(ptr);
			break;
		}
			
		
	}
	
}


void  Food::Draw(GLuint TextureImage[6]){
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	ang += 1;
	if (ang > 360) ang = 0;
	
	
	for (std::vector<SinglFood>::iterator ptr = m_food.begin(); ptr != m_food.end(); ptr++){
		glPushMatrix();
		glTranslatef((*ptr).mposx, 0.5, (*ptr).mposz);
		glRotatef(ang, 0, 1, 0);
		//glutSolidTorus(0.3,0.5,40,40);

		if((*ptr).mode == 0){
			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextureImage[0]);
		    glutSolidTeapot(0.5);
		    //glDisable(GL_TEXTURE_2D);
		}
		if ((*ptr).mode == 1){
			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextureImage[2]);
			glutSolidTorus(0.3, 0.5, 40, 40);
			//glDisable(GL_TEXTURE_2D);
		}
		if ((*ptr).mode == 2){
			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextureImage[4]);
			glutSolidSphere(0.4, 40, 40);
			//glDisable(GL_TEXTURE_2D);
		}else if ((*ptr).mode == 3){
			//glDisable(GL_LIGHTING);
			//glDisable(GL_TEXTURE_2D);
			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextureImage[1]);
			glColor3f(1,1,1);
			glutWireSphere(0.4, 15, 15);
			//glDisable(GL_TEXTURE_2D);
			//glEnable(GL_LIGHTING);
			//glEnable(GL_TEXTURE_2D);
		}
		/*if ((*ptr).mode == 4){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextureImage[4]);
			glutSolidCube(0.5);
			glDisable(GL_TEXTURE_2D);
		}*/
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
}


void Food::GenerateFood(Snake snake){
	SinglFood m_SinglFood;
	srand( time(NULL) );
	m_SinglFood.mposx = rand() / (float)RAND_MAX * m_MoveMap[0] - m_MoveMap[0]/ 2;
	m_SinglFood.mposz = rand() / (float)RAND_MAX * m_MoveMap[1] - m_MoveMap[1] / 2;
	m_SinglFood.mode = (rand() % (4-0))+ 0;

	m_food.push_back(m_SinglFood);
}

int total = 50;
void Food::Init(){ 
	m_food.clear();
	
	m_MoveMap[0] = 70;
	m_MoveMap[1] = 70;

	for (int i = 0; i < total; i++){
		SinglFood m_SinglFood;
		m_SinglFood.mposx = rand()/(float)RAND_MAX * m_MoveMap[0] - m_MoveMap[0] / 2;
		m_SinglFood.mposz = rand()/(float)RAND_MAX * m_MoveMap[1] - m_MoveMap[1] / 2;
		m_SinglFood.mode = (rand() % (4-0))+ 0;
		m_food.push_back(m_SinglFood);
	}
}
	


#endif	