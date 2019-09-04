#pragma once
#include "ggl.h"
class shader
{
public:
	GLuint mProgram;
	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation;
	GLint mPositionLocation, mColorLocation, mNormalLocation, mTexcoordLocation;
	void init(const char* vs, const char* fs);
};

