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
	glGenBuffers(1, &vbo);//opengl的驱动将变量vbo的地址改为显存中的地址
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//把vbo设置为当前的vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);//操作当前这个GL_ARRAY_BUFFER，在gpu开辟sizeof(float)*12的空间，将data从cpu发送到gpu，把数据data放到显卡上后就不会再修改他了
	glBindBuffer(GL_ARRAY_BUFFER, 0);//设置当前的GL_ARRAY_BUFFER为零，表示把cpu端的数据删掉
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