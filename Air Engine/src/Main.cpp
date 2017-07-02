#include <glad/glad.h>
#include <algorithm>
#include "graphics\Window.h"
#include "buffers\VertexArray.h"
#include "graphics\renderer\SimpleRenderer.h"
#include "io\File.h"
#include "graphics\shader\Shader.h"
#include "math\Math.h"
#include "geometry\Model.h"
#include "graphics\Texture.h"

#define CASE_STRING( CASE ) case CASE: return #CASE;

const char* ErrorString(GLenum error) {
	switch (error) {
		CASE_STRING(GL_NO_ERROR);
		CASE_STRING(GL_INVALID_ENUM);
		CASE_STRING(GL_INVALID_VALUE);
		CASE_STRING(GL_INVALID_OPERATION);
		CASE_STRING(GL_INVALID_FRAMEBUFFER_OPERATION);
		CASE_STRING(GL_OUT_OF_MEMORY);

#ifndef FROSTCORE_MAC_OS
		CASE_STRING(GL_STACK_OVERFLOW);
		CASE_STRING(GL_STACK_UNDERFLOW);
#endif

		CASE_STRING(GL_FRAMEBUFFER_UNDEFINED);
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);

#ifdef FROST_GL
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
#endif

		CASE_STRING(GL_FRAMEBUFFER_UNSUPPORTED);
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);

#ifdef FROST_GL
		CASE_STRING(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS);
#endif
	}
	return "";
}
#undef CASE_STRING

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;
	using namespace io;
	using namespace math;
	using namespace geometry;

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

	Window* window = new Window("Engine", 1280, 720);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	const char* phongVertexSource = File::readFile("res/shaders/lighting/AttenuationVertexShader.glsl");
	const char* phongFragmentSource = File::readFile("res/shaders/lighting/AttenuationFragmentShader.glsl");

	Shader* shader = new Shader(phongVertexSource, phongFragmentSource);
	
	Model* model = new Model("res/models/sponza/sponza.obj");

	SimpleRenderer* renderer = new SimpleRenderer();
	InputHandler* input = window->getInputHandler();

	shader->bind();
	shader->setMat4("projection", Matrix4f::perspective(1280.0f / 720.0f, 70.0f, 0.1f, 5000.0f));

	shader->setVec3("material.specular", Vector3f(1.0f, 1.0f, 1.0f));
	shader->setFloat("material.shininess", 32.0f);
	
	shader->setVec3("light.position", Vector3f(1.2f, 1.0f, 1.0f));
	shader->setVec3("light.ambient", Vector3f(1.0f, 1.0f, 1.0f));
	shader->setVec3("light.diffuse", Vector3f(1.0f, 1.0f, 1.0f));
	shader->setVec3("light.specular", Vector3f(1.0f, 1.0f, 1.0f));
	shader->setFloat("light.linear", 0.0014f);
	shader->setFloat("light.quadratic", 0.000007f);

	Vector3f viewPos, lightPos(1.2f, 1.0f, 1.0f);
	//shader->setVec3("lightPos", lightPos);
	float speed = 5.0f;
	float y = 0.0f;
	while (!window->shouldClose()) {
		//	f -= 0.01f;
			//std::cout << f << std::endl;
		renderer->prepareRender();

		//shader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, -9.0f, -15.0f)));
		shader->setVec3("viewPos", viewPos);
		shader->setMat4("model", Matrix4f::transformation(Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)),
			Matrix4f::rotation(Vector3f(0.0f, 1.0f), y), Matrix4f::identity()));
		shader->setMat4("view", Matrix4f::translation(viewPos));
		model->draw(*shader);
		//renderer->render(vertexArray);

		if (input->keyDown(GLFW_KEY_W))
			viewPos.z += speed;
		if (input->keyDown(GLFW_KEY_S))
			viewPos.z -= speed;
		if (input->keyDown(GLFW_KEY_A))
			viewPos.x += speed;
		if (input->keyDown(GLFW_KEY_D))
			viewPos.x -= speed;
		if (input->keyDown(GLFW_KEY_E))
			viewPos.y += speed;
		if (input->keyDown(GLFW_KEY_Q))
			viewPos.y -= speed;

		if (input->keyDown(GLFW_KEY_RIGHT))
			y += 2.0f;
		if (input->keyDown(GLFW_KEY_LEFT))
			y -= 2.0f;

		if (input->keyDown(GLFW_KEY_ESCAPE))
			break;

		input->update();
		window->Update();
	}
	shader->unBind();
	
	delete model;
	delete shader;
	delete renderer;
	delete window;

	return 0;
}