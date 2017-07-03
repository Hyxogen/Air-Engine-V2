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

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace buffer;
	using namespace renderer;
	using namespace io;
	using namespace math;
	using namespace geometry;

	Window* window = new Window("Engine", 1280, 720);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glStencilFunc(GL_EQUAL, 1, 0x00);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	const char* screenVertexSource = File::readFile("res/shaders/postprocessing/SimpleQuadVertexShader.glsl");
	const char* screenFragmentSource = File::readFile("res/shaders/postprocessing/SimpleQuadFragmentShader.glsl");
	
	const char* normalVertexSource = File::readFile("res/shaders/lighting/AttenuationVertexShader.glsl");
	const char* normalFragmentSource = File::readFile("res/shaders/lighting/AttenuationFragmentShader.glsl");

	const char* skyboxVertexSource = File::readFile("res/shaders/cubemap/CubemapVertexShader.glsl");
	const char* skyboxFragmentSource = File::readFile("res/shaders/cubemap/CubemapFragmentShader.glsl");

	GLuint framebuffer, texColorBuffer, renderBuffer, vao, vbo;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window->getWidth(), window->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window->getWidth(), window->getHeight());
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR: Framebuffer is incomplete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Shader* normalShader = new Shader(normalVertexSource, normalFragmentSource);
	Shader* screenShader = new Shader(screenVertexSource, screenFragmentSource);
	Shader* skyboxShader = new Shader(skyboxVertexSource, skyboxFragmentSource);
	
	delete[] normalVertexSource;
	delete[] normalFragmentSource;
	delete[] screenVertexSource;
	delete[] screenFragmentSource;
	delete[] skyboxVertexSource;
	delete[] skyboxFragmentSource;

	std::vector < std::string> skyboxFaces = {
		"res/textures/cubemaps/skybox/right.jpg",
		"res/textures/cubemaps/skybox/left.jpg",
		"res/textures/cubemaps/skybox/top.jpg",
		"res/textures/cubemaps/skybox/bottom.jpg",
		"res/textures/cubemaps/skybox/back.jpg",
		"res/textures/cubemaps/skybox/front.jpg"
	};

	//Texture* skybox = new Texture(skyboxFaces);

	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();

	Model* model = new Model("res/models/nanosuit/nanosuit.obj");
	//Model* cube = new Model("res/models/plane/plane.obj");
	//Model* cube = new Model("res/models/nanosuit/nanosuit.obj");

	std::vector<float> screenQuad = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	
	std::vector<unsigned int> screenIndices = {
		0, 1, 2, 3, 4, 5
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBufferData(GL_ARRAY_BUFFER, screenQuad.size() * sizeof(float), (void*)&screenQuad[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*) (2 * sizeof(float)));

	glBindVertexArray(0);

	SimpleRenderer* renderer = new SimpleRenderer();
	InputHandler* input = window->getInputHandler();
	
	Matrix4f projection = Matrix4f::perspective(window->getAspectRatio(), 70.0f, 0.1f, 5000.0f);

	normalShader->bind();
	normalShader->setMat4("projection", projection);

	normalShader->setVec3("material.specular", Vector3f(1.0f, 1.0f, 1.0f));
	normalShader->setFloat("material.shininess", 32.0f);
	
	normalShader->setVec3("light.position", Vector3f(1.2f, 1.0f, 1.0f));
	normalShader->setVec3("light.ambient", Vector3f(1.0f, 1.0f, 1.0f));
	normalShader->setVec3("light.diffuse", Vector3f(1.0f, 1.0f, 1.0f));
	normalShader->setVec3("light.specular", Vector3f(1.0f, 1.0f, 1.0f));
	normalShader->setFloat("light.linear", 0.0014f);
	normalShader->setFloat("light.quadratic", 0.000007f);

	Vector3f viewPos, lightPos(1.2f, 1.0f, 1.0f);

	float speed = 10.0f;
	float y = 0.0f;

	skyboxShader->unBind();
	while (!window->shouldClose()) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		//glEnable(GL_DEPTH_TEST);
		
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		normalShader->bind();

		normalShader->setVec3("viewPos", viewPos);
		normalShader->setMat4("model", Matrix4f::transformation(Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)),
			Matrix4f::rotation(Vector3f(0.0f, 1.0f), y), Matrix4f::identity()));
		normalShader->setMat4("view", Matrix4f::translation(viewPos));

		model->draw(*normalShader);
		normalShader->unBind();
		//cube->draw(*normalShader);
		/*
		//SKYBOX
		glDepthFunc(GL_LEQUAL);

		skyboxShader->bind();
		normalShader->setMat4("view", Matrix4f::translation(viewPos));
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());

		glDepthFunc(GL_LESS);
		skyboxShader->unBind();
		*/
		//Frame buffer rendering
		/*
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->bind();
		glDisable(GL_DEPTH_TEST);
		
		glBindVertexArray(vao);

		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		screenShader->unBind();
		*/
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
	normalShader->unBind();
	
	glDeleteTextures(1, &texColorBuffer);
	glDeleteRenderbuffers(1, &renderBuffer);
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
	//delete cube;
	//delete skybox;
	//delete windowPlane;
	delete model;
	delete normalShader;
	delete screenShader;
	delete renderer;
	delete window;

	return 0;
}