#include "Sphere.h"

#include <iostream>
#include "Config.h"

Sphere::Sphere()
{
	init(30);
}

Sphere::Sphere(const int precision)
{
	init(precision);
}

Sphere::~Sphere()
{
}

float Sphere::toRadians(float degrees)
{
	return (degrees * 2.0f * PI) / 360.0f;
}

void Sphere::init(const int prec)
{
	setNumIndices(prec);
	vertices.resize((prec + 1) * (prec + 1) * 5);
	indices.resize(prec * prec * 6);
	int verticeIndex = 0;
	int indiceIndex = 0;

	//计算三角形顶点坐标
	for (int r = 0; r <= prec; r++)//row
	{
		for (int c = 0; c <= prec; c++)//column
		{
			float xSegment = (float)c / (float)prec;
			float ySegment = (float)r / (float)prec;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			vertices[verticeIndex++] = (xPos);
			vertices[verticeIndex++] = (yPos);
			vertices[verticeIndex++] = (zPos);
					
			vertices[verticeIndex++] = ((float)c / (float)prec);
			vertices[verticeIndex++] = ((float)r / (float)prec);
		}
	}

	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			indices[indiceIndex++] = (i * (prec + 1) + j);
			indices[indiceIndex++] = ((i + 1) * (prec + 1) + j);
			indices[indiceIndex++] = ((i + 1) * (prec + 1) + j + 1);
									 
			indices[indiceIndex++] = (i * (prec + 1) + j);
			indices[indiceIndex++] = ((i + 1) * (prec + 1) + j + 1);
			indices[indiceIndex++] = (i * (prec + 1) + j + 1);
		}
	}
}
