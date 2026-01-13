#include <vector>

struct Vector3D {
    float x;
    float y;
    float z;
};

struct Vertex {
    Vector3D position;
};

struct Triangle {
    Vertex v0;
    Vertex v1;
    Vertex v2;
};