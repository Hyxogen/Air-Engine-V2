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

	unsigned int width = window->getWidth(), height = window->getHeight();
	
	FrameBuffer* screenBuffer = new FrameBuffer();
	Texture* colorBuffer = new Texture(width, height);
	RenderBuffer* renderBuffer = new RenderBuffer(GL_DEPTH24_STENCIL8, width, height);
	colorBuffer->bind();
	screenBuffer->addTextureBuffer(colorBuffer, GL_COLOR_ATTACHMENT0);
	screenBuffer->bind();

	renderBuffer->bind();
	screenBuffer->addRenderBuffer(renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);

	GLuint screenVAO, screenVBO;
	if (!screenBuffer->isComplete())
		std::cout << "ERROR: Framebuffer is incomplete!" << std::endl;
	screenBuffer->unBind();
	
	
	Shader* normalShader = new Shader(normalVertexSource, normalFragmentSource);
	Shader* screenShader = new Shader(screenVertexSource, screenFragmentSource);
	Shader* skyboxShader = new Shader(skyboxVertexSource, skyboxFragmentSource);
	
	delete[] normalVertexSource;
	delete[] normalFragmentSource;
	delete[] screenVertexSource;
	delete[] screenFragmentSource;
	delete[] skyboxVertexSource;
	delete[] skyboxFragmentSource;

	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();

	Model* model = new Model("res/models/sponza/sponza.obj");
	//Model* cube = new Model("res/models/plane/plane.obj");
	Model* cube = new Model("res/models/cube/Cube.obj");

	std::vector<float> screenQuad = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
									  // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	
	std::vector<unsigned int> screenIndices = {
		0, 1, 2, 0, 3, 4
	};

	std::vector<float> skyboxVertices = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	
	//VertexArray* screen = new VertexArray(std::move(screenQuad), std::move(screenIndices));
	glGenVertexArrays(1, &screenVAO);
	glGenBuffers(1, &screenVBO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);

	glBufferData(GL_ARRAY_BUFFER, screenQuad.size() * sizeof(float), (void*)&screenQuad[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	/*
	glBindVertexArray(0);
	screen->bind();
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
	screen->unBind();
	*/

	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices) * skyboxVertices.size(), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
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

	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();

	while (!window->shouldClose()) {
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer->getFrameBufferID());
		glEnable(GL_DEPTH_TEST);
		
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer->prepareRender();

		normalShader->bind();

		normalShader->setVec3("viewPos", viewPos);
		normalShader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)));

		normalShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));

		model->draw(*normalShader);
		normalShader->unBind();
		/*
		glDepthFunc(GL_LEQUAL);
		skyboxShader->bind();
		skyboxShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		*/

		
		//SKYBOX
		
		glDepthFunc(GL_LEQUAL);

		skyboxShader->bind();
		skyboxShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y));
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());		

		cube->draw(*skyboxShader);
		glDepthFunc(GL_LESS);
		skyboxShader->unBind();
		
		//Frame buffer rendering
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->bind();
		glDisable(GL_DEPTH_TEST);
		
		glBindVertexArray(screenVAO);

		glBindTexture(GL_TEXTURE_2D, colorBuffer->getTextureID());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//renderer->render(screen);
		glBindVertexArray(0);
		screenShader->unBind();

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
	
	glDeleteBuffers(1, &screenVBO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteVertexArrays(1, &skyboxVAO);

	delete cube;
	delete skybox;
	//delete windowPlane;
	delete model;
	delete colorBuffer;
	delete renderBuffer;

	delete screenBuffer;
	delete normalShader;
	delete screenShader;
	delete renderer;
	delete window;

	return 0;
}