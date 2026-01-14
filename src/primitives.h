#pragma once
#include "glm.h"

struct Vertex {
	glm::vec3 position;
};

struct Triangle {
	Vertex v0;
	Vertex v1;
	Vertex v2;
};