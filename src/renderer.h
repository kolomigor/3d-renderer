#pragma once
#include "camera.h"
#include "picture.h"
#include "world.h"

class Renderer {
public:
	void Render(const World& world, const Camera& camera, Picture& picture);

private:
	struct ScreenVertex {
		float x;
		float y;
		float depth;
	};

	ScreenVertex ProjectVertex(const glm::vec3& pos, const glm::mat4& vp,
	                           int width, int height) const;

	void RasterizeTriangle(const ScreenVertex& a, const ScreenVertex& b,
	                       const ScreenVertex& c, Picture& picture) const;

	static float Edge(const glm::vec2& a, const glm::vec2& b,
	                  const glm::vec2& p);
};
