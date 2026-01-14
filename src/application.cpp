#include "application.h"
#include "image_io.h"

Application::Application()
    : camera_(60.0f, 800.0f / 600.0f, 0.1f, 100.0f), picture_(800, 600) {
	camera_.SetPosition({0, 0, 5});
	camera_.LookAt({0, 0, 0});
}

void Application::Run() {
	Triangle t;
	t.v0.position = glm::vec3(-1.0f, -1.0f, 0.0f);
	t.v1.position = glm::vec3(1.0f, -1.0f, 0.0f);
	t.v2.position = glm::vec3(0.0f, 1.0f, 0.0f);
	world_.AddTriangle(t);
	renderer_.Render(world_, camera_, picture_);
	SavePPM(picture_, "output.ppm");
}