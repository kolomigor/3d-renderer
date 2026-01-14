#include "renderer.h"
#include "clip.h"
#include "primitives.h"
#include "rasterizer.h"

static bool IsBackFaceCCW(const ScreenVertex& a, const ScreenVertex& b, const ScreenVertex& c) {
	const float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return area >= 0.f;
}

ScreenVertex ProjectVertex(const glm::vec4& clip, int width, int height) {
	assert(clip.w > 0);
	assert(clip.z >= -clip.w);
	const glm::vec3 ndc = glm::vec3(clip) / clip.w;
	ScreenVertex out;
	out.x = (ndc.x * 0.5f + 0.5f) * static_cast<float>(width);
	out.y = (1.0f - (ndc.y * 0.5f + 0.5f)) * static_cast<float>(height);
	out.depth = ndc.z;
	return out;
}

static float Edge(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p) {
	return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
}

void Renderer::Render(const World& world, const Camera& camera, Picture& picture) {
	picture.Clear({0.0f, 0.0f, 0.0f});
	picture.ClearDepth();
	const glm::mat4 vp = camera.Projection() * camera.View();
	const int w = picture.Width();
	const int h = picture.Height();
	for (const Triangle& t : world.GetTriangles()) {
		glm::vec4 c0 = vp * glm::vec4(t.v0.position, 1.0f);
		glm::vec4 c1 = vp * glm::vec4(t.v1.position, 1.0f);
		glm::vec4 c2 = vp * glm::vec4(t.v2.position, 1.0f);
		auto clipped_triangles = ClipTriangleNear(c0, c1, c2);
		for (const ClipTriangle& tr : clipped_triangles) {
			ScreenVertex v0 = ProjectVertex(tr[0], w, h);
			ScreenVertex v1 = ProjectVertex(tr[1], w, h);
			ScreenVertex v2 = ProjectVertex(tr[2], w, h);
			if (IsBackFaceCCW(v0, v1, v2)) {
				continue;
			}
			Rasterizer::RasterizeTriangle(v0, v1, v2, picture);
		}
	}
}
