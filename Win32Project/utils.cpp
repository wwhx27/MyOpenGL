#include "utils.h"
GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
	GLuint shader = glCreateShader(shaderType);//����shader�����࣬������һ��shader�Ķ���
	glShaderSource(shader, 1, &shaderCode, nullptr);//shader��Ӧ��Դ��
	glCompileShader(shader);//���Կ���������shader
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);//�鿴shader�ı�����
	if (compileResult == GL_FALSE)
	{
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);//��ȡ������־
		printf("Compile Shader fail error log: %s \nshader code:\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);//�༭ʧ�ܺ�ɾ��shader
		shader = 0;
	}
	return shader;
}
GLuint CreateProgram(GLuint vsShader, GLuint fsShader)
{
	GLuint program = glCreateProgram();//����һ������
	glAttachShader(program, vsShader);//������õ�shader�󶨵���һ�������ĳ�����
	glAttachShader(program, fsShader);
	glLinkProgram(program);//���ӳ���
	glDetachShader(program, vsShader);//���Ӻ�shader�ӳ����Ͻ��
	glDetachShader(program, fsShader);
	GLint nResult;
	glGetProgramiv(program, GL_LINK_STATUS, &nResult);//��ȡ��������ӽ��
	if (nResult == GL_FALSE)
	{
		char log[1024] = { 0 };
		GLsizei writed = 0;
		glGetProgramInfoLog(program, 1024, &writed, log);//��ȡ���Ӵ�����־
		printf("create gpu program fail, link error: %s\n", log);
		glDeleteProgram(program);//ɾ������
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
	glGenTextures(1, &texture);//����һ���������
	glBindTexture(GL_TEXTURE_2D, texture);//�Ѹ��½��������������Ϊ��ǰ�������
	//���濪ʼ�����������1��2��3��
	//1.�����������ص���ز���
	//��һ����������ʾ����һ��2d�����ڶ�����������ʾ���������ݱ��Ŵ�ʱ������Ӧ�ò����������㷨ȥ�ɼ����أ�
	//���������������õڶ��������õ��㷨
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//2.��������������صĲ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//3.���������ݴ��ڴ��ϴ����Դ�
	//�ڶ�����������ʾ����ļ���0ʱ�������𣬼���n�Ǿ���n����С��opengl����ݶ���Σ�ȥ���������ѡ��
	//ͬ�������������ȥΪ�������ɫ����������������������������Կ������������ظ�ʽ�����ĸ��������������ݵĿ�
	//������������������ݵĸߡ��������������߿��ȣ�����д0�����߸������������������ڴ�����ʲô��ʽ��
	//�ڰ˸�����������������ÿһ�����������͡�//�ھŸ������������������ڴ��е�λ�ã������λ�ð����������Դ���ȥ
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	//����Ĳ����������ѵ�ǰ��������Ϊ0�����������Ժ�Ĳ����޸ĸ����úõ��������
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
