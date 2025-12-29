#include <cstdint>
#include <vector>

using u32 = uint32_t;

struct Vector3D {
    float x;
    float y;
    float z;
};

struct Vertex {
    Vector3D position;
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
};