#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include "Snake.h"

#include<math.h>
#include "stdio.h"
#include<iostream>

#define Pi 3.1415926
int overBound = 1;
bool isEmpty = false;

bool materMode = false;

float beginAng = 90;

float m_amb[4] = {0.3,0.2,0.1,1.0};
float m_dif[4] = {0.5,0.1,0.2,1.0};
float m_spec[4]={0.9,0.3,0.2,1.0};
float  m_shiny = 10;

Snake::Snake()
{
	Init();
}




Snake::~Snake()
{
}

float distance(float x, float y){
	return sqrt(x*x + y*y);
}


void Snake::gameO(){
	float ang1 = 1;
	m_MoveAng -= ang1;
}


void  Snake::ChangeDirection(int diretion, int mode){
	float delteAng = 3;
	m_MoveAng -= diretion * delteAng;

	
	if(fabs(m_MoveAng - beginAng) > 30){
		m_MoveAng += diretion * delteAng;
	}

	(*m_snake.begin()).mAngle = m_MoveAng;


	if(mode == 2){
		delteAng = 0.001;
	}
}

void  Snake::MoveForWard(float t){
	std::vector<SnakeNode>::iterator prePtr;
	std::vector<SnakeNode>::iterator ptr;
	//CollisonSelf();
	for (ptr = m_snake.begin(); ptr != m_snake.end(); ptr++)
	{

		if (ptr == m_snake.begin()){
			beginAng = m_MoveAng;
			float a = sin(m_MoveAng / 180.0*Pi);

			(*ptr).mposx += cos(m_MoveAng/180.0*Pi) * m_MoveSpeed*t;
			(*ptr).mposz += -sin(m_MoveAng / 180.0*Pi) * m_MoveSpeed*t;
		}

		else{

			float directonX = (*prePtr).mposx - (*ptr).mposx;
			float directonZ = (*prePtr).mposz - (*ptr).mposz;
			directonX = directonX/ distance(directonX, directonZ);
			directonZ = directonZ / distance(directonX, directonZ);

			(*ptr).mposx += directonX * m_MoveSpeed * t;
			(*ptr).mposz += directonZ * m_MoveSpeed * t;
			(*ptr).mDriection[0] = directonX;
			(*ptr).mDriection[1] = directonZ;
			(*ptr).mAngle = atan(directonZ / directonX);
			if (directonZ < 0){
				(*ptr).mAngle = -(*ptr).mAngle;
			}
		}
	  
		prePtr = ptr;	
	}
}


void  Snake::Draw(GLuint TextureImage[6]){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	float x = 0; float y = 0;

	materMode = true;
	if(m_snake.empty()){
		isEmpty = true;
	}

	for (std::vector<SnakeNode>::iterator ptr = m_snake.begin(); ptr != m_snake.end(); ptr++){
		glPushMatrix();
		//glDisable(GL_TEXTURE_2D);
		//glEnable(GL_LIGHTING);
				//std::cout<< (*ptr).mposx <<std::endl;
		//std::cout<< overBound <<std::endl;
		//printf((*ptr).mposx);
		glEnable(GL_TEXTURE_2D);

		
		if (ptr == m_snake.begin()){
			if ((*ptr).mposx > 50){
				//std::cout<< "hit1111111111111111111111111" <<std::endl;
				overBound = 0;
				//glutPostRedisplay(); 

			}
			if ((*ptr).mposx < -50){
				//std::cout<< "hit1111111111111111111111111" <<std::endl;
				overBound = 0;
				//glutPostRedisplay(); 
			}
			if ((*ptr).mposz > 50){
				//std::cout<< "hit111111111111111111111111111111111" <<std::endl;
				overBound = 0;
			}
			if ((*ptr).mposz < -50){
				//std::cout<< "hit111111111111111111111111111111" <<std::endl;
				overBound = 0;
			}
		}

		glTranslatef((*ptr).mposx , 0, (*ptr).mposz);
		glRotatef((*ptr).mAngle, 0, 1, 0);
	   



	   if(ptr == m_snake.begin()){
	   		glEnable(GL_TEXTURE_2D);
	   		glBindTexture(GL_TEXTURE_2D, TextureImage[4]);
	   		glutSolidCube(1.0);
	   		glDisable(GL_TEXTURE_2D);
	   }
		

	   else if (ptr == m_snake.end()){
		   glutSolidSphere(0.5,20,20);
	   }
	   else	{
	   	   glutSolidSphere(0.5, 20, 20);
	   }    
	   //glDisable(GL_LIGHTING);	 	   
	   glPopMatrix();

	   materMode = false;
	}
	glDisable(GL_TEXTURE_2D);

}

bool Snake::CollisonFood(float foodx,float foody){

	
	float dis = sqrt((foodx - (*m_snake.begin()).mposx)*(foodx - (*m_snake.begin()).mposx) + (foody - (*m_snake.begin()).mposz)*(foody - (*m_snake.begin()).mposz));
	

	if (dis < 0.9){
	
		SnakeNode snake;	
		snake.mAngle = m_snake.at(m_snake.size()-1).mAngle;
		snake.mDriection[0] = m_snake.at(m_snake.size()-1).mDriection[0];
		snake.mDriection[1] = m_snake.at(m_snake.size()-1).mDriection[1];
		snake.mposx = m_snake.at(m_snake.size()-1).mposx - snake.mDriection[0];
		snake.mposz = m_snake.at(m_snake.size()-1).mposz - snake.mDriection[1];
		m_snake.push_back(snake);
		return true;

	}
		

	return false;
}
void Snake::removeNode(){
	m_snake.pop_back();
	m_snake.pop_back();
}


/*void BadFood(float foodx, float foody){
	float dis = sqrt((foodx - (*m_snake.begin()).mposx)*(foodx - (*m_snake.begin()).mposx) + (foody - (*m_snake.begin()).mposz)*(foody - (*m_snake.begin()).mposz));
	if (dis < 1){
		m_snake.pop_back();
		return true;
	}
	return false;
}*/

void  Snake::Init(){
	m_snake.clear();
	
	m_MoveSpeed = 1;
	m_MoveAng = 90;
	m_MoveMap[0] = 100;
	m_MoveMap[1] = 100;

	int xpos = 0;
	int zpos = 0;

	
	for (int i = 0; i < 4; i++){
		SnakeNode snake;
		snake.mDriection[0] = 0;
		snake.mDriection[1] = -1;
		snake.mAngle = 90.0;
		snake.mposx = xpos + 0.5;
		snake.mposz = zpos + 0.5 + i;

		m_snake.push_back(snake);
	}
}
