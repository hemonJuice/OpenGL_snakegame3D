#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//#include"Snake.h"
#include<vector>
#include"Food.h"
#include"LoadTexbmp.h"
#include <sstream>	
#include<string>


#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

extern int overBound;
extern bool isEmpty;





float pi = 3.1415926;

//map setting
float map_witdh = 100;
float map_depth = 100;
Snake m_snake;
Food m_food;
float eye[3];
float lookat[3];
int score = 0;
bool GameOver = false;
float lightpos[3][4] = {{0,4,0,0.0},{0,4,0,1.0},{0,4,0,1.0}};
float LightAng = 0;
float timee = 0.0;
GLfloat m_tranlate[3]    = {0,0,-0};

//3 lights
void Light(){
	
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	float Light1AmdDif1[4] = { 0.5,0.2,0.0,1.0 };
	float Light1Spe1[4] =    { 1.0,0.6,0.0,1.0 };
	float spotLightDir1[4] = { sin(LightAng/180.0*pi),1,cos(LightAng/180.0*pi),0};
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos[0]);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  Light1AmdDif1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  Light1AmdDif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Spe1);

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotLightDir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);


	float Light1AmdDif2[4] = { 0.0,0.5,0.4,1.0 };
	float Light1Spe2[4] =    { 0.0,1.0,0.8,1.0 };
	float spotLightDir2[4] = {0,0,0,0};
	glLightfv(GL_LIGHT2, GL_POSITION, lightpos[1]);
	glLightfv(GL_LIGHT2, GL_AMBIENT,  Light1AmdDif2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  Light1AmdDif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light1Spe2);
	spotLightDir2[0] =  sin((LightAng+240.0)/180.0*pi);
	
	spotLightDir2[1] = 1;

	spotLightDir2[2] = cos((LightAng+240.0)/180.0*pi);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLightDir2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);




	float Light1AmdDif3[4] = { 0.4,0.0,0.5,1.0 };
	float Light1Spe3[4] = { 1.0,0.0,1.0,1.0 };
	float spotLightDir3[4] = {0,0,0,0};
	glLightfv(GL_LIGHT3, GL_POSITION, lightpos[2]);
	glLightfv(GL_LIGHT3, GL_AMBIENT,  Light1AmdDif3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  Light1AmdDif3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Light1Spe3);
	spotLightDir3[0] =  sin((LightAng+120.0)/180.0*pi);
	spotLightDir3[1] = 1;
	spotLightDir3[2] = cos((LightAng+120.0)/180.0*pi);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotLightDir3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60.0);

}



void DoRasterString(float x, float y, float z, char* s){
	glRasterPos3f((GLfloat)x, (GLfloat)y, (GLfloat)z);

	char num;			// one character to print
	for (; (num = *s) != '\0'; s++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, num);
	}
}




GLuint TextureImage[6];
void  LoadTextMap(void){
	TextureImage[0] = LoadTexBMP("food.bmp");
	TextureImage[1] = LoadTexBMP("22907.bmp");
	TextureImage[2] = LoadTexBMP("9807.bmp");
	TextureImage[3] = LoadTexBMP("floor.bmp");
	TextureImage[4] = LoadTexBMP("fire.bmp");
	TextureImage[5] = LoadTexBMP("hot_bk.bmp");
}



GLuint SkyTexture[6];
void LoadSky(void){
	SkyTexture[0] = LoadTexBMP("hot_bk.bmp");
	SkyTexture[1] = LoadTexBMP("hot_ft.bmp");
	SkyTexture[2] = LoadTexBMP("floor.bmp");
	SkyTexture[3] = LoadTexBMP("hot_dn.bmp");
	SkyTexture[4] = LoadTexBMP("hot_lf.bmp");
	SkyTexture[5] = LoadTexBMP("hot_rt.bmp");
}

void SkyBox(float x, float y, float z, float width, float height,float length){
	glDisable(GL_LIGHTING);
	glPushMatrix();
    glTranslatef(x,y,z);

    glBindTexture(GL_TEXTURE_2D, SkyTexture[0]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,          z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y,          z + length);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, SkyTexture[1]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,          z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,         y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,         y,          z);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, SkyTexture[2]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,          z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,         y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,         y,          z);

    glEnd();

    glPopMatrix(); 
    glEnable(GL_LIGHTING); 
}

void DrawMap(float x, float y, float z, float width, float height,float length){
	glEnable(GL_LIGHTING);
	glPushMatrix();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);

/*
	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);	
	glBegin(GL_QUADS);
	//glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);	
	//glBegin(GL_QUADS);
	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glNormal3f(1, 0, 0);glVertex3f(-map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0, -map_depth / 2.0); glNormal3f(1, 0, 0);glVertex3f(-map_depth / 2.0, 100, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0,  map_depth / 2.0); glNormal3f(1, 0, 0);glVertex3f(-map_depth / 2.0, 100, map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0,  map_depth / 2.0); glNormal3f(1, 0, 0);glVertex3f(-map_depth / 2.0, 0, map_depth / 2.0);
	//glEnd();
	//glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);	
	//glBegin(GL_QUADS);
	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glNormal3f(-1, 0, 0);glVertex3f(map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0, -map_depth / 2.0); glNormal3f(-1, 0, 0);glVertex3f(map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0,  map_depth / 2.0); glNormal3f(-1, 0, 0);glVertex3f(map_depth / 2.0, 100, map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0,  map_depth / 2.0); glNormal3f(-1, 0, 0);glVertex3f(map_depth / 2.0, 100, -map_depth / 2.0);
	//glEnd();

	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);	
	//glBegin(GL_QUADS);
	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 0, 1);glVertex3f(-map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 0, 1);glVertex3f(map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 0, 1);glVertex3f(-map_depth / 2.0, 100, -map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 0, 1);glVertex3f(map_depth / 2.0, 100, -map_depth / 2.0);
	//glEnd();

	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);	
	//glBegin(GL_QUADS);
	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 0, -1);glVertex3f(-map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 0, -1);glVertex3f(map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 0, -1);glVertex3f(-map_depth / 2.0, 100, map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 0, -1);glVertex3f(map_depth / 2.0, 100, map_depth / 2.0);
	//glEnd();
	glEnd();*/


	glBindTexture(GL_TEXTURE_2D, TextureImage[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 1, 0);glVertex3f(-map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0, -map_depth / 2.0); glNormal3f(0, 1, 0);glVertex3f(map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f( map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 1, 0);glVertex3f(map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0,  map_depth / 2.0); glNormal3f(0, 1, 0);glVertex3f(-map_depth / 2.0, 0, map_depth / 2.0);
	glEnd();
/*	glBindTexture(GL_TEXTURE_2D, TextureImage[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glNormal3f(0, 1, 0);glVertex3f(-map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f(1.0f, 1.0f); glNormal3f(0, 1, 0);glVertex3f(map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f(0.0f, 1.0f); glNormal3f(0, 1, 0);glVertex3f(map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f(0.0f, 0.0f); glNormal3f(0, 1, 0);glVertex3f(-map_depth / 2.0, 0, map_depth / 2.0);
	glEnd();*/
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, SkyTexture[0]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y - 1,z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - 1, z + length);

    glEnd();

	glBindTexture(GL_TEXTURE_2D, SkyTexture[1]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y - 1,z - length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z - length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y + height, z - length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - 1, z - length);

    glEnd();

	glBindTexture(GL_TEXTURE_2D, SkyTexture[3]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y - 1,z - length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y - 1, z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y - 1, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - 1, z - length);

    glEnd(); 
	
	glBindTexture(GL_TEXTURE_2D, SkyTexture[4]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - width, y - 1, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x - width, y + height, z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y + height, z - length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - 1, z - length);

    glEnd(); 

	glBindTexture(GL_TEXTURE_2D, SkyTexture[4]);
    glBegin(GL_QUADS);      

        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y - 1, z - length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z - length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y - 1, z + length);

    glEnd(); 
    glEnable(GL_LIGHTING);


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_LIGHTING);
}

void myTimerFunc(int val){
	if(GameOver){
		timee = timee;
	}else{
		timee += 0.007;
	}
	
	
	glutTimerFunc(1,myTimerFunc,0);
}


void display(){


	char buffer [33];
	sprintf(buffer,"%d",score);


	char buffer1 [100];
	sprintf(buffer1,"%.3f\n",timee);

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	


	DoRasterString(0.1,    0.3, -1, "score:");
	DoRasterString(0.25, 0.3, -1, buffer);

	DoRasterString(-0.3,    0.3, -1, "time:");
	DoRasterString(-0.15, 0.3, -1, buffer1);

	if(isEmpty == true){
		GameOver = true;
	}
	if(overBound == 0){
		GameOver = true;
	}



	if(GameOver){
		DoRasterString(0,  0.0, -1, "Game  Over");
		m_snake.m_MoveSpeed = 0;
		m_snake.gameO();
		/*for(int i = 0; i < 360; i += 1){
			m_snake.ChangeDirection(-1,2);
		}*/
	}
	//else{
	//SkyBox(0,0,0,50,50,50);

	glPushMatrix();
	glColor3f(1.0, 0, 0);


	//glTranslatef(-map_witdh/2.0, 0, -map_depth/2.0);
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], 0, 1, 0);
	Light();
    //CreateSkyBox(0,0,0,100,100,100);

	DrawMap(0,0,0,100,50,100);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
		//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shiny);
	//glDisable(GL_LIGHTING);
	m_snake.Draw(TextureImage);		
	m_food.Draw(TextureImage);
	//m_snake.ChangeDirection(1);//
	//m_snake.MoveForWard();
	glPopMatrix();
	//}
	glutSwapBuffers();
	
}



void ReshapeEvent(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();          
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);	
	
	glLoadIdentity();



	
}




void IdleEvent(){
	std::vector<SinglFood>::iterator iterf;
	for (iterf = m_food.m_food.begin(); iterf != m_food.m_food.end(); iterf++) {
		if (m_snake.CollisonFood((*iterf).mposx, (*iterf).mposz) == true){
			if ((*iterf).mode == 1){
				m_snake.m_MoveSpeed *= 2;
				score += 1;
			}
			else if ((*iterf).mode == 2){
				m_snake.m_MoveSpeed *= 0.5;
				score += 1;
			}
			else if ((*iterf).mode == 3){
				m_snake.removeNode();
				if(score==0){
					score = 0;
				}else{
					score -= 1;
				}
				
			}else if ((*iterf).mode == 4){
				score += 1;
			}
			else{
			    GameOver = true;
			    //score += 1;
			}
			
			m_food.Deal((*iterf).mposx, (*iterf).mposz);
			m_food.GenerateFood(m_snake);

			break;
		}
/*		if(m_snake.CollisonSelf() == true){
			GameOver = true;
		}*/
	}

	lookat[0] = (*m_snake.m_snake.begin()).mposx;
	lookat[1] = 2;
	lookat[2] = (*m_snake.m_snake.begin()).mposz;
	float ang = m_snake.m_MoveAng;
	float dis = 10;
	eye[0] = lookat[0] - dis * cos(ang / 180 * 3.1415926);
	eye[1] = lookat[1] + 3;
	eye[2] = lookat[2] + dis * sin(ang / 180 * 3.1415926);
	m_snake.MoveForWard(0.1);


	
	for(int i = 0; i < 3; i++){
	    lightpos[i][0] = (*m_snake.m_snake.begin()).mposx + 3.0;
	    lightpos[i][1] = (*m_snake.m_snake.begin()).mposz + 3.0;
	    lightpos[i][2] = (*m_snake.m_snake.begin()).mposz + 3.0;

	}
	if(LightAng++ > 360)  LightAng = 0;

	glutPostRedisplay(); 
   
}






void init(){
	LoadTextMap();
	LoadSky();
	glEnable(GL_DEPTH_TEST);
}




void SpecialKey(GLint key, GLint x, GLint y){
	switch (key) {
		case GLUT_KEY_UP:
			m_snake.m_MoveSpeed += 0.01;
			if (m_snake.m_MoveSpeed > 1.0){
				m_snake.m_MoveSpeed = 1.0;
			}
			break;
		case GLUT_KEY_LEFT:
			m_snake.ChangeDirection(-1);
			break;
		case GLUT_KEY_DOWN:
			m_snake.m_MoveSpeed -= 0.01;
			if (m_snake.m_MoveSpeed < 0.05){
				m_snake.m_MoveSpeed = 0.05;
			}
			break;
		case GLUT_KEY_RIGHT:
			m_snake.ChangeDirection(1);
			break;

	}

	
}


int main(int argc, char** argv)
{
	glutInit(&argc, (char**)argv);  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowPosition(110, 120);
	glutInitWindowSize(700, 700);
	glutCreateWindow("project");  
	glutDisplayFunc(display);    
	//glutKeyboardFunc(KeyboardEvent); 
	//glutMouseFunc(MouseEvent);      
	glutReshapeFunc(ReshapeEvent);   
	//glutMotionFunc(MotionEvent);   
	glutIdleFunc(IdleEvent);         
	glutSpecialFunc(&SpecialKey);
	init();
	//glutEntryFunc(MouseEntry);       
	glutTimerFunc(1,myTimerFunc,0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	

	glutMainLoop();                  

	return 0;
}


