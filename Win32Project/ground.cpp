#include "ground.h"

void Ground::Init()
{
	mVertexBuffer = new VertexBuffer;
	mVertexBuffer->SetSize(1600);
	for (int z = 0; z < 20; ++z)
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x)
		{
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
// 			vertex[offset].Position[0] = xStart;
// 			vertex[offset].Position[1] = -1.0f;
// 			vertex[offset].Position[2] = zStart;
// 			vertex[offset].Position[3] = 1.0f;
// 
// 			vertex[offset + 1].Position[0] = xStart + 10.0f;
// 			vertex[offset + 1].Position[1] = -1.0f;
// 			vertex[offset + 1].Position[2] = zStart;
// 			vertex[offset + 1].Position[3] = 1.0f;
// 
// 			vertex[offset + 2].Position[0] = xStart;
// 			vertex[offset + 2].Position[1] = -1.0f;
// 			vertex[offset + 2].Position[2] = zStart - 10.0f;
// 			vertex[offset + 2].Position[3] = 1.0f;
// 
// 			vertex[offset + 3].Position[0] = xStart + 10.0f;
// 			vertex[offset + 3].Position[1] = -1.0f;
// 			vertex[offset + 3].Position[2] = zStart - 10.0f;
// 			vertex[offset + 3].Position[3] = 1.0f;
			mVertexBuffer->SetPosition(offset, xStart, -1.0f, zStart);
			mVertexBuffer->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
			mVertexBuffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
			mVertexBuffer->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);
			
			mVertexBuffer->SetNormal(offset, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);

			if ((z % 2) ^ (x % 2)) //异或运算，相同为0，不同为1。0^0 =0;  0^1=1;  1^1=0; 1^0=1;
			{
				mVertexBuffer->SetColor(offset, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 1, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 2, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 3, 0.1f, 0.1f, 0.1f);
			}
			else
			{
				mVertexBuffer->SetColor(offset, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 1, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 2, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 3, 0.8f, 0.8f, 0.8f);
			}
		}
	}
	//mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * 1600, GL_STATIC_DRAW, vertex);
	mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex)*mVertexBuffer->mVertexCount, GL_STATIC_DRAW, mVertexBuffer->mVertexes);
// 	int fileSize = 0;
// 	unsigned char* shaderCode = LoadFileContent("Res/ground.vs", fileSize);
// 	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
// 	delete shaderCode;
// 	shaderCode = LoadFileContent("Res/ground.fs", fileSize);
// 	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
// 	delete shaderCode;
// 	mProgram = CreateProgram(vsShader, fsShader);
// 	glDeleteShader(vsShader);
// 	glDeleteShader(fsShader);
// 	mPositionLocation = glGetAttribLocation(mProgram, "position");
// 	mColorLocation = glGetAttribLocation(mProgram, "color");
// 	mNormalLocation = glGetAttribLocation(mProgram, "normal");
// 	mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
// 	mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
// 	mProjectionMatrixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
	mShader = new Shader;
	mShader->Init("Res/ground.vs", "Res/ground.fs");
}

void Ground::Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	glEnable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	mShader->Bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	for (int i = 0; i < 400; ++i)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
