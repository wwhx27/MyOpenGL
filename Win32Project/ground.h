#pragma once
#include "utils.h"
#include "vertexbuffer.h"
#include "shader.h"
class Ground
{
	VertexBuffer *mVertexBuffer;
	GLuint mVBO;
	Shader *mShader;
	glm::mat4 mModelMatrix;
// 	GLuint mProgram;
// 	GLint mPositionLocation, mColorLocation, mNormalLocation;
// 	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation;
public:
	void Init();
	void Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
};