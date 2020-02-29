/**
 * File              : SandboxApp.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include <engine.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "platform/opengl/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

// camera
//m_Texture = Engine::Texture2D::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/portal.png");
//const std::string textureSrc = "";
const std::string textureSrc = "/home/phil/work/private/games/bucket-engine/sandbox/assets/Checkerboard.png";
const std::string textureSrc2 = "/home/phil/work/private/games/bucket-engine/sandbox/assets/portal.png";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer()
      :Layer("Example"),
      // m_Camera(glm::vec3(0.0f, 0.0f, 3.0f)),
      m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
      m_CameraPosition(0.0f),
      m_SquarePosition(0.0f)
    {
      m_VertexArray.reset(Engine::VertexArray::Create());

      float vertices [3 * 7] = {
          -0.5f, -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
           0.5f, -0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
           0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
      };
      Engine::Ref<Engine::VertexBuffer> triangleVB;
      triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

      Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "position" },
        { Engine::ShaderDataType::Float4, "color" }
      };

      triangleVB->SetLayout(layout);
      m_VertexArray->AddVertexBuffer(triangleVB);

      uint32_t indices[3] = {0, 1, 2};

      Engine::Ref<Engine::IndexBuffer> triangleIA;
      triangleIA.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
      m_VertexArray->SetIndexBuffer(triangleIA);

      m_SquareVA.reset(Engine::VertexArray::Create());

      float squareVertices [5 * 4] = {
          -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
           0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
           0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
          -0.5f,  0.5f,  0.0f,  0.0f,  1.0f
      };

      Engine::Ref<Engine::VertexBuffer> squareVB;
      squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
      squareVB->SetLayout({
        { Engine::ShaderDataType::Float3, "position" },
        { Engine::ShaderDataType::Float2, "textCord" }
      });
      m_SquareVA->AddVertexBuffer(squareVB);


      uint32_t squareIndices[6] = {
        0, 1, 2,
        2, 3, 0
      };
      Engine::Ref<Engine::IndexBuffer> squareIA;
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
      m_Shader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));


      std::string flatColorVertexSrc = R"(
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
      std::string flatColorFragmentSrc = R"(
        #version 130
        in vec3 v_Position;
        uniform vec3 u_Color;
        out vec4 color;
        void main() {
          color = vec4(u_Color, 1.0);
        }
      )";
      m_FlatColorShader.reset(Engine::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));

      std::string textureVertexSrc = R"(
        #version 130
        in vec3 position;
        in vec2 textCord;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec2 v_TextCord;

        void main() {
          v_TextCord = textCord;
          gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
        }
      )";
      std::string textureFragmentSrc = R"(
        #version 130
        in vec2 v_TextCord;

        out vec4 color;

        uniform sampler2D u_Texture;

        void main() {
          color = texture(u_Texture, v_TextCord);
        }
      )";
      m_TextureShader.reset(Engine::Shader::Create(textureVertexSrc, textureFragmentSrc));
    
      m_Texture = Engine::Texture2D::Create(textureSrc);
      m_PortalTexture = Engine::Texture2D::Create(textureSrc2);
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

    }

    void OnUpdate(Engine::Timestep ts) override {
      {
        if (Engine::Input::IsKeyPressed(BE_KEY_LEFT)) {
          m_CameraPosition.x -= m_CameraSpeed * ts;
        } else if (Engine::Input::IsKeyPressed(BE_KEY_RIGHT)) {
          m_CameraPosition.x += m_CameraSpeed * ts;
        }
        if (Engine::Input::IsKeyPressed(BE_KEY_UP)) {
          m_CameraPosition.y += m_CameraSpeed * ts;
        } else if (Engine::Input::IsKeyPressed(BE_KEY_DOWN)) {
          m_CameraPosition.y -= m_CameraSpeed * ts;
        }
      }
      {
        if (Engine::Input::IsKeyPressed(BE_KEY_J)) {
          m_SquarePosition.x += m_SquareMoveSpeed * ts;
        } else if (Engine::Input::IsKeyPressed(BE_KEY_L)) {
          m_SquarePosition.x -= m_SquareMoveSpeed * ts;
        }
        if (Engine::Input::IsKeyPressed(BE_KEY_I)) {
          m_SquarePosition.y -= m_SquareMoveSpeed * ts;
        } else if (Engine::Input::IsKeyPressed(BE_KEY_K)) {
          m_SquarePosition.y += m_SquareMoveSpeed * ts;
        }
      }
      Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
      Engine::RenderCommand::Clear();

      /*
      {
        float xpos = Engine::Input::GetMouseX();
        float ypos = Engine::Input::GetMouseY();

        if (firstMouse)
        {
          lastX = xpos;
          lastY = ypos;
          firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;
        m_Camera.ProcessMouseMovement(xoffset, yoffset);
      }
      */

      m_Camera.SetPosition(m_CameraPosition);
      m_Camera.SetRotation(0.0f);

      Engine::Renderer::BeginScene(m_Camera);

      glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

      // TODO: Goal
      //Engine::MaterialRef material = new Engine::Material(m_FlatColorShader);
      //Engine::MaterialInstanceRef ml = new Engine::MaterialInstance(material);
      //ml->Set("u_Color", redColor);
      //squareMesh->SetMaterial(ml);

      // Grid
      for(int y = -10; y < 20; ++y) {
        for(int x = -10; x < 20; ++x) {
          glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
          Engine::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
          //Engine::Renderer::Submit(ml, m_FlatColorShader, transform);
        }
      }

      m_Texture->Bind();
      Engine::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
      m_PortalTexture->Bind();
      Engine::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
      /*
      Engine::Renderer::Submit(
        m_SquareVA,
        m_TextureShader,
        glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
      );
      */
      // Triangle
      // Engine::Renderer::Submit(m_VertexArray, m_Shader);

      Engine::Renderer::EndScene();


    }
    void OnEvent(Engine::Event& event) override {
      Engine::EventDispatcher dispatcher(event);

      dispatcher.Dispatch<Engine::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

    }
    bool OnKeyPressedEvent(Engine::KeyPressedEvent& event){
      return false;
    }

    virtual void OnImGuiRender() override {
      ImGui::Begin("Settings");
      ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
      ImGui::End();
    }
  private:
    Engine::Ref<Engine::Shader> m_Shader;
    Engine::Ref<Engine::Shader> m_FlatColorShader, m_TextureShader;

    Engine::Ref<Engine::VertexArray> m_VertexArray;
    Engine::Ref<Engine::VertexArray> m_SquareVA;

    Engine::Ref<Engine::Texture2D> m_Texture;
    Engine::Ref<Engine::Texture2D> m_PortalTexture;

    Engine::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed = 5.0f;
    float m_SquareMoveSpeed = 5.0f;

    glm::vec3 m_SquarePosition;
    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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
