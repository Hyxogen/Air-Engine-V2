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
#include "buffers\Texture.h"
#include "buffers\BufferObject.h"

#define POST_PROCESS
//#define CUSTOM_MULTISAMPLE;
//#define INSTANCED
//TODO Replace all data types with custom data types
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
	glEnable(GL_MULTISAMPLE);
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
	const char* defaultVertexSource = File::readFile("res/shaders/lighting/AttenuationVertexShader.glsl");
	const char* defaultFragmentSource = File::readFile("res/shaders/lighting/AttenuationFragmentShader.glsl");
	const char* defaultGeometrySource = File::readFile("res/shaders/SimpleGeometryShader.glsl");
	
#ifdef INSTANCED
	const char* instancedVertexSource = File::readFile("res/shaders/instanced/IAttenuationVertexShader.glsl");
	const char* instancedFragmentSource = File::readFile("res/shaders/instanced/IAttenuationFragmentShader.glsl");
#endif

	const char* skyboxVertexSource = File::readFile("res/shaders/cubemap/CubemapVertexShader.glsl");
	const char* skyboxFragmentSource = File::readFile("res/shaders/cubemap/CubemapFragmentShader.glsl");

	const char* normalVertexSource = File::readFile("res/shaders/geometry/NormalVertexShader.glsl");
	const char* normalFragmentSource = File::readFile("res/shaders/geometry/NormalFragmentShader.glsl");
	const char* normalGeometrySource = File::readFile("res/shaders/geometry/NormalGeometryShader.glsl");


	unsigned int width = window->getWidth(), height = window->getHeight();

#ifdef POST_PROCESS
	FrameBuffer* screenBuffer = new FrameBuffer();
	Texture* colorBuffer = new Texture(width, height);
	RenderBuffer* renderBuffer = new RenderBuffer(width, height, GL_DEPTH24_STENCIL8);
	colorBuffer->bind();
	screenBuffer->addTextureBuffer(colorBuffer, GL_COLOR_ATTACHMENT0);
	screenBuffer->bind();

	renderBuffer->bind();
	screenBuffer->addRenderBuffer(renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);

	if (!screenBuffer->isComplete())
		std::cout << "ERROR: Screenbuffer is incomplete!" << std::endl;
	screenBuffer->unBind();
#endif;

#ifdef CUSTOM_MULTISAMPLE
	FrameBuffer* sampleFrameBuffer = new FrameBuffer();

	Texture* sampleTexture = new Texture(width, height, (short) 4);
	RenderBuffer* sampleRenderBuffer = new RenderBuffer(width, height, 4, GL_DEPTH24_STENCIL8);

	sampleFrameBuffer->addTextureBuffer(sampleTexture, GL_COLOR_ATTACHMENT0);
	sampleFrameBuffer->addRenderBuffer(sampleRenderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);

	if (!sampleFrameBuffer->isComplete())
		std::cout << "ERROR: Sample Framebuffer is incomplete!" << std::endl;
	sampleFrameBuffer->unBind();
#endif

	Shader* defaultShader = new Shader(defaultVertexSource, defaultFragmentSource);
	Shader* skyboxShader = new Shader(skyboxVertexSource, skyboxFragmentSource);
	Shader* normalShader = new Shader(normalVertexSource, normalFragmentSource, normalGeometrySource);
#ifdef INSTANCED
	Shader* instancedShader = new Shader(instancedVertexSource, instancedFragmentSource);
#endif
#ifdef POST_PROCESS
	Shader* screenShader = new Shader(screenVertexSource, screenFragmentSource);
#endif

	delete[] defaultVertexSource;
	delete[] defaultFragmentSource;
	delete[] defaultGeometrySource;

#ifdef INSTANCED
	delete[] instancedVertexSource;
	delete[] instancedFragmentSource;
#endif

	delete[] skyboxVertexSource;
	delete[] skyboxFragmentSource;

	delete[] normalVertexSource;
	delete[] normalFragmentSource;
	delete[] normalGeometrySource;

#ifdef POST_PROCESS
	delete[] screenVertexSource;
	delete[] screenFragmentSource;

	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();
#endif

	Model* model = new Model("res/models/sponza/sponza.obj");
#ifdef INSTANCED
	Model* rock = new Model("res/models/rock/rock.obj");
#endif
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

	VertexArray* screen = new VertexArray(screenQuad, screenIndices);

	screen->bind();
	screen->assignAttribPointer(0, 2, GL_FLOAT, 4 * sizeof(float));
	screen->assignAttribPointer(1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	screen->unBind();

#endif;
#ifdef INSTANCED
	unsigned int amount = 100000;
	float radius = 50.0f;
	float offset = 2.5f;

	Matrix4f* modelMatrices = new Matrix4f[amount];
	srand((unsigned int) Window::getTime());

	for (unsigned int i = 0; i < amount; i++) {
		Matrix4f model;

		float angle = (float)i / (float)amount * 360.0f;

		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;

		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f;

		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;

		Matrix4f translation = Matrix4f::translation(Vector3f(x, y, z));

		float scale = (rand() % 20) / 100.0f + 0.05f;
		Matrix4f scaleMat = Matrix4f::scale(Vector3f(scale, scale, scale));

		float rotAngle = (rand() % 360);
		Matrix4f rotation = Matrix4f::rotation(Vector3f(0.4f, 0.6f, 0.6f), rotAngle);

		model = Matrix4f::transformation(translation, rotation, scaleMat);
		modelMatrices[i] = model;
	}

	BufferObject* bufferObject = new BufferObject(GL_ARRAY_BUFFER, &modelMatrices[0], amount * sizeof(Matrix4f));
	bufferObject->bind();
	for (unsigned int i = 0; i < rock->mMeshes.size(); i++) {
		GLuint VAO = rock->mMeshes[i]->getVaoID();
		VertexArray* vertexArray = rock->mMeshes[i]->getVertexArray();

		vertexArray->bind();

		GLsizei vec4Size = sizeof(Vector4f);
		vertexArray->assignAttribPointer(3, 4, GL_FLOAT, sizeof(Matrix4f), (void*) 0);
		vertexArray->assignAttribPointer(4, 4, GL_FLOAT, sizeof(Matrix4f), (void*) vec4Size);
		vertexArray->assignAttribPointer(5, 4, GL_FLOAT, sizeof(Matrix4f), (void*) (2 * vec4Size));
		vertexArray->assignAttribPointer(6, 4, GL_FLOAT, sizeof(Matrix4f), (void*) (3 * vec4Size));

		vertexArray->setAttribDivisor(3, 1);
		vertexArray->setAttribDivisor(4, 1);
		vertexArray->setAttribDivisor(5, 1);
		vertexArray->setAttribDivisor(6, 1);

		vertexArray->unBind();
	}
#endif

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

	defaultShader->bind();
	defaultShader->setMat4("projection", projection);

	defaultShader->setVec3("material.specular", Vector3f(1.0f, 1.0f, 1.0f));
	defaultShader->setFloat("material.shininess", 32.0f * 4.0f);

	defaultShader->setVec3("light.position", Vector3f(1.2f, 1.0f, 1.0f));
	defaultShader->setVec3("light.ambient", Vector3f(1.0f, 1.0f, 1.0f));
	defaultShader->setVec3("light.diffuse", Vector3f(1.0f, 1.0f, 1.0f));
	defaultShader->setVec3("light.specular", Vector3f(1.0f, 1.0f, 1.0f));
	defaultShader->setFloat("light.linear", 0.0014f);
	defaultShader->setFloat("light.quadratic", 0.000007f);

	Vector3f viewPos, lightPos(1.2f, 1.0f, 1.0f);

	float speed = 50.0f;
	float y = 0.0f;
	skyboxShader->bind();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setInt("skybox", 0);

	normalShader->bind();
	normalShader->setMat4("projection", projection);
#ifdef INSTANCED
	instancedShader->bind();
	instancedShader->setMat4("projection", projection);
	instancedShader->unBind();
#endif

#ifdef POST_PROCESS
	screenShader->bind();
	screenShader->setInt("screenTexture", 0);
	screenShader->unBind();
#endif

	int phong = 0;
	bool gammaCorrect = false;
	float lastTime = (float)Window::getTime();
	float deltaSum = 0;
	unsigned int numFrames = 0, numUpdates = 0;

	while (!window->shouldClose()) {
#ifndef CUSTOM_MULTISAMPLE
#ifdef POST_PROCESS
		screenBuffer->bind();
		//glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer->getBufferID());
#endif
#else // !CUSTOM_CUSTOM_MULTISAMPLE
		sampleFrameBuffer->bind();
#endif
		glDisable(GL_FRAMEBUFFER_SRGB);
		

		float currentTime = (float)Window::getTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		deltaSum += deltaTime;
		//std::cout << "Delta time: " << deltaTime << " Delta sum: " << deltaSum << std::endl;
		if (deltaSum >= 1.0) {
			window->setTitle(std::to_string((deltaTime * 1000.0)) + " ms || " + std::to_string(numFrames) + " fps" + " | " +
				std::to_string(numUpdates) + " ups");
			numUpdates = 0;
			numFrames = 0;
			deltaSum -= 1.0;
		}

		glEnable(GL_DEPTH_TEST);

		renderer->prepareRender();

		//Models
		defaultShader->bind();

		defaultShader->setVec3("viewPos", viewPos);
		defaultShader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, 0.0f)));

		defaultShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));

		model->draw(*defaultShader);
		defaultShader->unBind();
#ifdef INSTANCED
		instancedShader->bind();
		instancedShader->setVec3("viewPos", viewPos);
		instancedShader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)));
		instancedShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));

		rock->drawInstanced(*instancedShader, amount);
		

		instancedShader->unBind();
#endif

		/*
		normalShader->bind();

		normalShader->setMat4("model", Matrix4f::translation(Vector3f(0.0f, 0.0f, -15.0f)));
		normalShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y).multiply(Matrix4f::translation(viewPos)));

		model->draw(*normalShader);
		normalShader->unBind();
		*/
		//Skybox
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);

		skyboxShader->bind();
		skyboxShader->setMat4("view", Matrix4f::rotation(Vector3f(0.0f, 1.0f), -y));
		//glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());
		skybox->bind();

		cube->draw(*skyboxShader);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		skyboxShader->unBind();

#ifdef CUSTOM_MULTISAMPLE
		sampleFrameBuffer->bindTarget(GL_READ_FRAMEBUFFER);
	    screenBuffer->bindTarget(GL_DRAW_FRAMEBUFFER);
		sampleFrameBuffer->blitBuffer(Vector4f(0.0f, 0.0f, width, height), Vector4f(0.0f, 0.0f, width, height), GL_COLOR_BUFFER_BIT);
#endif // CUSTOM_MULTISAMPLE

		if (gammaCorrect)
			glEnable(GL_FRAMEBUFFER_SRGB);

		//Frame buffer rendering
#ifdef POST_PROCESS
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->bind();
		glDisable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, colorBuffer->getBufferID());
		renderer->render(screen);

		screenShader->unBind();
#endif

		if (input->keyDown(GLFW_KEY_W))
			viewPos.z += speed * deltaTime;
		if (input->keyDown(GLFW_KEY_S))
			viewPos.z -= speed * deltaTime;
		if (input->keyDown(GLFW_KEY_A))
			viewPos.x += speed * deltaTime;
		if (input->keyDown(GLFW_KEY_D))
			viewPos.x -= speed * deltaTime;
		if (input->keyDown(GLFW_KEY_E))
			viewPos.y += speed * deltaTime;
		if (input->keyDown(GLFW_KEY_Q))
			viewPos.y -= speed * deltaTime;

		if (input->keyDown(GLFW_KEY_UP))
			speed++;
		if (input->keyDown(GLFW_KEY_DOWN))
			speed--;

		if (input->keyDown(GLFW_KEY_RIGHT))
			y += 50.0f * deltaTime;
		if (input->keyDown(GLFW_KEY_LEFT))
			y -= 50.0f * deltaTime;

		if (input->keyDown(GLFW_KEY_ESCAPE))
			break;

		if (input->keyPressed(GLFW_KEY_B)) {
			phong = !phong;
			defaultShader->bind();
			defaultShader->setInt("phong", phong);
			defaultShader->unBind();
		}

		if (input->keyPressed(GLFW_KEY_C))
			gammaCorrect = !gammaCorrect;

		if (deltaSum >= numUpdates / 60.0) {
			input->update();
			numUpdates++;
		}

		input->update();
		window->Update();
		numFrames++;
		glFlush();
		//glFinish();
	}
	defaultShader->unBind();

	delete cube;
	delete skybox;
	delete model;
#ifdef POST_PROCESS
	delete colorBuffer;
	delete renderBuffer;
	delete screenBuffer;
	delete screenShader;
#endif
#ifdef CUSTOM_MULTISAMPLE
	delete sampleFrameBuffer;
	delete sampleTexture;
	delete sampleRenderBuffer;
#endif

#ifdef INSTANCED
	delete rock;
	delete bufferObject;
#endif
	delete normalShader;
	delete defaultShader;
	delete renderer;
	delete window;

	return 0;
}