#include "scene.h"
#include "ggl.h"
#include "utils.h"
GLuint vbo,ebo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, colorLocation;
GLint texcoordLocation, textureLocation;
GLuint texture;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;
void Init()
{
	float data[] = {
		-0.2f, -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f,
		0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,1.0f,0.0f,
		0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.5f,1.0f
	};
	glGenBuffers(1, &vbo);//opengl������������vbo�ĵ�ַ��Ϊ�Դ��еĵ�ַ
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//��vbo����Ϊ��ǰ��vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);//������ǰ���GL_ARRAY_BUFFER����gpu����sizeof(float)*12�Ŀռ䣬��data��cpu���͵�gpu��������data�ŵ��Կ��Ϻ�Ͳ������޸�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);//���õ�ǰ��GL_ARRAY_BUFFERΪ�㣬��ʾ��cpu�˵�����ɾ��
	unsigned short indexes[] = { 0,1,2 };//��0��1��2��˳�����vbo��ĵ�
	glGenBuffers(1, &ebo);//����һ��ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//���õ�ǰ��element_bufferΪebo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indexes, GL_STATIC_DRAW);//��ebo��cpu���ڴ�鴫���Կ���ȥ
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	colorLocation = glGetAttribLocation(program, "color");
	texcoordLocation = glGetAttribLocation(program, "texcoord");
	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
	textureLocation = glGetUniformLocation(program, "U_Texture");
	modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
	texture = CreateTexture2DFromBMP("Res/niutou.bmp");
}
void SetViewPortSize(float width, float height)
{
	projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}
void Draw()
{
	float frameTime = GetFrameTime();
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);//���ò�����������ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectMatrix));
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureLocation, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//���õ�ǰ�����ݼ�,��vbo����Ϊ��ǰҪ����ͼ�ε����ݼ������ǳ�����߽�shader�ڻ��Ƶ�ʱ��ȥvboȡ����
	glEnableVertexAttribArray(positionLocation);//���������飨AttribArray����positionLocation������
	//��һ����������۵�λ�ã��ڶ����������������������м�����������������������ʾÿ������������
	//���ĸ��������費��Ҫ��һ�������紫����ɫֵʱ255��255��255�������Ǹ������������һ���Ͱ�255ӳ��Ϊ1.0
	//����������������ŵ�����������Զ
	//��������������vbo���ĸ�λ�ÿ�ʼȡֵ
	//������Щ������Ŀ���Ǹ���gpu�����ȥ����vbo����ڴ��
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	//��һ����������ʾ���������Σ�ÿ���������һ���棻�ڶ����������ӵڼ����㿪ʼ���ƣ�������������Ҫ���ƶ��ٸ���
	//��仰��ִ�е�ʱ����gpu�ˣ��������vbo�е����ݣ����ֱ���������ͬ��shader��������shader�ֱ��õ��˲�ͬ�ĵ㣬
	//Ȼ�����ǵ�viewMatrix��modelmatrix��projectMatrix��һ���ģ�֮����������ͨ��shader����gpu�ϲ�ͬ���������ģ�core����ͬʱִ��
	//���������Ŀ�ģ�����gpu��ΰ�vbo�е����ݷַ���������ͬ��shader��������ȥִ��
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*4));
	glEnableVertexAttribArray(texcoordLocation);
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//�ڶ���������ʾ�����ٸ��������ݣ�Ҳ����ebo������������ö��ٸ���
	//������������ʾebo����������ͣ�//���ĸ�������ʾ��ʼλ��
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}