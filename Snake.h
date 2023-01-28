#ifndef SNAKE_H
#define SNAKE_H
#include<vector>
typedef struct _SnakeNode {
	float mposx;
	float mposz;
	float mDriection[2];
	float mAngle;
}SnakeNode;


class Snake
{
public:
	Snake();
	~Snake();
	void gameO();
	void ChangeDirection(int diretion,int mode = 0);
	void MoveForWard(float t);
	void Draw(GLuint TextureImage[6]);
	bool CollisonFood(float foodx, float foody);
	//bool CollisonBadFood(float foodx, float foody);

	void removeNode();
	std::vector<SnakeNode> m_snake;
	float m_MoveAng;
	float m_MoveSpeed;
//private:
	
	

	float m_MoveMap[2];
	void  Init();
	void  CollisonSelf();
};
#endif
