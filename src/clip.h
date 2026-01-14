#pragma once
#include <array>
#include <glm/glm.hpp>
#include <vector>

struct ClipVertex {
	glm::vec4 position;
};

using ClipTriangle = std::array<ClipVertex, 3>;

std::vector<ClipTriangle> ClipTriangleNear(const ClipVertex& c0, const ClipVertex& c1,
                                           const ClipVertex& c2);
