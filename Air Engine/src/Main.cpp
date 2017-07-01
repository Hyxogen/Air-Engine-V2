#include <glad/glad.h>
#include <algorithm>
#include "graphics\Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"
#include "io\File.h"
#include "graphics\shader\Shader.h"
#include "math\Math.h"

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;
	using namespace io;
	using namespace math;

#ifdef MAT_MUL_DEBUG
	Matrix4f matrix;
	Matrix4f other;

	for (int i = 0; i < 16; i++) {
		matrix.mElements[i] = i;
		other.mElements[i] = 16 + i;
	}

	matrix.multiply(other);

	system("pause");
#endif

	Window* window = new Window("Engine", 800, 600);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	const char* vertexSource = File::readFile("res/shaders/SimpleVertexShader.glsl");
	const char* fragmentSource = File::readFile("res/shaders/SimpleFragmentShader.glsl");

	Shader* shader = new Shader(vertexSource, fragmentSource);

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	VertexArray* vertexArray = new VertexArray(std::move(vertices));
	SimpleRenderer* renderer = new SimpleRenderer();

	shader->bind();
	shader->setMat4("projection", Matrix4f::perspective(800.0f / 600.0f, 70.0f, 0.1f, 1000.0f));
	//shader->setMat4("projection", Matrix4f::orthographic(0.1f, 500.0f, 2.0f, -2.0f, -2.0f, 1.0f));
	//shader->setMat4("projection", Matrix4f::orthographic(0.1f, 100.0f, 600, 0.0f, 0.0f, 800.0f));
	shader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, 1.0f)));
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