#include "renderer.h"
#include "clip.h"
#include "primitives.h"

bool Renderer::IsBackFaceCCW(const SV& a, const SV& b, const SV& c) {
	const float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	// Screen space has inverted Y axis,
	// so CCW test uses area >= 0
	return area >= 0.f;
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
			SV v0 = ProjectVertex(tr[0], w, h);
			SV v1 = ProjectVertex(tr[1], w, h);
			SV v2 = ProjectVertex(tr[2], w, h);
			if (Renderer::IsBackFaceCCW(v0, v1, v2)) {
				continue;
			}
			RasterizeTriangle(v0, v1, v2, picture);
		}
	}
}

Renderer::SV Renderer::ProjectVertex(const glm::vec4& clip, int width, int height) const {
	assert(clip.w > 0);
	assert(clip.z >= -clip.w);
	const glm::vec3 ndc = glm::vec3(clip) / clip.w;
	SV out;
	out.x = (ndc.x * 0.5f + 0.5f) * static_cast<float>(width);
	out.y = (1.0f - (ndc.y * 0.5f + 0.5f)) * static_cast<float>(height);
	out.depth = ndc.z;
	return out;
}

void Renderer::RasterizeTriangle(const SV& a, const SV& b, const SV& c, Picture& picture) const {
	const int min_x = static_cast<int>(std::floor(std::min({a.x, b.x, c.x})));
	const int max_x = static_cast<int>(std::ceil(std::max({a.x, b.x, c.x})));
	const int min_y = static_cast<int>(std::floor(std::min({a.y, b.y, c.y})));
	const int max_y = static_cast<int>(std::ceil(std::max({a.y, b.y, c.y})));
	const glm::vec2 p0{a.x, a.y};
	const glm::vec2 p1{b.x, b.y};
	const glm::vec2 p2{c.x, c.y};
	const float area = Edge(p0, p1, p2);
	if (area == 0.0f) {
		return;
	}
	for (int y = min_y; y <= max_y; ++y) {
		for (int x = min_x; x <= max_x; ++x) {
			const glm::vec2 p{static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f};
			const float w0 = Edge(p1, p2, p);
			const float w1 = Edge(p2, p0, p);
			const float w2 = Edge(p0, p1, p);
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
				const float alpha = w0 / area;
				const float beta = w1 / area;
				const float gamma = w2 / area;
				const float depth = alpha * a.depth + beta * b.depth + gamma * c.depth;
				picture.SetPixel(x, y, glm::vec3(1.0f, 1.0f, 1.0f), depth);
			}
		}
	}
}

float Renderer::Edge(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p) {
	return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
}