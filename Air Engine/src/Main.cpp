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
    switch(error) {
        CASE_STRING( GL_NO_ERROR );
        CASE_STRING( GL_INVALID_ENUM );
        CASE_STRING( GL_INVALID_VALUE );
        CASE_STRING( GL_INVALID_OPERATION );
        CASE_STRING( GL_INVALID_FRAMEBUFFER_OPERATION );
        CASE_STRING( GL_OUT_OF_MEMORY );

        #ifndef FROSTCORE_MAC_OS
        CASE_STRING( GL_STACK_OVERFLOW );
        CASE_STRING( GL_STACK_UNDERFLOW );
        #endif

        CASE_STRING( GL_FRAMEBUFFER_UNDEFINED );
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT );
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT );

        #ifdef FROST_GL
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER );
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER );
        #endif

        CASE_STRING( GL_FRAMEBUFFER_UNSUPPORTED );
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE );

        #ifdef FROST_GL
        CASE_STRING( GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS );
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

	Window* window = new Window("Engine", 800, 600);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	const char* vertexSource = File::readFile("res/shaders/SimpleVertexShader.glsl");
	const char* fragmentSource = File::readFile("res/shaders/SimpleFragmentShader.glsl");

	Shader* shader = new Shader(vertexSource, fragmentSource);
	graphics::Texture* texture = new graphics::Texture("res/textures/wall.jpg");
	/*
	std::vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f
	};

	std::vector<unsigned int> indices = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	VertexArray* vertexArray = new VertexArray(std::move(vertices), std::move(indices));
	*/

	Model* model = new Model("res/models/nanosuit/nanosuit.obj");
	SimpleRenderer* renderer = new SimpleRenderer();
	InputHandler* input = window->getInputHandler();

	shader->bind();
	shader->setMat4("projection", Matrix4f::perspective(800.0f / 600.0f, 70.0f, 0.1f, 100.0f));
	//shader->setMat4("projection", Matrix4f::orthographic(0.1f, 500.0f, 2.0f, -2.0f, -2.0f, 1.0f));
	//shader->setMat4("projection", Matrix4f::orthographic(0.1f, 100.0f, 600, 0.0f, 0.0f, 800.0f));

	//z = -1 // object visible(partially)
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	//shader->setInt("texture1", 0);
	//float f = 0.0f;
	shader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, -9.0f, -15.0f)));
	while (!window->shouldClose()) {
	//	f -= 0.01f;
		//std::cout << f << std::endl;
		renderer->prepareRender();
		

		model->draw(*shader);
		//renderer->render(vertexArray);
		input->update();
		window->Update();
	}
	shader->unBind();

	//vertexArray->unBind();

	//delete vertexArray;
	delete texture;
	delete model;
	delete shader;
	delete renderer;
	delete window;

	return 0;
}