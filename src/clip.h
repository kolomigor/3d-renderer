#pragma once
#include <array>
#include <glm/glm.hpp>
#include <vector>

using ClipTriangle = std::array<glm::vec4, 3>;

std::vector<ClipTriangle> ClipTriangleNear(const glm::vec4& c0, const glm::vec4& c1,
                                           const glm::vec4& c2);
