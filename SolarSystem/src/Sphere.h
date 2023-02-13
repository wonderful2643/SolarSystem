#pragma once

#include <cmath>
#include <vector>

class Sphere
{
public:
	Sphere();
	Sphere(const int precision);	// precision代表球体纵横划分的网格数，越大越球体精细
	~Sphere();

	//int getNumVertices()const { return numVertices; }
	int getNumIndices()const { return numIndices; }
	void setNumIndices(const int prec) { numIndices = prec * prec * 6; }
	std::vector<unsigned int> getIndices()const { return indices; }
	std::vector<float> getVertices()const { return vertices; }
private:
	//int numVertices;
	int numIndices;
	std::vector<unsigned int> indices;
	std::vector<float> vertices;
private:
	float toRadians(float degrees);
	void init(int prec);
};

