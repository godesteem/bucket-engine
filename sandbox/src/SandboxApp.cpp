/**
 * File              : SandboxApp.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 09.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include <engine.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

// camera
//m_Texture = Engine::Texture2D::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/portal.png");
//const std::string textureSrc = "";
const std::string textureSrc = "/home/phil/work/private/games/bucket-engine/sandbox/assets/Checkerboard.png";
const std::string textureSrc2 = "/home/phil/work/private/games/bucket-engine/sandbox/assets/portal.png";

class ExampleLayer: public Engine::Layer
{
  enum Objects {
    Suzanne, Triangle, Cube3D, Cube2D, Grid, ImageTexture, Cube3DMan
  };

  public:
    ExampleLayer()
      :Layer("Example"),
      m_SquarePosition(0.0f)
    {
      m_VertexArray.reset(Engine::VertexArray::Create());

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
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f
      };
      Engine::Ref<Engine::VertexBuffer> triangleVB;
      triangleVB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

      Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "position" },
        { Engine::ShaderDataType::Float2, "texture" },
      };

      triangleVB->SetLayout(layout);
      m_VertexArray->AddVertexBuffer(triangleVB);

      uint32_t indices[36] = {
          0, 1, 2,
          3, 4, 5,
          6, 7, 8,
          9, 10, 11,
          12, 13, 14,
          15, 16, 17,
          18, 19, 20,
          21, 22, 23,
          24, 25, 26,
          27, 28, 29,
          30, 31, 32,
          33, 34, 35
      };

      Engine::Ref<Engine::IndexBuffer> triangleIA;
      triangleIA.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));
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
      squareIA.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
      m_SquareVA->SetIndexBuffer(squareIA);

      m_Shader = Engine::Shader::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Default.glsl");
      m_FlatColorShader = Engine::Shader::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/FlatColor.glsl");
      auto textureShader = m_ShaderLibrary.Load("Texture", "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Texture.glsl");

      m_Texture = Engine::Texture2D::Create(textureSrc);
      m_PortalTexture = Engine::Texture2D::Create(textureSrc2);
      m_Suzanne = Engine::Mesh::Create(
          "/home/phil/work/private/games/bucket-engine/sandbox/assets/models/Suzanne.obj",
          "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Suzanne.glsl");
      m_Cube = Engine::Mesh::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/models/Example.obj",
                                    "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Example.glsl");
      m_Models.push_back(Engine::Mesh::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/models/Light.obj",
                                              "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Light.glsl"));
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));

      m_Shader->Bind();
      m_Shader->UploadUniformMat4("model", model);
      textureShader->Bind();
      textureShader->UploadUniformInt("u_Texture", 0);
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

      m_FlatColorShader->Bind();
      m_FlatColorShader->UploadUniformFloat3("u_Color", m_SquareColor);
      
      glm::mat4 model = glm::mat4(1.0f);
      m_Shader->Bind();
      m_Shader->UploadUniformMat4("model", model);
      if(objects[Objects::Cube3DMan]) {
        Engine::Renderer::Submit(m_VertexArray, m_FlatColorShader, glm::mat4(1.0f));
      }
      // TODO: Goal
      //Engine::MaterialRef material = new Engine::Material(m_FlatColorShader);
      //Engine::MaterialInstanceRef ml = new Engine::MaterialInstance(material);
      //ml->Set("u_Color", redColor);
      //squareMesh->SetMaterial(ml);
     

      if(objects[Objects::Grid]) {
        // Grid
        for (int y = -10; y < 20; ++y) {
          for (int x = -10; x < 20; ++x) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Engine::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
          }
        }
      }
      auto textureShader = m_ShaderLibrary.Get("Texture");
      if(objects[Objects::ImageTexture]) {
        m_Texture->Bind();
        Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_PortalTexture->Bind();
        Engine::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
      }
        if (objects[Objects::Cube2D]) {
          Engine::Renderer::Submit(
              m_SquareVA,
              textureShader,
              glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) *
              glm::scale(glm::mat4(1.0f), glm::vec3(1.5f))
          );
        }

      if(objects[Objects::Triangle]) glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * scale;

      if(objects[Objects::Cube3D]) m_Cube->OnUpdate(ts, m_PlayerCameraLayer.GetCamera());
      if(objects[Objects::Suzanne]) m_Suzanne->OnUpdate(ts, m_PlayerCameraLayer.GetCamera());
      for(const auto& obj : m_Models){
        obj->OnUpdate(ts, m_PlayerCameraLayer.GetCamera());
      }
      m_PlayerCameraLayer.OnUpdate(ts);

      Engine::Renderer::EndScene();
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
      ImGui::Checkbox("Suzanne", &objects[0]);
      ImGui::Checkbox( "Triangle", &objects[1]);
      ImGui::Checkbox("Cube3D", &objects[2]);
      ImGui::Checkbox( "Cube2D", &objects[3]);
      ImGui::Checkbox("Grid", &objects[4]);
      ImGui::Checkbox("ImageTexture", &objects[5]);
      ImGui::Checkbox("Cube3DMan", &objects[6]);
      ImGui::End();
      m_PlayerCameraLayer.OnImGuiRender();
      m_Suzanne->OnImGuiRender();
      m_Cube->OnImGuiRender();
      for(const auto& obj : m_Models){
        obj->OnImGuiRender();
      }
    }
  private:
    Engine::ShaderLibrary m_ShaderLibrary;
    Engine::Ref<Engine::Shader> m_Shader;
    Engine::Ref<Engine::Shader> m_FlatColorShader;

    Engine::Ref<Engine::VertexArray> m_VertexArray;
    Engine::Ref<Engine::VertexArray> m_SquareVA;

    Engine::Ref<Engine::Texture2D> m_Texture;
    Engine::Ref<Engine::Texture2D> m_PortalTexture;

    Engine::OrthographicCameraController m_PlayerCameraLayer;

    Engine::Ref<Engine::Mesh> m_Suzanne;
    Engine::Ref<Engine::Mesh> m_Cube;
    std::vector<Engine::Ref<Engine::Mesh>> m_Models;

    float m_SquareMoveSpeed = 5.0f;
    bool objects[7] = {false, false, false, false, false, false, true};

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

    ~Sandbox() = default;
};

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}
