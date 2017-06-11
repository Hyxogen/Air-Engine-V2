#include <glad/glad.h>
#include <algorithm>
#include "graphics/Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;

	Window* window = new Window("Engine", 800, 600);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	VertexArray* vertexArray = new VertexArray(std::move(vertices));
	SimpleRenderer* renderer = new SimpleRenderer();
	
	while (!window->shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		renderer->prepareRender();

		renderer->render(*vertexArray);
	}

	vertexArray->UnBind();

	delete vertexArray;
	delete renderer;
	delete window;
	

	return 0;
}