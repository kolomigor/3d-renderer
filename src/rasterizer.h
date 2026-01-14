#pragma once
#include "picture.h"
#include <glm/glm.hpp>

struct ScreenVertex {
	float x;
	float y;
	float depth;
};

class Rasterizer {
public:
	static void RasterizeTriangle(const ScreenVertex& a, const ScreenVertex& b,
	                              const ScreenVertex& c, Picture& picture);
};
