#include "Object2D.h"
#include <Core/Engine.h>
#define TWO_PI			(6.28318530718f)


// arc
Mesh* Object2D::CreateBow(std::string name, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	int line = 0;
	for (float i = 0.0; i <= TWO_PI / 2; i += 0.01)
	{
		vertices.emplace_back(glm::vec3(sin(i) * radius / 2, cos(i) * radius, 0), color);
		indices.push_back(line++);
	}

	Mesh* bow = new Mesh(name);
	bow->InitFromData(vertices, indices);
	bow->SetDrawMode(GL_LINE_LOOP);
	return bow;
}

// varful la sageata
Mesh* Object2D::CreateTriangle(std::string name, float length, float width, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0,  0), color),
		VertexFormat(glm::vec3(length, width / 2,  0), color),
		VertexFormat(glm::vec3(0, width,  0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };
	triangle->InitFromData(vertices, indices);
	return triangle;
}

// linie
Mesh* Object2D::CreateRectangle(std::string name, float length, float width, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, width, 0), color),
		VertexFormat(glm::vec3(0, width, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

// cercul de la balon
Mesh* Object2D::CreateBalloon(std::string name, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	int line = 0;
	for (float i = 0.0; i <= TWO_PI; i += 0.01)
	{	
		// de modificat
		vertices.emplace_back(glm::vec3(sin(i) * radius / 1.75, cos(i) * radius, 0), color);
		indices.push_back(line++);
	}

	Mesh* circle = new Mesh(name);
	circle->InitFromData(vertices, indices);
	circle->SetDrawMode(GL_POLYGON);
	return circle;
}

// coada de la balon
Mesh* Object2D::CreateTail(std::string name, float width, float height, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(width, height * 4,  0), color),
		VertexFormat(glm::vec3(0, height * 3,  0), color),
		VertexFormat(glm::vec3(width, height * 2,  0), color),
		VertexFormat(glm::vec3(0, height, 0), color),
		VertexFormat(glm::vec3(width, 0, 0), color),
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 1, 2, 2, 3, 3, 4 };

	line->InitFromData(vertices, indices);
	line->SetDrawMode(GL_LINES);
	return line;
}

// shuriken
Mesh* Object2D::CreateShuriken(std::string name, float width, float length, float width2, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(width, length,  10), color),
		VertexFormat(glm::vec3(0, length + 25,  10), color),
		VertexFormat(glm::vec3(width, length + 25,  10), color),
		VertexFormat(glm::vec3(width2, length + 25,  10), color),
		VertexFormat(glm::vec3(width2, length,  10), color),
		VertexFormat(glm::vec3(width2, 0,  10), color),
		VertexFormat(glm::vec3(width, 0,  10), color),
		VertexFormat(glm::vec3(0, 0,  10), color),
		VertexFormat(glm::vec3(0, length,  10), color)
	};

	Mesh* shuriken = new Mesh(name);
	// clockwise
	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 3, 4,
		5, 6, 0,
		0, 7, 8
	};

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}