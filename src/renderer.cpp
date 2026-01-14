#include "renderer.h"

void Renderer::Render(const World& world, const Camera& camera,
                      Picture& picture) {
	picture.Clear({0.0f, 0.0f, 0.0f});
	picture.ClearDepth();
	const glm::mat4 vp = camera.Projection() * camera.View();
	const int w = picture.Width();
	const int h = picture.Height();
	for (const Triangle& t : world.GetTriangles()) {
		ScreenVertex v0 = ProjectVertex(t.v0.position, vp, w, h);
		ScreenVertex v1 = ProjectVertex(t.v1.position, vp, w, h);
		ScreenVertex v2 = ProjectVertex(t.v2.position, vp, w, h);
		RasterizeTriangle(v0, v1, v2, picture);
	}
}

Renderer::ScreenVertex Renderer::ProjectVertex(const glm::vec3& pos,
                                               const glm::mat4& vp, int width,
                                               int height) const {
	const glm::vec4 clip = vp * glm::vec4(pos, 1.0f);
	const glm::vec3 ndc = glm::vec3(clip) / clip.w;
	ScreenVertex out;
	out.x = (ndc.x * 0.5f + 0.5f) * static_cast<float>(width);
	out.y = (1.0f - (ndc.y * 0.5f + 0.5f)) * static_cast<float>(height);
	out.depth = ndc.z;
	return out;
}

void Renderer::RasterizeTriangle(const ScreenVertex& a, const ScreenVertex& b,
                                 const ScreenVertex& c,
                                 Picture& picture) const {
	const int minX = static_cast<int>(std::floor(std::min({a.x, b.x, c.x})));
	const int maxX = static_cast<int>(std::ceil(std::max({a.x, b.x, c.x})));
	const int minY = static_cast<int>(std::floor(std::min({a.y, b.y, c.y})));
	const int maxY = static_cast<int>(std::ceil(std::max({a.y, b.y, c.y})));
	const glm::vec2 p0{a.x, a.y};
	const glm::vec2 p1{b.x, b.y};
	const glm::vec2 p2{c.x, c.y};
	const float area = Edge(p0, p1, p2);
	if (area == 0.0f) {
		return;
	}
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			const glm::vec2 p{static_cast<float>(x) + 0.5f,
			                  static_cast<float>(y) + 0.5f};
			const float w0 = Edge(p1, p2, p);
			const float w1 = Edge(p2, p0, p);
			const float w2 = Edge(p0, p1, p);
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
				const float alpha = w0 / area;
				const float beta = w1 / area;
				const float gamma = w2 / area;
				const float depth =
				    alpha * a.depth + beta * b.depth + gamma * c.depth;
				picture.SetPixel(x, y, glm::vec3(1.0f, 1.0f, 1.0f), depth);
			}
		}
	}
}

float Renderer::Edge(const glm::vec2& a, const glm::vec2& b,
                     const glm::vec2& p) {
	return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
}