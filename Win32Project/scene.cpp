#include "scene.h"
#include "ggl.h"
GLuint vbo;
void Init()
{
	float data[] = {
		-0.2f, -0.2f, -0.6f, 1.0f,
		0.2f, 0.2f, -0.6f, 1.0f,
		0.0f, 0.2f, -0.6f, 1.0f
	};
	glGenBuffers(1, &vbo);//opengl������������vbo�ĵ�ַ��Ϊ�Դ��еĵ�ַ
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//��vbo����Ϊ��ǰ��vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);//������ǰ���GL_ARRAY_BUFFER����gpu����sizeof(float)*12�Ŀռ䣬��data��cpu���͵�gpu��������data�ŵ��Կ��Ϻ�Ͳ������޸�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);//���õ�ǰ��GL_ARRAY_BUFFERΪ�㣬��ʾ��cpu�˵�����ɾ��
}
void SetViewPortSize(float width, float height)
{

}
void Draw()
{

}