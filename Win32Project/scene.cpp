#include "scene.h"
#include "ggl.h"
#include "utils.h"
GLuint vbo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;
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
	int fileSize = 0;
	unsigned char* shaderCode = LoadFileContent("Res/test.vs", fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	delete shaderCode;
	shaderCode = LoadFileContent("Res/test.fs", fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	delete shaderCode;
	program = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	positionLocation = glGetAttribLocation(program, "position");
	modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");
}
void SetViewPortSize(float width, float height)
{
	projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}
void Draw()
{
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectMatrix));
	glUseProgram(0);
}