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