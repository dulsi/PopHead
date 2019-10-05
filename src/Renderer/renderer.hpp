#pragma once

#include "vertexArray.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include <memory>

namespace ph {

class GameObject;
class Map;

class Renderer
{
public:
	Renderer();
	
	Renderer(Renderer&) = delete;
	Renderer& operator=(Renderer&) = delete;

	void setUpModernOpenGlTest();
	void drawModernOpenGlTest();

private:
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<VertexArray> mVao;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Camera> mCamera;
};

}
