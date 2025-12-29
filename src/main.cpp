#include "mesh_data.h"
#include <iostream>

MeshData CreateTriangle() {
    MeshData mesh;
    mesh.vertices = {
        {{0.0f, 0.0f, 0.0f}}, {{1.0f, 0.0f, 0.0f}}, {{0.0f, 1.0f, 0.0f}}};
    mesh.indices = {0, 1, 2};
    return mesh;
}

int main() {
    std::cout << "3D Renderer begins here" << std::endl;
    MeshData triangle = CreateTriangle();
    std::cout << "Triangle vertices: " << triangle.vertices.size() << std::endl;
    return 0;
}