#include "ground.h"

void Ground::Init()
{
	Vertex vertex[1600];
	for (int z = 0; z < 20; ++z)
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x)
		{
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
			vertex[offset].Position[0] = xStart;
			vertex[offset].Position[1] = -1.0f;
			vertex[offset].Position[2] = zStart;
			vertex[offset].Position[3] = 1.0f;

			vertex[offset + 1].Position[0] = xStart + 10.0f;
			vertex[offset + 1].Position[1] = -1.0f;
			vertex[offset + 1].Position[2] = zStart;
			vertex[offset + 1].Position[3] = 1.0f;

			vertex[offset + 2].Position[0] = xStart;
			vertex[offset + 2].Position[1] = -1.0f;
			vertex[offset + 2].Position[2] = zStart - 10.0f;
			vertex[offset + 2].Position[3] = 1.0f;

			vertex[offset + 3].Position[0] = xStart + 10.0f;
			vertex[offset + 3].Position[1] = -1.0f;
			vertex[offset + 3].Position[2] = zStart - 10.0f;
			vertex[offset + 3].Position[3] = 1.0f;
		}
	}
	mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * 1600, GL_STATIC_DRAW, vertex);
}