#include "utils.h"
GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
	GLuint shader = glCreateShader(shaderType);//根据shader的种类，来创建一个shader的对象
	glShaderSource(shader, 1, &shaderCode, nullptr);//shader对应的源码
	glCompileShader(shader);//用显卡驱动编译shader
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);//查看shader的编译结果
	if (compileResult == GL_FALSE)
	{
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);//获取错误日志
		printf("Compile Shader fail error log: %s \nshader code:\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);//编辑失败后删除shader
		shader = 0;
	}
	return shader;
}
GLuint CreateProgram(GLuint vsShader, GLuint fsShader)
{
	GLuint program = glCreateProgram();//创建一个程序
	glAttachShader(program, vsShader);//将编译好的shader绑定到上一步创建的程序上
	glAttachShader(program, fsShader);
	glLinkProgram(program);//链接程序
	glDetachShader(program, vsShader);//链接后将shader从程序上解绑
	glDetachShader(program, fsShader);
	GLint nResult;
	glGetProgramiv(program, GL_LINK_STATUS, &nResult);//获取程序的链接结果
	if (nResult == GL_FALSE)
	{
		char log[1024] = { 0 };
		GLsizei writed = 0;
		glGetProgramInfoLog(program, 1024, &writed, log);//获取链接错误日志
		printf("create gpu program fail, link error: %s\n", log);
		glDeleteProgram(program);//删除程序
		program = 0;
	}
	return program;
}

unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		for (int i = 0; i < width*height * 3; i += 3)
		{
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	return nullptr;
}

GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	glGenTextures(1, &texture);//生成一个纹理对象
	glBindTexture(GL_TEXTURE_2D, texture);//把刚新建的纹理对象设置为当前纹理对象
	//下面开始操作这个纹理（1，2，3）
	//1.设置纹理像素的相关参数
	//第一个参数：表示操作一个2d纹理；第二个参数：表示当纹理数据被放大时，我们应该采用怎样的算法去采集像素；
	//第三个参数：设置第二个参数用的算法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//2.设置纹理坐标相关的参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//3.将纹理数据从内存上传到显存
	//第二个参数：表示纹理的级别，0时基本级别，级别n是经过n级缩小；opengl会根据多边形，去纹理对象中选择不
	//同级别的像素数据去为多边形着色。第三个参数：你的纹理数据在显卡是怎样的像素格式。第四个参数：像素数据的宽
	//第五个参数：像素数据的高。第六个参数：边框宽度，必须写0；第七个参数：纹理数据在内存上是什么格式。
	//第八个参数：像素数据中每一个分量的类型。//第九个参数：像素数据在内存中的位置，从这个位置把他拷贝到显存上去
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	//纹理的操作结束。把当前纹理设置为0号纹理，以免以后的操作修改刚设置好的纹理对象
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

GLuint CreateTexture2DFromBMP(const char* bmpPath)
{
	int nFileSize = 0;
	unsigned char *bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (bmpFileContent == nullptr)
	{
		return 0;
	}
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char* pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	if (bmpWidth == 0)
	{
		delete bmpFileContent;
		return 0;
	}
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	delete bmpFileContent;
	return texture;
}

GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data /*= nullptr*/)
{
	GLuint object;
	glGenBuffers(1, &object);
	glBindBuffer(bufferType, object);
	glBufferData(bufferType, size, data, usage);
	glBindBuffer(bufferType, 0);
	return object;
}
