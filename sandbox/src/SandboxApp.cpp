/**
 * File              : SandboxApp.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include <engine.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>


class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer()
      :Layer("Example"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
    {
      m_VertexArray.reset(Engine::VertexArray::Create());

      float vertices [3 * 7] = {
          -0.5f, -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
           0.5f, -0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
           0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
      };
      std::shared_ptr<Engine::VertexBuffer> triangleVB;
      triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

      Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "position" },
        { Engine::ShaderDataType::Float4, "color" }
      };

      triangleVB->SetLayout(layout);
      m_VertexArray->AddVertexBuffer(triangleVB);

      uint32_t indices[3] = {0, 1, 2};

      std::shared_ptr<Engine::IndexBuffer> triangleIA;
      triangleIA.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
      m_VertexArray->SetIndexBuffer(triangleIA);

      m_SquareVA.reset(Engine::VertexArray::Create());

      float squareVertices [3 * 4] = {
          -0.5f, -0.5f,  0.0f,
           0.5f, -0.5f,  0.0f,
           0.5f,  0.5f,  0.0f,
          -0.5f,  0.5f,  0.0f,
      };

      std::shared_ptr<Engine::VertexBuffer> squareVB;
      squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
      squareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "position" }
      });
      m_SquareVA->AddVertexBuffer(squareVB);


      uint32_t squareIndices[6] = {
        0, 1, 2,
        2, 3, 0
      };
      std::shared_ptr<Engine::IndexBuffer> squareIA;
      squareIA.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)/ sizeof(uint32_t)));
      m_SquareVA->SetIndexBuffer(squareIA);

      BE_CORE_TRACE("Setting Shader");
      std::string vertexSrc = R"(
        #version 130
        in vec3 position;
        in vec4 color;
        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
          v_Position = position;
          v_Color = color;
          gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
        }
      )";
      std::string fragmentSrc = R"(
        #version 130
        in vec4 v_Color;
        in vec3 v_Position;
        out vec4 color;
        void main() {
          color = vec4(v_Position * 0.5 + 0.5, 1.0);
          color = v_Color;
        }
      )";
      m_Shader.reset(new Engine::Shader(vertexSrc, fragmentSrc));


      std::string flatColorvertexSrc = R"(
        #version 130
        in vec3 position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main() {
          v_Position = position;
          gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
        }
      )";
      std::string flatColorfragmentSrc = R"(
        #version 130
        in vec3 v_Position;
        uniform vec4 u_Color;
        out vec4 color;
        void main() {
          color = u_Color;
        }
      )";
      m_FlatColorShader.reset(new Engine::Shader(flatColorvertexSrc, flatColorfragmentSrc));

    }

    virtual void OnImGuiRender() override {
    }
    
    void OnUpdate(Engine::Timestep ts) override {

      if(Engine::Input::IsKeyPressed(BE_KEY_LEFT)){
        m_CameraPosition.x -= m_CameraSpeed * ts;
      }
      else if(Engine::Input::IsKeyPressed(BE_KEY_RIGHT)){
        m_CameraPosition.x += m_CameraSpeed * ts;
      }
      if(Engine::Input::IsKeyPressed(BE_KEY_UP)){
        m_CameraPosition.y += m_CameraSpeed * ts;
      }
      else if(Engine::Input::IsKeyPressed(BE_KEY_DOWN)){
        m_CameraPosition.y -= m_CameraSpeed * ts;
      }

      if(Engine::Input::IsKeyPressed(BE_KEY_J)){
        m_SquarePosition.x += m_SquareMoveSpeed * ts;
      }
      else if(Engine::Input::IsKeyPressed(BE_KEY_L)){
        m_SquarePosition.x -= m_SquareMoveSpeed * ts;
      }
      if(Engine::Input::IsKeyPressed(BE_KEY_I)){
        m_SquarePosition.y -= m_SquareMoveSpeed * ts;
      }
      else if(Engine::Input::IsKeyPressed(BE_KEY_K)){
        m_SquarePosition.y += m_SquareMoveSpeed * ts;
      }
      Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
      Engine::RenderCommand::Clear();

      m_Camera.SetPosition(m_CameraPosition);
      m_Camera.SetRotation(0.0f);

      Engine::Renderer::BeginScene(m_Camera);

      glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

      glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
      glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

      // TODO: Goal
      //Engine::MaterialRef material = new Engine::Material(m_FlatColorShader);
      //Engine::MaterialInstanceRef ml = new Engine::MaterialInstance(material);
      //ml->Set("u_Color", redColor);
      //squareMesh->SetMaterial(ml);

      for(int y = 0; y < 20; y++) {
        for(int x = 0; x < 20; x++) {
          glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
          if(x % 2 == 0){
            m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
          }
          else {
            m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);
          }
          Engine::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
          //Engine::Renderer::Submit(ml, m_FlatColorShader, transform);
        }
      }

      Engine::Renderer::Submit(m_VertexArray, m_Shader);

      Engine::Renderer::EndScene();


    }
    void OnEvent(Engine::Event& event) override {
      Engine::EventDispatcher dispatcher(event);

      dispatcher.Dispatch<Engine::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPresseEvent));

    }
    bool OnKeyPresseEvent(Engine::KeyPressedEvent& event){
      return false;
    }
  private:
    std::shared_ptr<Engine::Shader> m_Shader;
    std::shared_ptr<Engine::Shader> m_FlatColorShader;

    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::VertexArray> m_SquareVA;

    Engine::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed = 5.0f;
    float m_SquareMoveSpeed = 5.0f;

    glm::vec3 m_SquarePosition;
};

class Sandbox: public Engine::Application
{
  public:
    Sandbox()
    {
      PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}
