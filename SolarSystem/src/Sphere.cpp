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

void Sphere::init(int prec)
{
	setNumIndices(prec);

	//计算三角形顶点坐标
	for (int y = 0; y <= prec; y++)
	{
		for (int x = 0; x <= prec; x++)
		{
			float xSegment = (float)x / (float)prec;
			float ySegment = (float)y / (float)prec;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			vertices.push_back(xPos);
			vertices.push_back(yPos);
			vertices.push_back(zPos);

			vertices.push_back((float)x / (float)prec);
			vertices.push_back((float)y / (float)prec);
		}
	}

	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			indices.push_back(i * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + j + 1);

			indices.push_back(i * (prec + 1) + j);
			indices.push_back((i + 1) * (prec + 1) + j + 1);
			indices.push_back(i * (prec + 1) + j + 1);
		}
	}
}
