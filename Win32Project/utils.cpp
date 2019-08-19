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