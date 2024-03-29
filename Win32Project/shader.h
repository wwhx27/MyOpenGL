#pragma once
#include "ggl.h"
class Shader
{
public:
	GLuint mProgram;
	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation;
	GLint mPositionLocation, mColorLocation, mNormalLocation, mTexcoordLocation;
	void Init(const char* vs, const char* fs);
	void Bind(float* M, float* V, float* P);
};

