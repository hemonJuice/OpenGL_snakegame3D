#include"LoadTexbmp.h"


static void Reverse(void* x, const int n){
	int k;
	char* ch = (char*)x;
	for (k = 0; k < n / 2; k++)
	{
		char tmp = ch[k];
		ch[k] = ch[n - 1 - k];
		ch[n - 1 - k] = tmp;
	}
}






GLuint LoadTexBMP(const char* file){
	GLuint   texture;    
	FILE*          f;          
	unsigned short magic;     
	unsigned int dx;
	unsigned int dy;
	unsigned int size;
	unsigned short nbp;
	unsigned short bpp;
	GLubyte* image;      
	unsigned int   off;        
	unsigned int   k;          

	f = fopen(file,"rb");
	if (!f) {
		exit(0);
	}
   //  Check image magic
	fread(&magic, 2, 1, f);
	fseek(f, 8, SEEK_CUR);
	fread(&off, 4, 1, f);
		
	fseek(f, 4, SEEK_CUR);
	fread(&dx, 4, 1, f);
	fread(&dy, 4, 1, f);
	fread(&nbp, 2, 1, f);
	fread(&bpp, 2, 1, f);
	fread(&k, 4, 1, f);
	

	if (magic != 0x4D42 && magic != 0x424D){
		exit(0);
	}


	if (magic==0x424D)
	{
		Reverse(&off,4);
		Reverse(&dx,4);
		Reverse(&dy,4);
		Reverse(&nbp,2);
		Reverse(&bpp,2);
		Reverse(&k,4);
	}


	size = 3*dx*dy;
	image = (GLubyte*)(malloc(size));
	if (!image) {}

		if (fseek(f, off, SEEK_SET) || fread(image, size, 1, f) != 1) {}
			fclose(f);

		for (k=0;k<size;k+=3)
		{
			GLubyte temp = image[k];
			image[k]  = image[k+2];
			image[k+2] = temp;
		}



		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);

		glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		free(image);

		return texture;
	}
