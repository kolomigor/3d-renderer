#include "application.h"
#include "image_io.h"
#include "primitives.h"

Application::Application() : camera_(60.0f, 800.0f / 600.0f, 0.1f, 100.0f), picture_(800, 600) {
	// camera_.SetPosition({0, 0, 0});
	// camera_.LookAt({0, 0, -1});
	camera_.SetPosition({2.5f, 2.0f, 2.0f});
	camera_.LookAt({0, 0, -6});
}

void Application::Run() {
	auto addTri = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 ca, glm::vec3 cb,
	                  glm::vec3 cc) {
		Triangle t;
		t.v0.position = a;
		t.v0.color = ca;
		t.v1.position = b;
		t.v1.color = cb;
		t.v2.position = c;
		t.v2.color = cc;
		world_.AddTriangle(t);
	};

	// Центр куба
	glm::vec3 c(0, 0, -6);
	float s = 1.0f;

	// 8 вершин
	glm::vec3 v000 = c + glm::vec3(-s, -s, -s);
	glm::vec3 v001 = c + glm::vec3(-s, -s, s);
	glm::vec3 v010 = c + glm::vec3(-s, s, -s);
	glm::vec3 v011 = c + glm::vec3(-s, s, s);
	glm::vec3 v100 = c + glm::vec3(s, -s, -s);
	glm::vec3 v101 = c + glm::vec3(s, -s, s);
	glm::vec3 v110 = c + glm::vec3(s, s, -s);
	glm::vec3 v111 = c + glm::vec3(s, s, s);

	// Цвета граней
	glm::vec3 red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
	glm::vec3 yellow(1, 1, 0), cyan(0, 1, 1), magenta(1, 0, 1);

	// FRONT (+Z)  ближняя к камере
	addTri(v001, v101, v111, green, green, green);
	addTri(v001, v111, v011, green, green, green);

	// BACK (-Z)
	addTri(v000, v010, v110, red, red, red);
	addTri(v000, v110, v100, red, red, red);

	// LEFT (-X)
	addTri(v000, v001, v011, blue, blue, blue);
	addTri(v000, v011, v010, blue, blue, blue);

	// RIGHT (+X)
	addTri(v100, v110, v111, yellow, yellow, yellow);
	addTri(v100, v111, v101, yellow, yellow, yellow);

	// TOP (+Y)
	addTri(v010, v011, v111, cyan, cyan, cyan);
	addTri(v010, v111, v110, cyan, cyan, cyan);

	// BOTTOM (-Y)
	addTri(v000, v100, v101, magenta, magenta, magenta);
	addTri(v000, v101, v001, magenta, magenta, magenta);

	renderer_.Render(world_, camera_, picture_);
	SavePPM(picture_, "output.ppm");
}
