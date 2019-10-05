#include <GL/glew.h>
#include "renderer.hpp"
#include "GameObjects/gameObject.hpp"
#include "Logs/logs.hpp"
#include "buffers.hpp"
#include "openglErrors.hpp"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <iostream>

namespace ph {

Renderer::Renderer()
{
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
		PH_LOG_ERROR("GLEW wasn't initialized correctly!");

	/*GLCheck( const GLubyte* openglVersionInfo = glGetString(GL_VERSION) );
	std::cout << "OpenGL version: " << openglVersionInfo << std::endl;*/

	GLCheck( glEnable(GL_BLEND) );
	GLCheck( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
}

void Renderer::setUpModernOpenGlTest()
{
	mShader = std::make_shared<Shader>("resources/shaders/basic.vs.glsl", "resources/shaders/basic.fs.glsl");

	std::array<float, 16> vertices = {
	  // positions | texture coords
		 0.5f,  0.5f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f  // top left 
	};

	std::array<unsigned, 6> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	VertexBuffer vbo = createVertexBuffer(vertices.data(), vertices.size() * sizeof(float));
	IndexBuffer ibo = createIndexBuffer(indices.data(), indices.size() * sizeof(unsigned));
	mVao = std::make_shared<VertexArray>();
	mVao->setVertexBuffer(vbo, VertexBufferLayout::position2_texCoords2);
	mVao->setIndexBuffer(ibo);

	mTexture = std::make_shared<Texture>("resources/textures/others/gate.png");

	mCamera = std::make_shared<Camera>();
}

void Renderer::drawModernOpenGlTest()
{
	glClearColor(0.2, 0.3, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	sf::Transform modelMatrix = sf::Transform::Identity;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mCamera->move({-0.02f, 0.f});
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mCamera->move({0.02f, 0.f});
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		mCamera->move({0.f, 0.02f});
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		mCamera->move({0.f, -0.02f});

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		mCamera->zoom(1.01);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		mCamera->zoom(0.99);

	mTexture->bind();

	mShader->bind();
	mShader->setUniformMatrix4x4("modelMatrix", modelMatrix.getMatrix());
	mShader->setUniformMatrix4x4("viewProjectionMatrix", mCamera->getViewProjectionMatrix4x4());
	
	mVao->bind();
	
	GLCheck( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) );
}

}
