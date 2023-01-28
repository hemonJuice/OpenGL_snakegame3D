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
#include <ctime>
#include "food.h"
using namespace std;

//food
int foodAmount = 10;
int indexs = 10;

int FoodX[10];
int FoodZ[10];
bool foodOn = true;

int *randNum(int min,int max){
	int *arr = new int[2*foodAmount];
    int a;
	srand(time(NULL));
	for (size_t i = 0; i < 2*foodAmount; i++){
		a = rand();
		int p = a % (max - min+1) + min;
		arr[i] = p; 
	}

	return arr;	
}

void setFood(){
	int *temp = randNum(2,50);
	for(int k = 0; k < 2*foodAmount; k += 2){
		FoodX[k/2] = temp[k];
		FoodZ[k/2] = temp[k+1];			
	}

}


void drawFood(){


	GLubyte indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 };
    
    
    GLfloat colors[]   = { 
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v1,v2,v3 (front)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v3,v4,v5 (right)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  // v1,v6,v7,v2 (left)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v7,v4,v3,v2 (bottom)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0, }; // v4,v7,v6,v5 (back)   
	
	if(foodOn == true){		
        setFood();
		foodOn = false;
	}
	for(int l = 0; l < indexs; l++){
        	GLfloat vertices[] = {
					    FoodX[l]+1, 1, FoodZ[l],                 // v0 (front)
                        FoodX[l]  , 1, FoodZ[l],                 // v1
                        FoodX[l]  , 0, FoodZ[l],                 // v2
                        FoodX[l]+1, 0, FoodZ[l],                 // v3

                        FoodX[l]+1, 1, FoodZ[l],                 // v0 (right)
                        FoodX[l]+1, 0, FoodZ[l],                 // v3
                        FoodX[l]+1, 0, FoodZ[l]+1,                // v4
                        FoodX[l]+1, 1, FoodZ[l]+1,                 // v5

                        FoodX[l]+1, 1, FoodZ[l],                // v0 (top)
                        FoodX[l]+1, 1, FoodZ[l]+1,                // v5
                        FoodX[l]  , 1, FoodZ[l]+1,                // v6
                        FoodX[l] , 1, FoodZ[l],                // v1

                        FoodX[l]  , 1, FoodZ[l],               // v1 (left)
                        FoodX[l]  , 1, FoodZ[l]+1,               // v6
                        FoodX[l]  , 0, FoodZ[l]+1,               // v7
                        FoodX[l]  , 0, FoodZ[l],                // v2

                        FoodX[l]  , 0, FoodZ[l]+1,               // v7 (bottom)
                        FoodX[l]+1, 0, FoodZ[l]+1,                 // v4
                        FoodX[l]+1, 0, FoodZ[l],                 // v3
                        FoodX[l]  , 0, FoodZ[l],                 // v2

                        FoodX[l]+1, 0, FoodZ[l]+1,                // v4 (back)
                        FoodX[l]  , 0, FoodZ[l]+1,                // v7
                        FoodX[l]  , 1, FoodZ[l]+1,                // v6
                        FoodX[l]+1, 1, FoodZ[l]+1,                 // v5
            
                       };
                    //glEnableClientState(GL_NORMAL_ARRAY);
    		glEnableClientState(GL_COLOR_ARRAY);
    		glEnableClientState(GL_VERTEX_ARRAY);

        	glColorPointer(3, GL_FLOAT, 0, colors);
    		glVertexPointer(3, GL_FLOAT, 0, vertices);


    		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);


    		glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    		glDisableClientState(GL_COLOR_ARRAY);
    		//glDisableClientState(GL_NORMAL_ARRAY);             

        }
                 

/*	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glVertex3f(FoodX,0,FoodZ);
	glVertex3f(FoodX + 1,0,FoodZ);
	glVertex3f(FoodX + 1,0,FoodZ + 1);
	glVertex3f(FoodX,0,FoodZ + 1);
    glEnd();*/	

}