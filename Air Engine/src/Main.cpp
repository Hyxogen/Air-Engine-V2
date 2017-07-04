#include <glad/glad.h>
#include <algorithm>
#include "graphics\Window.h"
#include "buffers\VertexArray.h"
#include "buffers\FrameBuffer.h"
#include "graphics\renderer\SimpleRenderer.h"
#include "io\File.h"
#include "graphics\shader\Shader.h"
#include "math\Math.h"
#include "geometry\Model.h"
#include "graphics\Texture.h"

//#define POST_PROCESS

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
	glEnable(GL_CULL_FACE);
	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//glStencilFunc(GL_EQUAL, 1, 0x00);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	
#ifdef POST_PROCESS
	const char* screenVertexSource = File::readFile("res/shaders/postprocessing/SimpleQuadVertexShader.glsl");
	const char* screenFragmentSource = File::readFile("res/shaders/postprocessing/SimpleQuadFragmentShader.glsl");
#endif
	const char* normalVertexSource = File::readFile("res/shaders/lighting/AttenuationVertexShader.glsl");
	const char* normalFragmentSource = File::readFile("res/shaders/lighting/AttenuationFragmentShader.glsl");
	const char* normalGeometrySource = File::readFile("res/shaders/SimpleGeometryShader.glsl");

	const char* skyboxVertexSource = File::readFile("res/shaders/cubemap/CubemapVertexShader.glsl");
	const char* skyboxFragmentSource = File::readFile("res/shaders/cubemap/CubemapFragmentShader.glsl");

	unsigned int width = window->getWidth(), height = window->getHeight();
	
#ifdef POST_PROCESS
	FrameBuffer* screenBuffer = new FrameBuffer();
	Texture* colorBuffer = new Texture(width, height);
	RenderBuffer* renderBuffer = new RenderBuffer(GL_DEPTH24_STENCIL8, width, height);
	colorBuffer->bind();
	screenBuffer->addTextureBuffer(colorBuffer, GL_COLOR_ATTACHMENT0);
	screenBuffer->bind();

	renderBuffer->bind();
	screenBuffer->addRenderBuffer(renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);

	if (!screenBuffer->isComplete())
		std::cout << "ERROR: Framebuffer is incomplete!" << std::endl;
	screenBuffer->unBind();
#endif;
	
	Shader* normalShader = new Shader(normalVertexSource, normalFragmentSource);
	Shader* skyboxShader = new Shader(skyboxVertexSource, skyboxFragmentSource);
#ifdef POST_PROCESS
	Shader* screenShader = new Shader(screenVertexSource, screenFragmentSource);
#endif
	
	delete[] normalVertexSource;
	delete[] normalFragmentSource;
	delete[] normalGeometrySource;
	delete[] skyboxVertexSource;
	delete[] skyboxFragmentSource;

#ifdef POST_PROCESS
	delete[] screenVertexSource;
	delete[] screenFragmentSource;

	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();
#endif

	Model* model = new Model("res/models/nanosuit/nanosuit.obj");
	//Model* cube = new Model("res/models/plane/plane.obj");
	Model* cube = new Model("res/models/cube/Cube.obj");

#ifdef POST_PROCESS
	std::vector<float> screenQuad = {
		// positions   // texCoords
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
	
	VertexArray* screen = new VertexArray(std::move(screenQuad), std::move(screenIndices), 2);

	glBindVertexArray(0);
	screen->bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
	screen->unBind();
#endif;

	std::vector < std::string> skyboxFaces = {
		"res/textures/cubemaps/skybox/right.jpg",
		"res/textures/cubemaps/skybox/left.jpg",
		"res/textures/cubemaps/skybox/top.jpg",
		"res/textures/cubemaps/skybox/bottom.jpg",
		"res/textures/cubemaps/skybox/back.jpg",
		"res/textures/cubemaps/skybox/front.jpg"
	};

	Texture* skybox = new Texture(skyboxFaces);

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
	skyboxShader->bind();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setInt("skybox", 0);

#ifdef POST_PROCESS
	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();
#endif
	while (!window->shouldClose()) {
#ifdef POST_PROCESS
		glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer->getFrameBufferID());
#endif
		glEnable(GL_DEPTH_TEST);
		
		renderer->prepareRender();

		//Models
		normalShader->bind();
		normalShader->setFloat("time", glfwGetTime());

		normalShader->setVec3("viewPos", viewPos);
		normalShader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)));

		normalShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));

		model->draw(*normalShader);
		normalShader->unBind();

		//Skybox
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		skyboxShader->bind();
		skyboxShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y));
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());		
		
		cube->draw(*skyboxShader);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		skyboxShader->unBind();
		
		//Frame buffer rendering
#ifdef POST_PROCESS
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->bind();
		glDisable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, colorBuffer->getTextureID());
		renderer->render(screen);

		screenShader->unBind();
#endif

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

	delete cube;
	delete skybox;
	delete model;
#ifdef POST_PROCESS
	delete colorBuffer;
	delete renderBuffer;
	delete screenBuffer;
	delete screenShader;
#endif
	delete normalShader;
	delete renderer;
	delete window;

	return 0;
}