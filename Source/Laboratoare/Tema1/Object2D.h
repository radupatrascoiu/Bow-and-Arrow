#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	Mesh* CreateRectangle(std::string name, float length, float width, glm::vec3 color, bool fill);
	Mesh* CreateTriangle(std::string name, float length, float width, glm::vec3 color);
	Mesh* CreateBow(std::string name, float radius, glm::vec3 color);
	Mesh* CreateTail(std::string name, float width, float height, glm::vec3 color);
	Mesh* CreateShuriken(std::string name, float length, float width, float width2, glm::vec3 color);
	Mesh* CreateBalloon(std::string name, float radius, glm::vec3 color);
}

