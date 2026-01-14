#include "clip.h"

static bool InsideNear(const glm::vec4& v) {
	return v.z >= -v.w;
}

static glm::vec4 IntersectNear(const glm::vec4& a, const glm::vec4& b) {
	float da = a.z + a.w;
	float db = b.z + b.w;
	float t = da / (da - db);
	return a + t * (b - a);
}

std::vector<ClipTriangle> ClipTriangleNear(const glm::vec4& c0, const glm::vec4& c1,
                                           const glm::vec4& c2) {
	const glm::vec4 v[3] = {c0, c1, c2};
	const bool inside[3] = {InsideNear(c0), InsideNear(c1), InsideNear(c2)};
	int insideCount = inside[0] + inside[1] + inside[2];
	std::vector<ClipTriangle> out;
	if (insideCount == 0) {
		return out;
	}
	if (insideCount == 3) {
		out.push_back({c0, c1, c2});
		return out;
	}
	if (insideCount == 1) {
		int i = inside[0] ? 0 : (inside[1] ? 1 : 2);
		int o1 = (i + 1) % 3;
		int o2 = (i + 2) % 3;
		glm::vec4 p1 = IntersectNear(v[i], v[o1]);
		glm::vec4 p2 = IntersectNear(v[i], v[o2]);
		out.push_back({v[i], p1, p2});
		return out;
	}
	if (insideCount == 2) {
		int o = inside[0] ? (inside[1] ? 2 : 1) : 0;
		int i1 = (o + 1) % 3;
		int i2 = (o + 2) % 3;
		glm::vec4 p1 = IntersectNear(v[i1], v[o]);
		glm::vec4 p2 = IntersectNear(v[i2], v[o]);
		out.push_back({v[i1], v[i2], p1});
		out.push_back({v[i2], p2, p1});
		return out;
	}
	return out;
}