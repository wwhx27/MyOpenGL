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
			mVertexBuffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 1.0f);
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
}