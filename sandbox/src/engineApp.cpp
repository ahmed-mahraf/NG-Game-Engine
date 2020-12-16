/** \file engineApp.cpp
*/
#include "engineApp.h"


ExampleLayer::ExampleLayer()
	: Layer("Shape"), m_cameraController(1280.f / 720.f)
{
	//<!create triangle 
	m_vA = Engine::VertexArray::create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	m_vB = Engine::VertexBuffer::create(vertices, sizeof(vertices));
	Engine::BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "a_Position" },
		{ Engine::ShaderDataType::Float4, "a_Color" }
	};
	m_vB->setLayout(layout);
	m_vA->addVertexBuffer(m_vB);

	uint32_t indices[3] = { 0, 1, 2 };
	m_iB = Engine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
	m_vA->setIndexBuffer(m_iB);

	m_quadVA = Engine::VertexArray::create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	
	m_quadVB = Engine::VertexBuffer::create(squareVertices, sizeof(squareVertices));
	m_quadVB->setLayout({
		{ Engine::ShaderDataType::Float3, "a_Position" },
		{ Engine::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_quadVA->addVertexBuffer(m_quadVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	m_quadIB = Engine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_quadVA->setIndexBuffer(m_quadIB);

	std::string vertexSrc = R"(
			#version 440 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string fragmentSrc = R"(
			#version 440 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_shader = Engine::Shader::create("VertexPosColor", vertexSrc, fragmentSrc);

	std::string quadShaderVertexSrc = R"(
			#version 440 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string quadShaderFragmentSrc = R"(
			#version 440 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_quadShader = Engine::Shader::create("FlatColor", quadShaderVertexSrc, quadShaderFragmentSrc);

	auto textureShader = m_shaderLibrary.load("assets/shaders/Texture.glsl");

	m_texture = Engine::Texture2D::create("assets/textures/Checkerboard.png");
	m_pacmanTexture = Engine::Texture2D::create("assets/textures/pacman.png");

	textureShader->bind();
	textureShader->setInt("u_Texture", 0);
}

void ExampleLayer::onUpdate(Engine::Timestep ts)
{
	m_cameraController.onUpdate(ts);

	Engine::RenderCommand::setClearColour({ 0.1f, 0.1f, 0.1f, 1 });
	Engine::RenderCommand::clear();

	Engine::Renderer::beginScene(m_cameraController.getCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_quadShader->bind();
	m_quadShader->setFloat3("u_Color", m_quadColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Engine::Renderer::submit(m_quadShader, m_quadVA, transform);
		}
	}

	auto textureShader = m_shaderLibrary.get("Texture");

	m_texture->bind();
	Engine::Renderer::submit(textureShader, m_quadVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_pacmanTexture->bind();
	Engine::Renderer::submit(textureShader, m_quadVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Engine::Renderer::endScene();
}

void ExampleLayer::onEvent(Engine::Event & e)
{
	m_cameraController.onEvent(e);
}

void ExampleLayer::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_quadColor));
	ImGui::End();
}

//<!engine app constructor
engineApp::engineApp()
{
	//PushLayer(new ExampleLayer()); // MAIN SHAPE LAYER
	PushLayer(new Engine2D()); // MAIN SHAPE LAYER
}
//<!engine app deconstructor
engineApp::~engineApp()
{

}

//<!start application
Engine::Application* Engine::startApplication()
{
	return new engineApp();
}