#include "application.h"
#include "image_io.h"

Application::Application() : camera_(60.0f, 800.0f / 600.0f, 0.1f, 100.0f), picture_(800, 600) {
	camera_.SetPosition({0, 0, 2});
	camera_.LookAt({0, 0, 0});
}

void Application::Run() {
	Triangle t1;
	t1.v0.position = glm::vec3(-1.2f, -0.5f, 0.0f);
	t1.v1.position = glm::vec3(-0.2f, -0.5f, 0.0f);
	t1.v2.position = glm::vec3(-0.7f, 0.5f, 0.0f);
	world_.AddTriangle(t1);

	Triangle t2;
	t2.v0.position = glm::vec3(0.2f, -0.5f, 0.0f);
	t2.v1.position = glm::vec3(1.2f, -0.5f, 0.0f);
	t2.v2.position = glm::vec3(0.7f, 0.5f, 0.0f);
	world_.AddTriangle(t2);

	renderer_.Render(world_, camera_, picture_);
	SavePPM(picture_, "output.ppm");
}
