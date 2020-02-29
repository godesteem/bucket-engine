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

class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer()
      :Layer("Example"),
      m_SquarePosition(0.0f)
    {
      m_VertexArray.reset(Engine::VertexArray::Create());
  
      /*
      2D cube \w color
      float vertices [3 * 7] = {
          -0.5f, -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
           0.5f, -0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
           0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
      };
      
      2D cube \w texture
      float vertices [] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
      };
      */
      float vertices [] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
        
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
      
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
      };
      Engine::Ref<Engine::VertexBuffer> triangleVB;
      triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

      Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "position" },
        { Engine::ShaderDataType::Float2, "texture" },
      };

      triangleVB->SetLayout(layout);
      m_VertexArray->AddVertexBuffer(triangleVB);

      uint32_t indices[6] = {0, 1, 3, 1, 2, 3};

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

      m_Shader = Engine::Shader::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Default.glsl");
      m_FlatColorShader = Engine::Shader::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/FlatColor.glsl");
      auto textureShader = m_ShaderLibrary.Load("Texture", "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Texture.glsl");

      m_Texture = Engine::Texture2D::Create(textureSrc);
      m_PortalTexture = Engine::Texture2D::Create(textureSrc2);
      
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));

      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_Shader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_Shader)->UploadUniformMat4("model", model);
      std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

    }

    void OnUpdate(Engine::Timestep ts) override {
      Engine::Renderer::BeginScene(m_PlayerCameraLayer.GetCamera());
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

      glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
      
      glm::mat4 model = glm::mat4(1.0f);
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_Shader)->Bind();
      std::dynamic_pointer_cast<Engine::OpenGLShader>(m_Shader)->UploadUniformMat4("model", model);

      BE_TRACE("SandboxApp::OnUpdate Render");

      // TODO: Goal
      //Engine::MaterialRef material = new Engine::Material(m_FlatColorShader);
      //Engine::MaterialInstanceRef ml = new Engine::MaterialInstance(material);
      //ml->Set("u_Color", redColor);
      //squareMesh->SetMaterial(ml);
     
     /* 
      // Grid
      for(int y = -10; y < 20; ++y) {
        for(int x = -10; x < 20; ++x) {
          glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
          Engine::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
          //Engine::Renderer::Submit(ml, m_FlatColorShader, transform);
        }
      }
      
      auto textureShader = m_ShaderLibrary.Get("Texture");

      m_Texture->Bind();
      Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
      m_PortalTexture->Bind();
      Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
      
      
      Engine::Renderer::Submit(
        m_SquareVA,
        m_TextureShader,
        glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
      );
      */
      // Triangle
      //glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * scale;
      Engine::Renderer::Submit(m_VertexArray, m_Shader, glm::mat4(1.0f));

      Engine::Renderer::EndScene();

      m_PlayerCameraLayer.OnUpdate(ts);
    }
    void OnEvent(Engine::Event& event) override {
      Engine::EventDispatcher dispatcher(event);

      dispatcher.Dispatch<Engine::KeyPressedEvent>(BE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
      m_PlayerCameraLayer.OnEvent(event);
    }
    bool OnKeyPressedEvent(Engine::KeyPressedEvent& event){
      return false;
    }

    virtual void OnImGuiRender() override {
      ImGui::Begin("Admin");
      ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
      ImGui::End();
      m_PlayerCameraLayer.OnImGuiRender();

    }
  private:
    Engine::ShaderLibrary m_ShaderLibrary;
    Engine::Ref<Engine::Shader> m_Shader;
    Engine::Ref<Engine::Shader> m_FlatColorShader;

    Engine::Ref<Engine::VertexArray> m_VertexArray;
    Engine::Ref<Engine::VertexArray> m_SquareVA;

    Engine::Ref<Engine::Texture2D> m_Texture;
    Engine::Ref<Engine::Texture2D> m_PortalTexture;

    Engine::OrthographicCameraLayer m_PlayerCameraLayer;

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
