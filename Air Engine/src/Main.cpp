#include <glad/glad.h>
#include <algorithm>
#include "graphics/Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"
#include "io\File.h"

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

	File file("G:/Onedrive/Documenten/Visual Studio 2017/Projects/Air Engine/Test fileeee.txt");
	file.createFile();
	bool exists = file.exists();
	long long size = file.file_size();
	std::vector<std::string> lines = file.readFileLines();
	const char* chars = file.readFile();

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	file.close();
	delete[] chars;

	VertexArray* vertexArray = new VertexArray(std::move(vertices));
	SimpleRenderer* renderer = new SimpleRenderer();

	while (!window->shouldClose()) {	
		glClear(GL_COLOR_BUFFER_BIT);
		
		renderer->prepareRender();
		
		renderer->render(vertexArray);
		window->Update();
	}

	vertexArray->unBind();

	delete vertexArray;
	delete renderer;
	delete window;
	
	file.close();
	return 0;
}