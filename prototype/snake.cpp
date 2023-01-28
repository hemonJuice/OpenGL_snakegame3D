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
#include "snake.h"

using namespace std;

//snake

extern int FoodX[10];
extern int FoodZ[10];
extern bool foodOn;
extern int indexs;


int posX[50] = {25,24,23,22};
int posZ[50] = {25,25,25,25};
int snakeLength = 4;
int direction = 0;





bool touchBound = false;

float lookPos[3];// = {posX[0]+0.5,0.5,posZ[0]+0.5};
float camPos[3] = {25,25,0};// = {50, 50, -25};





void drawSnake(){

/*
	if(snakeLength > 4){
	
	}*/
	GLubyte indices[]  = { 
					   0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 }; 

    GLfloat colors1[]   = { 
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v1,v2,v3 (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v5,v6,v1 (top)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  // v1,v6,v7,v2 (left)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0 }; // v4,v7,v6,v5 (back)  

    GLfloat colors2[]   = { 
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v3,v4,v5 (right)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,  // v0,v5,v6,v1 (top)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,  // v1,v6,v7,v2 (left)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v7,v4,v3,v2 (bottom)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1 }; // v4,v7,v6,v5 (back)                        

	if(touchBound == false){

		for(int i = snakeLength - 1 ; i > 0; i--){
			posX[i] = posX[i - 1];
			posZ[i] = posZ[i - 1];
		}	


		if(direction == 1){
			posX[0]--;
			//camPos[0] = posX[0] + 20;
			//camPos[1] = 15;
			//camPos[2] = posZ[0] + 0.5;
			direction = 0;
			//lookPos[0]--;
		}else if(direction == -1){
			posX[0]++;
			//camPos[0] = posX[0] - 20;
			//camPos[1] = 15;
			//camPos[2] = posZ[0] + 0.5;
			direction = 0;
			//lookPos[0]++;
		}else if(direction == 2){
			posZ[0]++;
			//camPos[0] = posX[0] + 0.5;
			//camPos[1] = 15;
			//camPos[2] = posZ[0] - 20;
			direction = 0;
		}else if(direction == -2){
			posZ[0]--;
			//camPos[0] = posX[0] + 0.5;
			//camPos[1] = 15;
			//camPos[2] = posZ[0] + 20;
			direction = 0;
		}
		lookPos[0] = posX[0]+0.5;
		lookPos[1] = 0.5;
		lookPos[2] = posZ[0]+0.5;

		gluLookAt(camPos[0], camPos[1], camPos[2], lookPos[0], lookPos[1], lookPos[2], 0, 1, 0);

        for(int j = 0; j < snakeLength; j++){
        	
			GLfloat vertices[] = {
					    posX[j]+1, 1, posZ[j],   //0, 0, 1,   1, 1, 1,              // v0 (front)
                        posX[j]  , 1, posZ[j],   //0, 0, 1,   1, 1, 0,              // v1
                        posX[j]  , 0, posZ[j],   //0, 0, 1,   1, 0, 0,              // v2
                        posX[j]+1, 0, posZ[j],   //0, 0, 1,   1, 0, 1,              // v3

                        posX[j]+1, 1, posZ[j],   //1, 0, 0,   1, 1, 1,              // v0 (right)
                        posX[j]+1, 0, posZ[j],   //1, 0, 0,   1, 0, 1,              // v3
                        posX[j]+1, 0, posZ[j]+1,   //1, 0, 0,   0, 0, 1,              // v4
                        posX[j]+1, 1, posZ[j]+1,   //1, 0, 0,   0, 1, 1,              // v5

                        posX[j]+1, 1, posZ[j],   //0, 1, 0,   1, 1, 1,              // v0 (top)
                        posX[j]+1, 1, posZ[j]+1,   //0, 1, 0,   0, 1, 1,              // v5
                        posX[j]  , 1, posZ[j]+1,   //0, 1, 0,   0, 1, 0,              // v6
                        posX[j]  , 1, posZ[j],   //0, 1, 0,   1, 1, 0,              // v1

                        posX[j]  , 1, posZ[j],  //-1, 0, 0,   1, 1, 0,              // v1 (left)
                        posX[j]  , 1, posZ[j]+1,  //-1, 0, 0,   0, 1, 0,              // v6
                        posX[j]  , 0, posZ[j]+1,  //-1, 0, 0,   0, 0, 0,              // v7
                        posX[j]  , 0, posZ[j],  //-1, 0, 0,   1, 0, 0,              // v2

                        posX[j]  , 0, posZ[j]+1,   //0,-1, 0,   0, 0, 0,              // v7 (bottom)
                        posX[j]+1, 0, posZ[j]+1,   //0,-1, 0,   0, 0, 1,              // v4
                        posX[j]+1, 0, posZ[j],   //0,-1, 0,   1, 0, 1,              // v3
                        posX[j]  , 0, posZ[j],   //0,-1, 0,   1, 0, 0,              // v2

                        posX[j]+1, 0, posZ[j]+1,   //0, 0,-1,   0, 0, 1,              // v4 (back)
                        posX[j]  , 0, posZ[j]+1,   //0, 0,-1,   0, 0, 0,              // v7
                        posX[j]  , 1, posZ[j]+1,   //0, 0,-1,   0, 1, 0,              // v6
                        posX[j]+1, 1, posZ[j]+1,   //0, 0,-1,   0, 1, 1               // v5
            
                       };

                   	
        

            //glEnableClientState(GL_NORMAL_ARRAY);
    		glEnableClientState(GL_COLOR_ARRAY);
    		glEnableClientState(GL_VERTEX_ARRAY);

            

            if(j == 0){
            	glColorPointer(3, GL_FLOAT, 0, colors1);
            }else{
            	glColorPointer(3, GL_FLOAT, 0, colors2);
            }
    		glVertexPointer(3, GL_FLOAT, 0, vertices);


    		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);


    		glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    		glDisableClientState(GL_COLOR_ARRAY);
    		//glDisableClientState(GL_NORMAL_ARRAY);        

        }          
/*		for(int j = 0; j < snakeLength; j++){
			glBegin(GL_QUADS);
			glColor3f(1,0,0);
			glVertex3f(posX[j],0,posZ[j]);
			glVertex3f(posX[j] + 1,0,posZ[j]);
			glVertex3f(posX[j] + 1,0,posZ[j] + 1);
			glVertex3f(posX[j],0,posZ[j] + 1);
			glEnd();
		}*/

		for(int k = 0; k < 10; k++){
			if(posX[0] == FoodX[k] && posZ[0] == FoodZ[k]){
				snakeLength++;
				for(int a = k; k < 9; k++){
					FoodX[a] = FoodX[a+1];
					FoodZ[a] = FoodZ[a+1];
					break;
				}
				indexs--;
                //setOneFood();

				//foodOn = true;
			}	
		}


		
        if(posX[0] == 0 || posX[0] == 50-1 || posZ[0] == 0 || posZ[0] == 50-1){
			snakeLength--;
			touchBound = true;
		}	
	}
}




