#include<vector>
#include"Snake.h"
using namespace std;
typedef struct _SinglFood 
{
	float mposx;
	float mposz;
	int mode;
}SinglFood;

class Food
{
public:
	 Food();
	~Food();
	void GenerateFood(Snake snake);
	void Init();
	void Deal(float x, float z);
	void Draw(GLuint TextureImage[6]);
	std::vector<SinglFood> m_food;
private:
	float m_MoveMap[2];
	
	//int m_count;
};

