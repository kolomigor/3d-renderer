#pragma once
#include "camera.h"
#include "picture.h"
#include "world.h"

class Renderer {
public:
	void Render(const World& world, const Camera& camera, Picture& picture);

private:
	// Screen Vertex
	struct SV {
		float x;
		float y;
		float depth;
	};
	static bool IsBackFaceCCW(const SV& a, const SV& b, const SV& c);
	const glm::vec4& FromWorldSpaceToClipSpace();
	SV ProjectVertex(const glm::vec4& clip, int w, int h) const;
	void RasterizeTriangle(const SV& a, const SV& b, const SV& c, Picture& picture) const;
	static float Edge(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p);
};
