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