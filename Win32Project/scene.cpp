#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
GLuint vbo,ebo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, colorLocation;
GLint texcoordLocation, textureLocation;
GLuint texture;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;
Ground ground;
void Init()
{
	float data[] = {
		-0.2f, -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f,
		0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,1.0f,0.0f,
		0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.5f,1.0f
	};
	glGenBuffers(1, &vbo);//opengl的驱动将变量vbo的地址改为显存中的地址
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//把vbo设置为当前的vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);//操作当前这个GL_ARRAY_BUFFER，在gpu开辟sizeof(float)*12的空间，将data从cpu发送到gpu，把数据data放到显卡上后就不会再修改他了
	glBindBuffer(GL_ARRAY_BUFFER, 0);//设置当前的GL_ARRAY_BUFFER为零，表示把cpu端的数据删掉
	unsigned short indexes[] = { 0,1,2 };//按0，1，2的顺序绘制vbo里的点
	glGenBuffers(1, &ebo);//创建一个ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);//设置当前的element_buffer为ebo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indexes, GL_STATIC_DRAW);//将ebo从cpu的内存块传到显卡上去
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
	ground.Init();
}
void SetViewPortSize(float width, float height)
{
	projectMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}
void Draw()
{
	float frameTime = GetFrameTime();
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);//设置擦除背景的颜色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	ground.Draw(viewMatrix, projectMatrix);
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectMatrix));
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureLocation, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//设置当前的数据集,把vbo设置为当前要绘制图形的数据集，就是程序或者叫shader在绘制的时候去vbo取数据
	glEnableVertexAttribArray(positionLocation);//启用属性组（AttribArray）中positionLocation这个插槽
	//第一个参数：插槽的位置；第二个参数：这个插槽中数据有几个分量；第三个参数：表示每个分量的类型
	//第四个参数：需不需要归一化，假如传入颜色值时255，255，255，他不是浮点数，如果归一化就把255映射为1.0
	//第五个参数：紧挨着的两个点相距多远
	//第六个参数：从vbo的哪个位置开始取值
	//设置这些参数的目的是告诉gpu，如何去遍历vbo这个内存块
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	//第一个参数：表示绘制三角形，每三点个绘制一个面；第二个参数：从第几个点开始绘制；第三个参数：要绘制多少个点
	//这句话在执行的时候，在gpu端，他会遍历vbo中的数据，并分别传入三个不同的shader，这三个shader分别拿到了不同的点，
	//然后他们的viewMatrix，modelmatrix，projectMatrix是一样的，之后这三个点通过shader会在gpu上不同的三个核心（core）上同时执行
	//这个函数的目的：告诉gpu如何把vbo中的数据分发到各个不同的shader，让他们去执行
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*4));
	glEnableVertexAttribArray(texcoordLocation);
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//第二个参数表示画多少个索引数据，也就是ebo里的索引数据用多少个；
	//第三个参数表示ebo里的数据类型；//第四个参数表示开始位置
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}