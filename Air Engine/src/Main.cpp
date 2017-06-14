#include <glad/glad.h>
#include <algorithm>
#include "graphics/Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"
#include "io\File.h"
#include "graphics\shader\Shader.h"

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;
	using namespace io;

	Window* window = new Window("Engine", 800, 600);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	const char* vertexSource = File::readFile("res/shaders/SimpleVertexShader.vert");
	const char* fragmentSource = File::readFile("res/shaders/SimpleFragmentShader.frag");

	Shader* shader = new Shader(vertexSource, fragmentSource);
	
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	VertexArray* vertexArray = new VertexArray(std::move(vertices));
	SimpleRenderer* renderer = new SimpleRenderer();

	shader->bind();
	while (!window->shouldClose()) {	
		renderer->prepareRender();
		
		renderer->render(vertexArray);
		window->Update();
	}
	shader->unBind();

	vertexArray->unBind();

	delete vertexArray;
	delete shader;
	delete renderer;
	delete window;
	
	return 0;
}